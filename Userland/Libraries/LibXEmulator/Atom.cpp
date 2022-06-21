//#include <unordered_set>
//#include <unordered_map>
//#include <string_view>
#include <AK/HashTable.h>
#include <AK/HashMap.h>
#include <AK/String.h>

#include "Atom.h"

namespace XLib {
extern "C" {
#include <X11/Xatom.h>
#include <X11/Xlib.h>
}
}

struct AtomEntry {
    XLib::Atom id = -1;
    AK::String string;

    AtomEntry(const char* str, XLib::Atom id = -1) : id(id), string(strdup(str)) {}

    bool operator==(const AtomEntry& rhs) const {
        return string == rhs.string;
    }

    bool operator!=(const AtomEntry& rhs) const {
        return !(*this == rhs);
    }
};

template<>
struct AK::Traits<AtomEntry> : public GenericTraits<AtomEntry> {
    static unsigned hash(AtomEntry const& entry)
    {
        return entry.string.hash();
    }
};

static AK::HashTable<AtomEntry> sAtoms;
static AK::HashMap<XLib::Atom, AtomEntry> sPredefinedAtoms;

void
_x_init_atoms()
{
	const char* xa_names[] = {
        "NO_ATOM",
        "XA_PRIMARY",
        "XA_SECONDARY",
        "XA_ARC",
        "XA_ATOM",
        "XA_BITMAP",
        "XA_CARDINAL",
        "XA_COLORMAP",
        "XA_CURSOR",
        "XA_CUT_BUFFER0",
        "XA_CUT_BUFFER1",
        "XA_CUT_BUFFER2",
        "XA_CUT_BUFFER3",
        "XA_CUT_BUFFER4",
        "XA_CUT_BUFFER5",
        "XA_CUT_BUFFER6",
        "XA_CUT_BUFFER7",
        "XA_DRAWABLE",
        "XA_FONT",
        "XA_INTEGER",
        "XA_PIXMAP",
        "XA_POINT",
        "XA_RECTANGLE",
        "XA_RESOURCE_MANAGER",
        "XA_RGB_COLOR_MAP",
        "XA_RGB_BEST_MAP",
        "XA_RGB_BLUE_MAP",
        "XA_RGB_DEFAULT_MAP",
        "XA_RGB_GRAY_MAP",
        "XA_RGB_GREEN_MAP",
        "XA_RGB_RED_MAP",
        "XA_STRING",
        "XA_VISUALID",
        "XA_WINDOW",
        "XA_WM_COMMAND",
        "XA_WM_HINTS",
        "XA_WM_CLIENT_MACHINE",
        "XA_WM_ICON_NAME",
        "XA_WM_ICON_SIZE",
        "XA_WM_NAME",
        "XA_WM_NORMAL_HINTS",
        "XA_WM_SIZE_HINTS",
        "XA_WM_ZOOM_HINTS",
        "XA_MIN_SPACE",
        "XA_NORM_SPACE",
        "XA_MAX_SPACE",
        "XA_END_SPACE",
        "XA_SUPERSCRIPT_X",
        "XA_SUPERSCRIPT_Y",
        "XA_SUBSCRIPT_X",
        "XA_SUBSCRIPT_Y",
        "XA_UNDERLINE_POSITION",
        "XA_UNDERLINE_THICKNESS",
        "XA_STRIKEOUT_ASCENT",
        "XA_STRIKEOUT_DESCENT",
        "XA_ITALIC_ANGLE",
        "XA_X_HEIGHT",
        "XA_QUAD_WIDTH",
        "XA_WEIGHT",
        "XA_POINT_SIZE",
        "XA_RESOLUTION",
        "XA_COPYRIGHT",
        "XA_NOTICE",
        "XA_FONT_NAME",
        "XA_FAMILY_NAME",
        "XA_FULL_NAME",
        "XA_CAP_HEIGHT",
        "XA_WM_CLASS",
        "XA_WM_TRANSIENT_FOR",
        NULL
    };

    //PthreadWriteLocker wrlock(sAtomsLock);
    if (sAtoms.contains(xa_names[0]))
        return; // Already initialized.

    auto insert = [](const char* name, XLib::Atom id) {
        sAtoms.set(AtomEntry(name, id));
        sPredefinedAtoms.set(id, *sAtoms.find(name));
    };

    for (int i = 0; xa_names[i] != NULL; i++)
        insert(xa_names[i], i);

#define ATOM(NAME) insert(#NAME, Atoms::NAME);
#include "atoms.h"
#undef ATOM
}
