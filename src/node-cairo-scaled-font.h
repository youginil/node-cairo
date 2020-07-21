#ifndef __NODE_CAIRO_SCALED_FONT_H__
#define __NODE_CAIRO_SCALED_FONT_H__

#include "cairo.h"
#include <napi.h>

class CairoScaledFont : public Napi::ObjectWrap<CairoScaledFont>
{
public:
  CairoScaledFont(const Napi::CallbackInfo& info);
  ~CairoScaledFont();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_scaled_font_t* scaledFont);
  static bool HasInstance(const Napi::Value& value);

  cairo_scaled_font_t* GetScaledFont();
  void SetScaledFont(cairo_scaled_font_t* scaledFont);

  static Napi::Value Create(const Napi::CallbackInfo& info);
  Napi::Value Reference(const Napi::CallbackInfo& info);
  Napi::Value Destroy(const Napi::CallbackInfo& info);
  Napi::Value Status(const Napi::CallbackInfo& info);
  Napi::Value Extents(const Napi::CallbackInfo& info);
  Napi::Value TextExtents(const Napi::CallbackInfo& info);
  Napi::Value GlyphExtents(const Napi::CallbackInfo& info);
  Napi::Value TextToGlyphs(const Napi::CallbackInfo& info);
  Napi::Value GetFontFace(const Napi::CallbackInfo& info);
  Napi::Value GetFontOptions(const Napi::CallbackInfo& info);
  Napi::Value GetFontMatrix(const Napi::CallbackInfo& info);
  Napi::Value GetCtm(const Napi::CallbackInfo& info);
  Napi::Value GetScaleMatrix(const Napi::CallbackInfo& info);
  Napi::Value GetType(const Napi::CallbackInfo& info);
  Napi::Value GetReferenceCount(const Napi::CallbackInfo& info);
  Napi::Value SetUserData(const Napi::CallbackInfo& info);
  Napi::Value GetUserData(const Napi::CallbackInfo& info);

private:
  cairo_scaled_font_t* scaledFont_;
};

#endif