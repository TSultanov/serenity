#include <AK/Format.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
}
}

#define UNIMPLEMENTED() dbgln("Stub: {}", __func__)

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-result"

using namespace XLib;

extern "C" Cursor
XCreateFontCursor(Display *display, unsigned int xshape)
{
    UNIMPLEMENTED();
    return (Cursor)0;
}

extern "C" Cursor
XCreateGlyphCursor(Display *display, Font source_font, Font mask_font,
    unsigned int source_char, unsigned int mask_char,
    XColor const *foreground_color, XColor const *background_color)
{
    // TODO: other options?
    return XCreateFontCursor(display, source_char);
}

extern "C" Cursor
XCreatePixmapCursor(Display* display, Pixmap source, Pixmap mask,
    XColor* foreground_color, XColor* background_color,
    unsigned int x, unsigned int y)
{
    UNIMPLEMENTED();
    return (Cursor)0;
}

extern "C" Status
XFreeCursor(Display* display, Cursor cursor)
{
    UNIMPLEMENTED();
    return Success;
}

extern "C" Status
XRecolorCursor(Display* display, Cursor cursor, XColor* foreground_color, XColor* background_color)
{
    UNIMPLEMENTED();
    return BadImplementation;
}

extern "C" Status
XQueryBestCursor(Display* display, Drawable d, unsigned int width, unsigned int height,
    unsigned int* width_return, unsigned int* height_return)
{
    if (width_return)
        *width_return = width;
    if (height_return)
        *height_return = height;
    return Success;
}


#pragma GCC diagnostic pop