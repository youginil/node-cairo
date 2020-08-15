#include "node-pango-utils.h"
#include "node-cairo-utils.h"
#include <pango/pangocairo.h>

using namespace std;

Napi::Object
InitPangoUtils(Napi::Env env, Napi::Object exports)
{
  exports.Set("markupEscapeText", Napi::Function::New(env, MarkupEscapeText));
  return exports;
}

Napi::Value
MarkupEscapeText(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsString(info[0], "text", env)) {
    return env.Undefined();
  }
  string text = info[0].As<Napi::String>();
  gchar* result = g_markup_escape_text(text.c_str(), text.length());
  return Napi::String::New(env, result);
}