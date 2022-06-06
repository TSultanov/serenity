#include "ObjectManager.h"

ObjectManager& ObjectManager::the()
{
    static ObjectManager obj;
    return obj;
}

AK::RefPtr<XWindow> ObjectManager::get_window(XLib::Window xlib_window) const
{
    if(m_windows.contains(static_cast<XLib::XID>(xlib_window)))
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