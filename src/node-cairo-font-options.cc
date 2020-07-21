#include "node-cairo-font-options.h"

Napi::FunctionReference* fontOptionsConstructor = new Napi::FunctionReference();

Napi::Object
CairoFontOptions::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(env, "CairoFontOptions", {});
  *fontOptionsConstructor = Napi::Persistent(func);
  exports.Set("CairoFontOptions", func);
  return exports;
}

CairoFontOptions::CairoFontOptions(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoFontOptions>(info)
{
  this->options_ = nullptr;
}

CairoFontOptions::~CairoFontOptions()
{
  if (this->options_) {
    cairo_font_options_destroy(this->options_);
    this->options_ = nullptr;
  }
}

Napi::Object
CairoFontOptions::NewInstance(cairo_font_options_t* options)
{
  Napi::Object obj = fontOptionsConstructor->New({});
  CairoFontOptions* fontOptions =
    Napi::ObjectWrap<CairoFontOptions>::Unwrap(obj);
  fontOptions->SetOptions(options);
  return obj;
}

bool
CairoFontOptions::HasInstance(const Napi::Value& v)
{
  return v.IsObject() &&
         v.As<Napi::Object>().InstanceOf(fontOptionsConstructor->Value());
}

cairo_font_options_t*
CairoFontOptions::GetOptions()
{
  return this->options_;
}

void
CairoFontOptions::SetOptions(cairo_font_options_t* options)
{
  this->options_ = options;
}
