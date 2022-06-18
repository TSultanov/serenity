#include <AK/Format.h>

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#undef register
}
}

int (*XLib::XSynchronize(Display*, Bool))(Display*)
{
    dbgln("Stub: XSynchronize");
    return nullptr;
}
