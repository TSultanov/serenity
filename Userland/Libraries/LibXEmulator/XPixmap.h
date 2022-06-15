#pragma once

#include <LibCore/Object.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Rect.h>
#include <LibGUI/Painter.h>

#include "XDrawable.h"

namespace XLib {
extern "C" {
#include "LibGUI/Painter.h"
#include <X11/Xlib.h>
}
}

class XPixmap : public XDrawable {
    C_OBJECT(XPixmap)
public:
    XLib::Pixmap id() { return m_id; }

    AK::RefPtr<Gfx::Bitmap> bitmap() { return m_bitmap; }
    GUI::Painter& painter() override { return m_painter; }
private:
    XPixmap(XLib::Display* dpy, Gfx::IntRect frame);

    XLib::Pixmap m_id;
    XLib::Display * m_display;
    Gfx::IntRect m_frame;

    AK::RefPtr<Gfx::Bitmap> m_bitmap;
    GUI::Painter m_painter;
};