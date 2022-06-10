#pragma once

#include "LibGUI/Painter.h"
#include "LibGUI/Window.h"
#include "LibGUI/Widget.h"
#include "LibCore/Object.h"

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

class XWindow : public GUI::Widget {
    C_OBJECT(XWindow)
public:
    XLib::Window id() const {
        return m_id;
    }

    long event_mask() const { return m_event_mask; }
    void event_mask(long mask);

    XWindow* parent_window();

    GUI::Painter& painter() { return m_painter; }

protected:
    void paint_event(GUI::PaintEvent&) override;
    void resize_event(GUI::ResizeEvent&) override;

private:
    XWindow(XLib::Display* display, RefPtr<GUI::Window> host_window, Gfx::IntRect frame);

    XLib::Window m_id;
    XLib::Display * m_display;

    long m_event_mask;

    AK::RefPtr<GUI::Window> m_window;

    AK::NonnullRefPtr<Gfx::Bitmap> m_bitmap;
    GUI::Painter m_painter;
};