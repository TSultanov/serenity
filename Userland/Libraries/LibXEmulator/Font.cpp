#include <AK/HashMap.h>
#include <AK/String.h>
#include <LibGfx/Font/Font.h>
#include <LibGfx/Font/FontDatabase.h>

#include "Font.h"

#include <ctype.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xatom.h>
}
}

//static struct FontDatabaseInitializer {
//    FontDatabaseInitializer()
//    {
//        Gfx::FontDatabase::the().set_default_font_query("Katica 10 400 0"sv);
//    }
//} g_init;

struct XLFD {
    String foundry = "*";
    String family = "*";
    String weight = "*";
    char slant = '*';
    String setwidth = "*";
    String add_style = "*";
    int pixels = 0, decipoints = 0;
    int resolution_x = 0, resolution_y = 0;
    char spacing = '*';
    int average_width = 0;
    String charset = "*";
    String encoding = "*";
};

struct FontEntry {
    XLFD xlfd;
    String variant;
};
static AK::HashMap<uint16_t, FontEntry*> sFonts;
static uint16_t sLastFontID = 1;

enum {
    DEFAULT_PLAIN_FONT = 0,
    DEFAULT_FIXED_FONT,

    COUNT_DEFAULT_FONTS
};
static uint16_t sDefaultFonts[COUNT_DEFAULT_FONTS] = {};

static XLib::Font
make_Font(uint16_t id, uint16_t pointSize)
{
    return (id & UINT16_MAX) | ((pointSize & UINT16_MAX) << 16);
}

static char
get_slant(String variant)
{
    if (!variant.equals_ignoring_case("Italic"))
        return 'r';
    return 'i';
}

static const char*
get_weight(String variant)
{
    static const char* medium = "medium";
    static const char* bold = "bold";
    if (variant.equals_ignoring_case("bold"))
        return bold;
    return medium;
}

static XLFD
create_xlfd(String family, String variant)
{
    XLFD xlfd;
    xlfd.foundry = "TTFont";
    xlfd.family = family;
    xlfd.weight = get_weight(variant);
    xlfd.slant = get_slant(variant);
    xlfd.setwidth = "normal";
    xlfd.add_style = "";
    xlfd.spacing = 'p'; // FIXME

    xlfd.charset = "iso10646-8";
    return xlfd;
}

static XLFD
parse_xlfd(const char* string)
{
    XLFD xlfd;
    const String bstring(string);
    if (!bstring.find('-').has_value()) {
        // Special case: set family only.
        xlfd.family = bstring;

        // Special case: fixed has a different default size.
        if (bstring == "fixed")
            xlfd.decipoints = 100;

        return xlfd;
    }

    auto values = bstring.split('-');

    for (size_t field = 0; field < values.size(); field++) {
        const auto value = values[field];

        switch (field) {
        case 1: xlfd.foundry = value; break;
        case 2: xlfd.family = value; break;
        case 3: xlfd.weight = value; break;
        case 4: xlfd.slant = value[0]; break;
        case 5: xlfd.setwidth = value; break;
        case 6: xlfd.add_style = value; break;
        case 7: xlfd.pixels			= strtol(value.characters(), NULL, 10); break;
        case 8: xlfd.decipoints		= strtol(value.characters(), NULL, 10); break;
        case 9: xlfd.resolution_x	= strtol(value.characters(), NULL, 10); break;
        case 10: xlfd.resolution_y	= strtol(value.characters(), NULL, 10); break;
        case 11: xlfd.spacing = value[0]; break;
        case 12: xlfd.average_width	= strtol(value.characters(), NULL, 10); break;
        case 13: xlfd.charset = value; break;
        case 14: xlfd.encoding = value; break;
            break;
        }
    }
    return xlfd;
}

static bool
compare_xlfds(const XLFD& compare, const XLFD& base, uint16_t baseID)
{
    const String wild_string = "*";

    // skip: foundry, resolution_x, resolution_y, average_width
#define COMPARE(FIELD, WILD) (compare.FIELD == WILD || base.FIELD == WILD || compare.FIELD == base.FIELD)
#define COMPARE_CHAR(FIELD) \
	(compare.FIELD == '*' || base.FIELD == '*' \
		|| compare.FIELD == base.FIELD || tolower(compare.FIELD) == base.FIELD)
#define COMPARE_STRING(FIELD) \
	(compare.FIELD == wild_string || base.FIELD == wild_string \
		|| compare.FIELD.equals_ignoring_case(base.FIELD))

    if (!COMPARE_STRING(family)) {
        // Special case: "Helvetica" matches the default display font,
        // and "fixed" or "cursor" matches the default fixed font.
        bool match = false;
        if (baseID == sDefaultFonts[DEFAULT_PLAIN_FONT] && compare.family.equals_ignoring_case("Helvetica"))
            match = true;
        if (baseID == sDefaultFonts[DEFAULT_FIXED_FONT] && compare.family.equals_ignoring_case("fixed"))
            match = true;
        if (baseID == sDefaultFonts[DEFAULT_FIXED_FONT] && compare.family.equals_ignoring_case("cursor"))
            match = true;
        if (!match)
            return false;
    }
    if (!COMPARE_STRING(weight))
        return false;
    if (!COMPARE_CHAR(slant))
        return false;
    if (!COMPARE_STRING(setwidth))
        return false;
    if (!COMPARE_STRING(add_style))
        return false;
    if (!COMPARE(pixels, 0))
        return false;
    if (!COMPARE(decipoints, 0))
        return false;
    if (!COMPARE_CHAR(spacing))
        return false;
    if (!COMPARE_STRING(charset))
        return false;
    if (!COMPARE_STRING(encoding))
        return false;

#undef COMPARE

    return true;
}

