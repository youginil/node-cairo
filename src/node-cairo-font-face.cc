#include "node-cairo-font-face.h"
#include "node-cairo-utils.h"

using namespace std;

static Napi::FunctionReference* fontFaceConstructor =
  new Napi::FunctionReference();

Napi::Object
CairoFontFace::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "CairoFontFace",
    {
      InstanceMethod("reference", &CairoFontFace::Reference),
      InstanceMethod("destroy", &CairoFontFace::Destroy),
      InstanceMethod("status", &CairoFontFace::Status),
      InstanceMethod("getType", &CairoFontFace::GetType),
      InstanceMethod("getReferenceCount", &CairoFontFace::GetReferenceCount),
      InstanceMethod("setUserData", &CairoFontFace::SetUserData),
      InstanceMethod("getUserData", &CairoFontFace::GetUserData),
      StaticMethod("toyFontFaceCreate", &CairoFontFace::ToyFontFaceCreate),
      InstanceMethod("toyFontFaceGetFamily",
                     &CairoFontFace::ToyFontFaceGetFamily),
      InstanceMethod("toyFontFaceGetSlant",
                     &CairoFontFace::ToyFontFaceGetSlant),
      InstanceMethod("toyFontFaceGetWeight",
                     &CairoFontFace::ToyFontFaceGetWeight),
    });
  *fontFaceConstructor = Napi::Persistent(func);
  exports.Set("CairoFontFace", func);
  return exports;
}

CairoFontFace::CairoFontFace(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoFontFace>(info)
{
  this->fontFace_ = nullptr;
}

CairoFontFace::~CairoFontFace()
{
  if (this->fontFace_) {
    cairo_font_face_destroy(this->fontFace_);
    this->fontFace_ = nullptr;
  }
}

Napi::Object
CairoFontFace::NewInstance(cairo_font_face_t* fontFace)
{
  Napi::Object obj = fontFaceConstructor->New({});
  CairoFontFace* ff = Napi::ObjectWrap<CairoFontFace>::Unwrap(obj);
  ff->SetFontFace(fontFace);
  return obj;
}

bool
CairoFontFace::HasInstance(const Napi::Value& value)
{
  if (!value.IsObject()) {
    return false;
  }
  return value.As<Napi::Object>().InstanceOf(fontFaceConstructor->Value());
}

cairo_font_face_t*
CairoFontFace::GetFontFace()
{
  return this->fontFace_;
}

void
CairoFontFace::SetFontFace(cairo_font_face_t* fontFace)
{
  this->fontFace_ = fontFace;
}

Napi::Value
CairoFontFace::Reference(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_face_reference(this->fontFace_);
  return info.This();
}

Napi::Value
CairoFontFace::Destroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  if (this->fontFace_) {
    cairo_font_face_destroy(this->fontFace_);
    this->fontFace_ = nullptr;
  }
  return info.This();
}

Napi::Value
CairoFontFace::Status(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_status_t status = cairo_font_face_status(this->fontFace_);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoFontFace::GetType(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_type_t type = cairo_font_face_get_type(this->fontFace_);
  return Napi::Number::New(env, type);
}

Napi::Value
CairoFontFace::GetReferenceCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  unsigned int count = cairo_font_face_get_reference_count(this->fontFace_);
  return Napi::Number::New(env, count);
}

Napi::Value
CairoFontFace::SetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoFontFace::GetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoFontFace::ToyFontFaceCreate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "font family", info[0]) ||
      !ParamIsNumber(env, "font slant", info[1]) ||
      !ParamIsNumber(env, "font weight", info[2])) {
    return env.Undefined();
  }
  string family = info[0].As<Napi::String>();
  int slant = info[1].As<Napi::Number>();
  int weight = info[2].As<Napi::Number>();
  cairo_font_face_t* face = cairo_toy_font_face_create(
    family.c_str(), (cairo_font_slant_t)slant, (cairo_font_weight_t)weight);
  return CairoFontFace::NewInstance(face);
}

Napi::Value
CairoFontFace::ToyFontFaceGetFamily(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  const char* family = cairo_toy_font_face_get_family(this->fontFace_);
  return Napi::String::New(env, family);
}

Napi::Value
CairoFontFace::ToyFontFaceGetSlant(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_slant_t slant = cairo_toy_font_face_get_slant(this->fontFace_);
  return Napi::Number::New(env, slant);
}

Napi::Value
CairoFontFace::ToyFontFaceGetWeight(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_weight_t weight = cairo_toy_font_face_get_weight(this->fontFace_);
  return Napi::Number::New(env, weight);
}