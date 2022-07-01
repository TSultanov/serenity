/*
* Copyright 2021, Haiku, Inc. All rights reserved.
* Distributed under the terms of the MIT license.
*/

#include <AK/ScopeGuard.h>
#include <AK/HashMap.h>
#include <AK/String.h>

#include <pthread.h>
#include <cstring>

namespace XLib {
extern "C" {
#define register
#include <X11/Xlib.h>
#include <X11/Xresource.h>

#include "xorg/Xlcint.h"
#include "xorg/Xresinternal.h"
#undef register
}
}

using namespace XLib;

static pthread_rwlock_t sQuarksLock;
static AK::HashMap<XrmQuark, AK::String> sQuarksToStrings;
static AK::HashMap<AK::String, XrmQuark> sStringsToQuarks;
static XrmQuark sLastQuark = 1;

extern "C" XrmQuark
XLib::XrmUniqueQuark()
{
   pthread_rwlock_wrlock(&sQuarksLock);
   AK::ScopeGuard([]() { pthread_rwlock_unlock(&sQuarksLock); });
   return sLastQuark++;
}

extern "C" XrmString
XLib::XrmQuarkToString(XrmQuark quark)
{
   pthread_rwlock_rdlock(&sQuarksLock);
   AK::ScopeGuard([]() { pthread_rwlock_unlock(&sQuarksLock); });

   Optional<AK::String> result = sQuarksToStrings.get(quark);
   if (!result.has_value())
       return NULL;

   return strdup(result.value().characters());
}

extern "C" XrmQuark
XLib::_XrmInternalStringToQuark(const char* name, int len, Signature /*sig*/, Bool /*permstring*/)
{
   if (!name)
       return 0;

   pthread_rwlock_rdlock(&sQuarksLock);
   AK::ScopeGuard([]() { pthread_rwlock_unlock(&sQuarksLock); });
   const AK::String string(name, len < 0 ? strlen(name) : len);
   const auto result = sStringsToQuarks.get(string);
   if (result.has_value())
       return result.value();

   pthread_rwlock_unlock(&sQuarksLock);

   XrmQuark quark = XrmUniqueQuark();
   pthread_rwlock_wrlock(&sQuarksLock);
   AK::ScopeGuard([]() { pthread_rwlock_unlock(&sQuarksLock); });
   sQuarksToStrings.set(quark, string);
   sStringsToQuarks.set(string, quark);
   return quark;
}

extern "C" XrmQuark
XLib::XrmStringToQuark(const char* string)
{
   return _XrmInternalStringToQuark(string, -1, -1, False);
}

extern "C" XrmQuark
XLib::XrmPermStringToQuark(const char* string)
{
   return _XrmInternalStringToQuark(string, -1, -1, True);
}

extern "C" XrmMethods
XLib::_XrmInitParseInfo(XPointer* /*state*/)
{
   return NULL;
}