void
_x_init_font()
{
    if (sFonts.size() != 0)
        return;


    Gfx::FontDatabase::the().set_default_font_query("Katica 10 400 0"sv);
    Gfx::FontDatabase::the().set_fixed_width_font_query("Csilla 10 400 0"sv);

    auto& default_plain_font = Gfx::FontDatabase::the().default_font();
    auto& default_fixed_Font =Gfx::FontDatabase::the().default_fixed_width_font();

    {
        FontEntry* font = new FontEntry;
        font->variant = default_plain_font.variant();
        font->xlfd = create_xlfd(default_plain_font.family(), default_plain_font.variant());
        sFonts.set(sLastFontID, font);
        sDefaultFonts[DEFAULT_PLAIN_FONT] = sLastFontID;
        sLastFontID++;
    }

    {
        FontEntry* font = new FontEntry;
        font->variant = default_fixed_Font.variant();
        font->xlfd = create_xlfd(default_fixed_Font.family(), default_fixed_Font.variant());
        sFonts.set(sLastFontID, font);
        sDefaultFonts[DEFAULT_FIXED_FONT] = sLastFontID;
        sLastFontID++;
    }
}

static void
extract_Font(XLib::Font font, uint16_t& id, uint16_t& pointSize)
{
    id = (font & UINT16_MAX);
    pointSize = (font >> 16) & UINT16_MAX;
}

static FontEntry*
lookup_font(int id)
{
    const auto& it = sFonts.get(id);
    if(it.has_value())
        return it.value();

    return nullptr;
}

AK::RefPtr<Gfx::Font> gfxfont_from_font(XLib::Font fid)
{
    uint16_t id, pointSize;
    extract_Font(fid, id, pointSize);

    FontEntry* fontId = lookup_font(id);
    if (!fontId)
        return Gfx::FontDatabase::the().default_font();

    auto font = Gfx::FontDatabase::the().get(fontId->xlfd.family, fontId->variant, pointSize);
    if(font.is_null())
        return Gfx::FontDatabase::the().default_font();
    return font;
}

extern "C" XLib::XFontStruct*
XLib::XQueryFont(Display */*display*/, Font id)
{
    FontEntry* ident = lookup_font(id);
    if (!ident)
        return NULL;

    auto bfont = gfxfont_from_font(id);

    XFontStruct* font = (XFontStruct*)calloc(1, sizeof(XFontStruct));
    font->fid = id;
    font->direction = FontLeftToRight; // FIXME
    font->min_char_or_byte2 = 0;
    font->max_char_or_byte2 = 0xFF;
    font->min_byte1 = 0;
    font->max_byte1 = 0;

    font->ascent = font->max_bounds.ascent = bfont->pixel_metrics().ascent;
    font->descent = font->max_bounds.descent = bfont->pixel_metrics().descent;

    font->min_bounds.width = bfont->width(".");
    font->max_bounds.width = bfont->width("@");

    return font;
}

extern "C" XLib::XFontStruct*
XLib::XLoadQueryFont(Display *display, const char *name)
{
    return XQueryFont(display, XLoadFont(display, name));
}

extern "C" XLib::Font
XLib::XLoadFont(Display* /*dpy*/, const char* name)
{
    XLFD patternXLFD = parse_xlfd(name);

    // Clear out sizes before comparing.
    uint16_t ptSize = patternXLFD.decipoints / 10;
    if (ptSize == 0)
        ptSize = patternXLFD.pixels * 0.75f;
    patternXLFD.decipoints = patternXLFD.pixels = 0;

    int id = 0;
    for (const auto& font : sFonts) {
        if (compare_xlfds(patternXLFD, font.value->xlfd, font.key)) {
            id = font.key;
            break;
        }
    }

    if (id != 0)
        return make_Font(id, ptSize);
    return 0;
}

