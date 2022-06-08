#pragma once

#include <LibCore/Object.h>
#include <LibGfx/Bitmap.h>
#include <LibGfx/Rect.h>

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

class XPixmap : public Core::Object {
    C_OBJECT(XPixmap)
public:
    XLib::Pixmap id() { return m_id; }

    AK::RefPtr<Gfx::Bitmap> bitmap() { return m_bitmap; }
private:
    XPixmap(XLib::Display* dpy, Gfx::IntRect frame);

    XLib::Pixmap m_id;
    XLib::Display * m_display;
    Gfx::IntRect m_frame;

    AK::RefPtr<Gfx::Bitmap> m_bitmap;
};