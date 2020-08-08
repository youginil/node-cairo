#include "node-pango-enum.h"
#include <pango/pangocairo.h>

Napi::Object
InitPangoEnums(Napi::Env env, Napi::Object exports)
{
  Napi::Object wrap = Napi::Object::New(env);
  wrap.Set("WORD", Napi::Number::New(env, PANGO_WRAP_WORD));
  wrap.Set("CHAR", Napi::Number::New(env, PANGO_WRAP_CHAR));
  wrap.Set("WORD_CHAR", Napi::Number::New(env, PANGO_WRAP_WORD_CHAR));
  exports.Set("PangoWrapMode", wrap);

  Napi::Object ellipsize = Napi::Object::New(env);
  ellipsize.Set("NONE", Napi::Number::New(env, PANGO_ELLIPSIZE_NONE));
  ellipsize.Set("START", Napi::Number::New(env, PANGO_ELLIPSIZE_START));
  ellipsize.Set("MIDDLE", Napi::Number::New(env, PANGO_ELLIPSIZE_MIDDLE));
  ellipsize.Set("END", Napi::Number::New(env, PANGO_ELLIPSIZE_END));
  exports.Set("PangoEllipsizeMode", ellipsize);

  Napi::Object align = Napi::Object::New(env);
  align.Set("LEFT", Napi::Number::New(env, PANGO_ALIGN_LEFT));
  align.Set("CENTER", Napi::Number::New(env, PANGO_ALIGN_CENTER));
  align.Set("RIGHT", Napi::Number::New(env, PANGO_ALIGN_RIGHT));
  exports.Set("PangoAlignment", align);
  
  return exports;
}