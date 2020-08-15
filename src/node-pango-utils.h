#ifndef __NODE_PANGO_UTILS_H__
#define __NODE_PANGO_UTILS_H__

#include <napi.h>

Napi::Object
InitPangoUtils(Napi::Env env, Napi::Object exports);

Napi::Value
MarkupEscapeText(const Napi::CallbackInfo& info);

#endif