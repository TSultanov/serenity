#pragma once
#include <LibGfx/Font/Font.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xatom.h>
}
}

AK::RefPtr<Gfx::Font> gfxfont_from_font(XLib::Font fid);

void _x_init_font();