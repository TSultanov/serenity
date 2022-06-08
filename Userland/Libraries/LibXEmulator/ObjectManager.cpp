#include "ObjectManager.h"

ObjectManager& ObjectManager::the()
{
    static ObjectManager obj;
    return obj;
}

AK::RefPtr<XWindow> ObjectManager::get_window(XLib::Window xlib_window) const
{
    if(m_windows.contains(xlib_window))
        return m_windows.get(xlib_window).value();

    return nullptr;
}

XLib::Window ObjectManager::add_window(AK::RefPtr<XWindow> window)
{
    auto xid = next_xid();
    m_windows.set(xid, window);
    return xid;
}

void ObjectManager::remove_window(XLib::Window xlib_window)
{
    m_windows.remove(xlib_window);
}

AK::RefPtr<XPixmap> ObjectManager::get_pixmap(XLib::Pixmap xlib_pixmap) const
{
    if(m_pixmaps.contains(xlib_pixmap))
        return m_pixmaps.get(xlib_pixmap).value();

    return nullptr;
}

XLib::Pixmap ObjectManager::add_pixmap(AK::RefPtr<XPixmap> pixmap)
{
    auto xid = next_xid();
    m_pixmaps.set(xid, pixmap);
    return xid;
}

void ObjectManager::remove_pixmap(XLib::Pixmap xlib_pixmap)
{
    m_pixmaps.remove(xlib_pixmap);
}