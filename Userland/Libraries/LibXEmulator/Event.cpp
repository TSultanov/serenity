#include "ObjectManager.h"
#include "XWindow.h"

namespace XLib {
extern "C" {
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
}
}

using namespace XLib;

extern "C" int
XSelectInput(Display* /*display*/, Window w, long mask)
{
    auto window = ObjectManager::the().get_window(w);
    if (window.is_null())
        return BadWindow;
    window->event_mask(mask);
    return Success;
}