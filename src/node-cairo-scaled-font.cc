#include "node-cairo-scaled-font.h"
#include "node-cairo-font-face.h"
#include "node-cairo-font-options.h"
#include "node-cairo-utils.h"

using namespace std;

static Napi::FunctionReference* scaledFontConstructor =
  new Napi::FunctionReference();

Napi::Object
CairoScaledFont::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "CairoScaledFont",
    {
      StaticMethod("fontCreate", &CairoScaledFont::Create),
      InstanceMethod("reference", &CairoScaledFont::Reference),
      InstanceMethod("destroy", &CairoScaledFont::Destroy),
      InstanceMethod("status", &CairoScaledFont::Status),
      InstanceMethod("extents", &CairoScaledFont::Extents),
      InstanceMethod("textExtents", &CairoScaledFont::TextExtents),
      InstanceMethod("glyphExtents", &CairoScaledFont::GlyphExtents),
      InstanceMethod("textToGlyphs", &CairoScaledFont::TextToGlyphs),
      InstanceMethod("getFontFace", &CairoScaledFont::GetFontFace),
      InstanceMethod("getFontOptions", &CairoScaledFont::GetFontOptions),
      InstanceMethod("getFontMatrix", &CairoScaledFont::GetFontMatrix),
      InstanceMethod("getCtm", &CairoScaledFont::GetCtm),
      InstanceMethod("getScaleMatrix", &CairoScaledFont::GetScaleMatrix),
      InstanceMethod("getType", &CairoScaledFont::GetType),
      InstanceMethod("getReferenceCount", &CairoScaledFont::GetReferenceCount),
      InstanceMethod("setUserData", &CairoScaledFont::SetUserData),
      InstanceMethod("getUserData", &CairoScaledFont::GetUserData),
    });
  *scaledFontConstructor = Napi::Persistent(func);
  exports.Set("CairoScaledFont", func);
  return exports;
}

CairoScaledFont::CairoScaledFont(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoScaledFont>(info)
{
  this->scaledFont_ = nullptr;
}

CairoScaledFont::~CairoScaledFont()
{
  if (this->scaledFont_) {
    cairo_scaled_font_destroy(this->scaledFont_);
    this->scaledFont_ = nullptr;
  }
}

Napi::Object
CairoScaledFont::NewInstance(cairo_scaled_font_t* scaledFont)
{
  Napi::Object obj = scaledFontConstructor->New({});
  CairoScaledFont* sf = Napi::ObjectWrap<CairoScaledFont>::Unwrap(obj);
  sf->SetScaledFont(scaledFont);
  return obj;
}

bool
CairoScaledFont::HasInstance(const Napi::Value& value)
{
  if (!value.IsObject()) {
    return false;
  }
  return value.As<Napi::Object>().InstanceOf(scaledFontConstructor->Value());
}

cairo_scaled_font_t*
CairoScaledFont::GetScaledFont()
{
  return this->scaledFont_;
}

void
CairoScaledFont::SetScaledFont(cairo_scaled_font_t* scaledFont)
{
  this->scaledFont_ = scaledFont;
}

Napi::Value
CairoScaledFont::Create(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 4)) {
    return env.Undefined();
  }
  if (!CairoFontFace::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid font face.");
  }
  CairoFontFace* face =
    Napi::ObjectWrap<CairoFontFace>::Unwrap(info[0].As<Napi::Object>());
  if (!ParamIsMatrix(env, "font matrix", info[1]) ||
      !ParamIsMatrix(env, "ctm", info[2])) {
    return env.Undefined();
  }
  cairo_matrix_t fontMatrix, ctm;
  ObjectToMatrix(info[1].As<Napi::Object>(), &fontMatrix);
  ObjectToMatrix(info[2].As<Napi::Object>(), &ctm);
  if (!CairoFontOptions::HasInstance(info[3])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid font options.");
  }
  CairoFontOptions* options =
    Napi::ObjectWrap<CairoFontOptions>::Unwrap(info[3].As<Napi::Object>());
  cairo_scaled_font_t* sf = cairo_scaled_font_create(
    face->GetFontFace(), &fontMatrix, &ctm, options->GetOptions());
  cairo_status_t status = cairo_scaled_font_status(sf);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create scaled font.", status);
  }
  return CairoScaledFont::NewInstance(sf);
}

Napi::Value
CairoScaledFont::Reference(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_scaled_font_reference(this->scaledFont_);
  return info.This();
}

Napi::Value
CairoScaledFont::Destroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_scaled_font_destroy(this->scaledFont_);
  return info.This();
}

