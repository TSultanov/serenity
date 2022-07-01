/*
* Copyright 2021, Haiku, Inc. All rights reserved.
* Distributed under the terms of the MIT license.
*/
#include <AK/HashMap.h>
#include <AK/Format.h>
#include "Extension.h"

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#undef register
}
}

#define UNIMPLEMENTED() dbgln("Extensions: {}", __func__)

static int sLastExtension = 1;

static AK::HashMap<int, XLib::_XExtension*> sExtensions;

void
_x_extensions_close(XLib::Display* dpy)
{
   for (const auto& it : sExtensions) {
       if (it.value->close_display)
           it.value->close_display(dpy, &it.value->codes);
   }
   sExtensions.clear();
}

extern "C" XLib::XExtCodes*
XLib::XAddExtension(Display* /*dpy*/)
{
       const int id = sLastExtension++;
   _XExtension* extension = new _XExtension;
   extension->codes.extension = id;

   // arbitrary
   extension->codes.major_opcode = id;
   extension->codes.first_event = id * 100000;
   extension->codes.first_error = id * 100000;
   sExtensions.set(id, extension);
   return &extension->codes;
}

extern "C" XLib::CloseDisplayType
XLib::XESetCloseDisplay(Display* /*dpy*/, int extension_id, CloseDisplayType proc)
{
   const auto& ext = sExtensions.get(extension_id);
   if (!ext.has_value())
       return NULL;

   CloseDisplayType last = ext.value()->close_display;
   ext.value()->close_display = proc;
   return last;
}

extern "C" Bool
XLib::XQueryExtension(Display* /*display*/, const char* /*name*/,
   int* /*major_opcode_return*/, int* /*first_event_return*/, int* /*first_error_return*/)
{
   UNIMPLEMENTED();
   return 0;
}

extern "C" char**
XLib::XListExtensions(Display* /*dpy*/, int* /*nextensions_return*/)
{
   UNIMPLEMENTED();
   return NULL;
}

extern "C" int
XLib::XFreeExtensionList(char** /*list*/)
{
   return Success;
}
