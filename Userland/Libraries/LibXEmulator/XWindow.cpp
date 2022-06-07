#include "XWindow.h"
#include "ObjectManager.h"

XWindow::XWindow(XLib::Display* display, Gfx::IntRect frame) :
    m_id(ObjectManager::the().add_window(this)),
    m_display(display), m_painter(*this)
{
    set_relative_rect(frame);
}

void XWindow::create_host_window() {
    m_window = GUI::Window::construct();
    m_window->set_main_widget(this);
}

void XWindow::event_mask(long mask)
{
    m_event_mask = mask;
}

XWindow* XWindow::parent_window()
{
    return dynamic_cast<XWindow*>(this->parent());
}

void XWindow::paint_event(GUI::PaintEvent&)
{
    GUI::Painter painter_1(*this);
}