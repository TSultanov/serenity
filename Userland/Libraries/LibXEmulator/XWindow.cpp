#include "XWindow.h"
#include "ObjectManager.h"

XWindow::XWindow(XLib::Display* display, Gfx::IntRect frame) :
    m_id(ObjectManager::the().add_window(this)),
    m_display(display)
{
    set_relative_rect(frame);
}

void XWindow::create_host_window() {
    m_window = GUI::Window::construct();
    m_window->set_main_widget(this);
}

void
XWindow::event_mask(long mask)
{
    m_event_mask = mask;
}