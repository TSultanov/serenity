#pragma once

#include "LibGUI/Painter.h"
#include "LibGUI/Window.h"
#include "LibGUI/Widget.h"
#include "LibCore/Object.h"

#include "XDrawable.h"

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
}
}

class XWindow;

class _XWidgetImpl : public GUI::Widget {
    C_OBJECT(_XWidgetImpl)

protected:
    void paint_event(GUI::PaintEvent&) override;
    void resize_event(GUI::ResizeEvent&) override;

private:
    _XWidgetImpl(XWindow& xWindow);

    XWindow& m_xWindow;
};

class XWindow : /*public GUI::Widget,*/ public XDrawable {
    friend _XWidgetImpl;
    C_OBJECT(XWindow)
public:
    XLib::Window id() const {
        return m_id;
    }

    long event_mask() const { return m_event_mask; }
    void event_mask(long mask);

    XWindow* parent_window();

    GUI::Painter& painter() override { return m_painter; }

    AK::NonnullRefPtr<_XWidgetImpl> widget() { return m_widget; }

    AK::RefPtr<Gfx::Bitmap> bitmap() override { return m_bitmap;}

private:
    XWindow(XLib::Display* display, RefPtr<GUI::Window> host_window, Gfx::IntRect frame);

    XLib::Window m_id;
    XLib::Display * m_display;

    long m_event_mask;

    AK::RefPtr<GUI::Window> m_window;

    AK::NonnullRefPtr<Gfx::Bitmap> m_bitmap;
    GUI::Painter m_painter;

    AK::NonnullRefPtr<_XWidgetImpl> m_widget;
};