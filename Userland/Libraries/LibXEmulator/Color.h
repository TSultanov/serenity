#pragma once

#include <LibGfx/Color.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

static inline void
_x_get_rgb_masks(XLib::Visual* v)
{
    v->red_mask     = 255 << 16;
    v->green_mask   = 255 << 8;
    v->blue_mask    = 255;
}

static inline unsigned long
_x_rgb_to_pixel(Color color)
{
    long result = long(color.blue()) | (long(color.green()) << 8)
        | (long(color.red()) << 16) | (long(color.alpha()) << 24);
    return result;
}
