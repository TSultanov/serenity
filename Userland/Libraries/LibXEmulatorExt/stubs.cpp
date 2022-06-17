#include <X11/Xlib.h>
//#include <X11/extensions/xex>

extern "C" {

void* XextFindDisplay(void* /*extinfo*/, Display* /*dpy*/);

void* XextFindDisplay(void* /*extinfo*/, Display* /*dpy*/)
{
    return NULL;
}
}