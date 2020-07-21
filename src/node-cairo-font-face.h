#ifndef __NODE_CAIRO_FONT_FACE_H__
#define __NODE_CAIRO_FONT_FACE_H__

#include "cairo.h"
#include <napi.h>

class CairoFontFace : public Napi::ObjectWrap<CairoFontFace>
{
public:
  CairoFontFace(const Napi::CallbackInfo& info);
  ~CairoFontFace();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_font_face_t* fontFace);
  static bool HasInstance(const Napi::Value& value);

  cairo_font_face_t* GetFontFace();
  void SetFontFace(cairo_font_face_t* fontFace);

  Napi::Value Reference(const Napi::CallbackInfo& info);
  Napi::Value Destroy(const Napi::CallbackInfo& info);
  Napi::Value Status(const Napi::CallbackInfo& info);
  Napi::Value GetType(const Napi::CallbackInfo& info);
  Napi::Value GetReferenceCount(const Napi::CallbackInfo& info);
  Napi::Value SetUserData(const Napi::CallbackInfo& info);
  Napi::Value GetUserData(const Napi::CallbackInfo& info);
  static Napi::Value ToyFontFaceCreate(const Napi::CallbackInfo& info);
  Napi::Value ToyFontFaceGetFamily(const Napi::CallbackInfo& info);
  Napi::Value ToyFontFaceGetSlant(const Napi::CallbackInfo& info);
  Napi::Value ToyFontFaceGetWeight(const Napi::CallbackInfo& info);

private:
  cairo_font_face_t* fontFace_;
};

#endif