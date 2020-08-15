#ifndef __NODE_CAIRO_FONT_OPTIONS_H__
#define __NODE_CAIRO_FONT_OPTIONS_H__

#include "cairo.h"
#include <napi.h>

class CairoFontOptions : public Napi::ObjectWrap<CairoFontOptions>
{
public:
  CairoFontOptions(const Napi::CallbackInfo& info);
  ~CairoFontOptions();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_font_options_t* options);
  static bool HasInstance(const Napi::Value& v);

  cairo_font_options_t* GetOptions();
  void SetOptions(cairo_font_options_t* options);

  Napi::Value SetAntialias(const Napi::CallbackInfo& info);

private:
  cairo_font_options_t* options_;
};

#endif