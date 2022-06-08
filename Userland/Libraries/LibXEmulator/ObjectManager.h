#pragma once

#include "Undef.h"
#include <AK/HashMap.h>
#include <LibCore/Object.h>
#include "XWindow.h"
#include "XPixmap.h"

namespace XLib {
extern "C" {
#include "X11/Xlib.h"
}
}

class ObjectManager {
public:
    static ObjectManager& the();
    ObjectManager() = default;

    AK::RefPtr<XWindow> get_window(XLib::Window xlib_window) const;
    XLib::Window add_window(AK::RefPtr<XWindow> window);
    void remove_window(XLib::Window xlib_window);

    AK::RefPtr<XPixmap> get_pixmap(XLib::Pixmap xlib_pixmap) const;
    XLib::Pixmap add_pixmap(AK::RefPtr<XPixmap> pixmap);
    void remove_pixmap(XLib::Pixmap xlib_pixmap);
private:
    XLib::XID next_xid() {
        static XLib::XID xid{0};
        return xid++;
    }

    AK::HashMap<XLib::XID, AK::RefPtr<XWindow>> m_windows;
    AK::HashMap<XLib::XID, AK::RefPtr<XPixmap>> m_pixmaps;
};
