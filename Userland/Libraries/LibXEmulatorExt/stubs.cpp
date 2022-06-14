#include <X11/Xlib.h>
//#include <X11/extensions/extutil.h>

extern "C" {

void* XextFindDisplay(void* /*extinfo*/, Display* /*dpy*/)
{
    return NULL;
}
}