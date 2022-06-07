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

    AK::RefPtr<GUI::Window> window() {
        return this->m_window;
    }

    long event_mask() { return m_event_mask; }
    void event_mask(long mask);

    void create_host_window();

    XWindow* parent_window();

    GUI::Painter& painter() { return m_painter; }

protected:
    void paint_event(GUI::PaintEvent&) override;

private:
    XWindow(XLib::Display* display, Gfx::IntRect frame);

    XLib::Window m_id;
    XLib::Display * m_display;

    long m_event_mask;

    GUI::Painter m_painter;

    AK::RefPtr<GUI::Window> m_window;
};