Napi::Value
CairoScaledFont::Status(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_status_t status = cairo_scaled_font_status(this->scaledFont_);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoScaledFont::Extents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_extents_t extents;
  cairo_scaled_font_extents(this->scaledFont_, &extents);
  Napi::Object result;
  FontExtentsToObject(env, extents, &result);
  return result;
}

Napi::Value
CairoScaledFont::TextExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "text", info[0])) {
    return env.Undefined();
  }
  string text = info[0].As<Napi::String>();
  cairo_text_extents_t extents;
  cairo_scaled_font_text_extents(this->scaledFont_, text.c_str(), &extents);
  Napi::Object result;
  TextExtentsToObject(env, &extents, &result);
  return result;
}

Napi::Value
CairoScaledFont::GlyphExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsArray(env, "glyphs", info[0])) {
    return env.Undefined();
  }
  Napi::Array arr = info[0].As<Napi::Array>();
  vector<cairo_glyph_t> glyphs;
  for (uint32_t i = 0; i < arr.Length(); i++) {
    cairo_glyph_t glyph;
    ObjectToGlyph(arr.Get(i).As<Napi::Object>(), &glyph);
    glyphs.push_back(glyph);
  }
  cairo_text_extents_t extents;
  cairo_scaled_font_glyph_extents(
    this->scaledFont_, glyphs.data(), glyphs.size(), &extents);
  Napi::Object result;
  TextExtentsToObject(env, &extents, &result);
  return result;
}

Napi::Value
CairoScaledFont::TextToGlyphs(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1]) ||
      !ParamIsString(env, "text", info[2])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  string text = info[2].As<Napi::String>();
  cairo_glyph_t** glyphs = nullptr;
  int glyphsNum;
  cairo_text_cluster_t* clusters = nullptr;
  int* clustersNum = nullptr;
  cairo_text_cluster_flags_t* clusterFlags = nullptr;
  cairo_status_t status = cairo_scaled_font_text_to_glyphs(this->scaledFont_,
                                                           x,
                                                           y,
                                                           text.c_str(),
                                                           text.length(),
                                                           glyphs,
                                                           &glyphsNum,
                                                           &clusters,
                                                           clustersNum,
                                                           clusterFlags);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to text to glyphs.", status);
  }
  Napi::Object result;
  Napi::Array glyphArr;
  for (int i = 0; i < glyphsNum; i++) {
    Napi::Object g;
    GlyphToObject(env, *glyphs[i], &g);
    glyphArr.Set(i, g);
  }
  result.Set("glyphs", glyphArr);
  if (clusters == nullptr) {
    result.Set("clusters", env.Null());
  } else {
    Napi::Array clusterArr;
    for (int i = 0; i < *clustersNum; i++) {
      Napi::Object c;
      TextClusterToObject(env, clusters[i], &c);
      clusterArr.Set(i, c);
    }
    result.Set("clusters", clusterArr);
  }
  result.Set("clusterFlags",
             clusterFlags == nullptr ? env.Null()
                                     : Napi::Number::New(env, *clusterFlags));
  return result;
}

Napi::Value
CairoScaledFont::GetFontFace(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_face_t* face = cairo_scaled_font_get_font_face(this->scaledFont_);
  cairo_status_t status = cairo_font_face_status(face);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get font face.", status);
  }
  return CairoFontFace::NewInstance(face);
}

Napi::Value
CairoScaledFont::GetFontOptions(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_options_t* options = cairo_font_options_create();
  cairo_scaled_font_get_font_options(this->scaledFont_, options);
  cairo_status_t status = cairo_font_options_status(options);
  if (status) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get font options.", status);
  }
  return CairoFontOptions::NewInstance(options);
}

Napi::Value
CairoScaledFont::GetFontMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  cairo_scaled_font_get_font_matrix(this->scaledFont_, &matrix);
  Napi::Object result;
  MatrixToObject(env, matrix, &result);
  return result;
}

Napi::Value
CairoScaledFont::GetCtm(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  cairo_scaled_font_get_ctm(this->scaledFont_, &matrix);
  Napi::Object result;
  MatrixToObject(env, matrix, &result);
  return result;
}

Napi::Value
CairoScaledFont::GetScaleMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  cairo_scaled_font_get_scale_matrix(this->scaledFont_, &matrix);
  Napi::Object result;
  MatrixToObject(env, matrix, &result);
  return result;
}

Napi::Value
CairoScaledFont::GetType(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_type_t type = cairo_scaled_font_get_type(this->scaledFont_);
  return Napi::Number::New(env, type);
}

Napi::Value
CairoScaledFont::GetReferenceCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  unsigned int count = cairo_scaled_font_get_reference_count(this->scaledFont_);
  return Napi::Number::New(env, count);
}

Napi::Value
CairoScaledFont::SetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoScaledFont::GetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}