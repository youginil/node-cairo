#include "node-cairo-surface.h"
#include "cairo-pdf.h"
#include "cairo-script.h"
#include "cairo-svg.h"
#include "node-cairo-font-options.h"
#include "node-cairo-utils.h"
#include <set>

using namespace std;

static set<string> mimes = {
  CAIRO_MIME_TYPE_JPEG,         CAIRO_MIME_TYPE_PNG,
  CAIRO_MIME_TYPE_JP2,          CAIRO_MIME_TYPE_URI,
  CAIRO_MIME_TYPE_UNIQUE_ID,    CAIRO_MIME_TYPE_JBIG2,
  CAIRO_MIME_TYPE_JBIG2_GLOBAL, CAIRO_MIME_TYPE_JBIG2_GLOBAL_ID,
  CAIRO_MIME_TYPE_CCITT_FAX,    CAIRO_MIME_TYPE_CCITT_FAX_PARAMS,
};

static Napi::FunctionReference* surfaceConstructor =
  new Napi::FunctionReference();

Napi::Object
CairoSurface::Init(Napi::Env env, Napi::Object exports)
{
  // register class
  Napi::Function func = DefineClass(
    env,
    "CairoSurface",
    {
      InstanceMethod("createSimilar", &CairoSurface::CreateSimilar),
      InstanceMethod("createSimilarImage", &CairoSurface::CreateSimilarImage),
      InstanceMethod("createForRectangle", &CairoSurface::CreateForRectangle),
      InstanceMethod("reference", &CairoSurface::Reference),
      InstanceMethod("destroy", &CairoSurface::Destroy),
      InstanceMethod("status", &CairoSurface::Status),
      InstanceMethod("finish", &CairoSurface::Finish),
      InstanceMethod("flush", &CairoSurface::Flush),
      InstanceMethod("getDevice", &CairoSurface::GetDevice),
      InstanceMethod("getFontOptions", &CairoSurface::GetFontOptions),
      InstanceMethod("getContent", &CairoSurface::GetContent),
      InstanceMethod("markDirty", &CairoSurface::MarkDirty),
      InstanceMethod("markDirtyRectangle", &CairoSurface::MarkDirtyRectangle),
      InstanceMethod("setDeviceOffset", &CairoSurface::SetDeviceOffset),
      InstanceMethod("getDeviceOffset", &CairoSurface::GetDeviceOffset),
      InstanceMethod("getDeviceScale", &CairoSurface::GetDeviceScale),
      InstanceMethod("setDeviceScale", &CairoSurface::SetDeviceScale),
      InstanceMethod("setFallbackResolution",
                     &CairoSurface::SetFallbackResolution),
      InstanceMethod("getFallbackResolution",
                     &CairoSurface::GetFallbackResolution),
      InstanceMethod("getType", &CairoSurface::GetType),
      InstanceMethod("getReferenceCount", &CairoSurface::GetReferenceCount),
      InstanceMethod("setUserData", &CairoSurface::SetUserData),
      InstanceMethod("getUserData", &CairoSurface::GetUserData),
      InstanceMethod("copyPage", &CairoSurface::CopyPage),
      InstanceMethod("showPage", &CairoSurface::ShowPage),
      InstanceMethod("hasShowTextGlyphs", &CairoSurface::HasShowTextGlyphs),
      InstanceMethod("setMimeData", &CairoSurface::SetMimeData),
      InstanceMethod("getMimeData", &CairoSurface::GetMimeData),
      InstanceMethod("supportsMimeType", &CairoSurface::SupportsMimeType),
      InstanceMethod("mapToImage", &CairoSurface::MapToImage),
      StaticMethod("formatStrideForWidth", &CairoSurface::FormatStrideForWidth),
      StaticMethod("imageSurfaceCreate", &CairoSurface::ImageSurfaceCreate),
      StaticMethod("imageSurfaceCreateForData",
                   &CairoSurface::ImageSurfaceCreateForData),
      InstanceMethod("imageSurfaceGetData", &CairoSurface::ImageSurfaceGetData),
      InstanceMethod("imageSurfaceGetdata", &CairoSurface::ImageSurfaceGetData),
      InstanceMethod("imageSurfaceGetFormat",
                     &CairoSurface::ImageSurfaceGetFormat),
      InstanceMethod("imageSurfaceGetWidth",
                     &CairoSurface::ImageSurfaceGetWidth),
      InstanceMethod("imageSurfaceGetHeight",
                     &CairoSurface::ImageSurfaceGetHeight),
      InstanceMethod("imageSurfaceGetStride",
                     &CairoSurface::ImageSurfaceGetStride),
      StaticMethod("pdfSurfaceCreate", &CairoSurface::PdfSurfaceCreate),
      StaticMethod("pdfSurfaceCreateForStream",
                   &CairoSurface::PdfSurfaceCreateForStream),
      InstanceMethod("pdfSurfaceRestrictToVersion",
                     &CairoSurface::PdfSurfaceRestrictToVersion),
      StaticMethod("pdfGetVersions", &CairoSurface::PdfGetVersions),
      StaticMethod("pdfVersionToString", &CairoSurface::PdfVersionToString),
      InstanceMethod("pdfSurfaceSetSize", &CairoSurface::PdfSurfaceSetSize),
      InstanceMethod("pdfSurfaceAddOutline",
                     &CairoSurface::PdfSurfaceAddOutline),
      InstanceMethod("pdfSurfaceSetMetadata",
                     &CairoSurface::PdfSurfaceSetMetadata),
      InstanceMethod("pdfSurfaceSetPageLabel",
                     &CairoSurface::PdfSurfaceSetPageLabel),
      InstanceMethod("pdfSurfaceSetThumbnailSize",
                     &CairoSurface::PdfSurfaceSetThumbnailSize),
      StaticMethod("imageSurfaceCreateFromPng",
                   &CairoSurface::ImageSurfaceCreateFromPng),
      StaticMethod("imageSurfaceCreateFromPngStream",
                   &CairoSurface::ImageSurfaceCreateFromPngStream),
      InstanceMethod("writeToPng", &CairoSurface::WriteToPng),
      InstanceMethod("writeToPngStream", &CairoSurface::WriteToPngStream),
      StaticMethod("recordingSurfaceCreate",
                   &CairoSurface::RecordingSurfaceCreate),
      InstanceMethod("recordingSurfaceInkExtents",
                     &CairoSurface::RecordingSurfaceInkExtents),
      InstanceMethod("recordingSurfaceGetExtents",
                     &CairoSurface::RecordingSurfaceGetExtents),
      StaticMethod("svgSurfaceCreate", &CairoSurface::SvgSurfaceCreate),
      StaticMethod("svgSurfaceCreateForStream",
                   &CairoSurface::SvgSurfaceCreateForStream),
      InstanceMethod("svgSurfaceGetDocumentUnit",
                     &CairoSurface::SvgSurfaceGetDocumentUnit),
      InstanceMethod("svgSurfaceSetDocumentUnit",
                     &CairoSurface::SvgSurfaceSetDocumentUnit),
      InstanceMethod("svgSurfaceRestrictToVersion",
                     &CairoSurface::SvgSurfaceRestrictToVersion),
      StaticMethod("svgGetVersions", &CairoSurface::SvgGetVersions),
      StaticMethod("svgVersionToString", &CairoSurface::SvgVersionToString),
      InstanceMethod("scriptFromRecordingSurface",
                     &CairoSurface::ScriptFromRecordingSurface),
      StaticMethod("scriptSurfaceCreate", &CairoSurface::ScriptSurfaceCreate),
      StaticMethod("scriptSurfaceCreateForTarget",
                   &CairoSurface::ScriptSurfaceCreateForTarget),
    });
  *surfaceConstructor = Napi::Persistent(func);
  exports.Set("CairoSurface", func);
  return exports;
}

CairoSurface::CairoSurface(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoSurface>(info)
{
  this->surface_ = nullptr;
}

CairoSurface::~CairoSurface()
{
  if (this->surface_) {
    cairo_surface_destroy(this->surface_);
    this->surface_ = nullptr;
  }
  if (this->uks.size() > 0) {
    for (auto iter = this->uks.begin(); iter != this->uks.end(); iter++) {
      free(iter->second);
    }
    this->uks.clear();
  }
}

Napi::Object
CairoSurface::NewInstance(cairo_surface_t* surface)
{
  Napi::Object obj = surfaceConstructor->New({});
  CairoSurface* s = Napi::ObjectWrap<CairoSurface>::Unwrap(obj);
  s->SetSurface(surface);
  cairo_surface_reference(surface);
  return obj;
}

bool
CairoSurface::HasInstance(const Napi::Value& v)
{
  return v.IsObject() &&
         v.As<Napi::Object>().InstanceOf(surfaceConstructor->Value());
}

cairo_surface_t*
CairoSurface::GetSurface()
{
  return this->surface_;
}

void
CairoSurface::SetSurface(cairo_surface_t* s)
{
  this->surface_ = s;
}

Napi::Value
CairoSurface::CreateSimilar(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 3) {
    return ThrowErrorAsJavaScriptException(env, "Wrong number of arguments");
  }
  // content
  if (!ParamIsNumber(env, "content", info[0])) {
    return env.Undefined();
  }
  int content = info[0].As<Napi::Number>();
  if (content != CAIRO_CONTENT_COLOR && content != CAIRO_CONTENT_ALPHA &&
      content != CAIRO_CONTENT_COLOR_ALPHA) {
    return ThrowTypeErrorAsJavaScriptException(
      env, "The second parameter is invalid");
  }
  if (!ParamIsNumber(env, "width", info[1]) ||
      !ParamIsNumber(env, "height", info[2])) {
    return env.Undefined();
  }
  int width = info[1].As<Napi::Number>();
  int height = info[2].As<Napi::Number>();
  cairo_surface_t* surface = cairo_surface_create_similar(
    this->surface_, static_cast<cairo_content_t>(content), width, height);
  cairo_status_t status = cairo_surface_status(surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create similar surface.", status);
  }
  return CairoSurface::NewInstance(surface);
}

Napi::Value
CairoSurface::CreateSimilarImage(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (info.Length() != 3) {
    return ThrowErrorAsJavaScriptException(env, "Wrong number of arguments");
  }
  // format
  if (!CheckCairoFormatParameter(env, info[0])) {
    return env.Undefined();
  }
  int format = info[0].As<Napi::Number>();
  if (!ParamIsNumber(env, "width", info[1]) ||
      !ParamIsNumber(env, "height", info[2])) {
    return env.Undefined();
  }
  int width = info[1].As<Napi::Number>();
  int height = info[2].As<Napi::Number>();
  cairo_surface_t* surface = cairo_surface_create_similar_image(
    this->surface_, (cairo_format_t)format, width, height);
  cairo_status_t status = cairo_surface_status(surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create similar image surface.", status);
  }
  return CairoSurface::NewInstance(surface);
}

Napi::Value
CairoSurface::CreateForRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 4)) {
    return env.Undefined();
  }
  // x
  if (!ParamIsNumber(env, "x", info[0])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  // y
  if (!ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  double y = info[1].As<Napi::Number>();
  // width
  if (!ParamIsNumber(env, "width", info[2])) {
    return env.Undefined();
  }
  double width = info[2].As<Napi::Number>();
  // height
  if (!ParamIsNumber(env, "height", info[3])) {
    return env.Undefined();
  }
  double height = info[3].As<Napi::Number>();
  cairo_surface_t* s =
    cairo_surface_create_for_rectangle(this->surface_, x, y, width, height);
  cairo_status_t status = cairo_surface_status(s);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create for rectangle.", status);
  }
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoSurface::Reference(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_surface_reference(this->surface_);
  return info.This();
}

Napi::Value
CairoSurface::Destroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  if (this->surface_) {
    cairo_surface_destroy(this->surface_);
    this->surface_ = nullptr;
  }
  return info.This();
}

Napi::Value
CairoSurface::Status(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  int status = cairo_surface_status(this->surface_);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoSurface::Finish(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_surface_finish(this->surface_);
  return info.This();
}

Napi::Value
CairoSurface::Flush(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_surface_flush(this->surface_);
  return info.This();
}

Napi::Value
CairoSurface::GetDevice(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_device_t* d = cairo_surface_get_device(this->surface_);
  return CairoDevice::NewInstance(d);
}

Napi::Value
CairoSurface::GetFontOptions(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_options_t* options = cairo_font_options_create();
  cairo_surface_get_font_options(this->surface_, options);
  return CairoFontOptions::NewInstance(options);
}

Napi::Value
CairoSurface::GetContent(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_content_t content = cairo_surface_get_content(this->surface_);
  return Napi::Number::New(env, content);
}

Napi::Value
CairoSurface::MarkDirty(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_surface_mark_dirty(this->surface_);
  return info.This();
}

Napi::Value
CairoSurface::MarkDirtyRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 4)) {
    return info.This();
  }
  // x
  if (!ParamIsNumber(env, "x", info[0])) {
    return info.This();
  }
  int x = info[0].As<Napi::Number>();
  // y
  if (!ParamIsNumber(env, "y", info[1])) {
    return info.This();
  }
  int y = info[1].As<Napi::Number>();
  // width
  if (!ParamIsNumber(env, "width", info[2])) {
    return info.This();
  }
  int width = info[2].As<Napi::Number>();
  // height
  if (!ParamIsNumber(env, "width", info[3])) {
    return info.This();
  }
  int height = info[3].As<Napi::Number>();
  cairo_surface_mark_dirty_rectangle(this->surface_, x, y, width, height);
  return info.This();
}

Napi::Value
CairoSurface::SetDeviceOffset(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return info.This();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_surface_set_device_offset(this->surface_, x, y);
  return info.This();
}

Napi::Value
CairoSurface::GetDeviceOffset(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double x, y;
  cairo_surface_get_device_offset(this->surface_, &x, &y);
  Napi::Object result = Napi::Object::New(env);
  result.Set("x", Napi::Number::New(env, x));
  result.Set("y", Napi::Number::New(env, y));
  return result;
}

Napi::Value
CairoSurface::GetDeviceScale(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double x, y;
  cairo_surface_get_device_scale(this->surface_, &x, &y);
  Napi::Object result = Napi::Object::New(env);
  result.Set("x", Napi::Number::New(env, x));
  result.Set("y", Napi::Number::New(env, y));
  return result;
}

Napi::Value
CairoSurface::SetDeviceScale(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "x scale", info[0]) ||
      !ParamIsNumber(env, "y scale", info[1])) {
    return info.This();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_surface_set_device_scale(this->surface_, x, y);
  return info.This();
}

Napi::Value
CairoSurface::SetFallbackResolution(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "x pixels", info[0]) ||
      !ParamIsNumber(env, "y pixels", info[1])) {
    return info.This();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_surface_set_fallback_resolution(this->surface_, x, y);
  return info.This();
}

Napi::Value
CairoSurface::GetFallbackResolution(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double x, y;
  cairo_surface_get_fallback_resolution(this->surface_, &x, &y);
  Napi::Object result = Napi::Object::New(env);
  result.Set("x", Napi::Number::New(env, x));
  result.Set("y", Napi::Number::New(env, y));
  return result;
}

Napi::Value
CairoSurface::GetType(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_surface_type_t type = cairo_surface_get_type(this->surface_);
  return Napi::Number::New(env, type);
}

Napi::Value
CairoSurface::GetReferenceCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  unsigned int count = cairo_surface_get_reference_count(this->surface_);
  return Napi::Number::New(env, count);
}

Napi::Value
CairoSurface::SetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  // key
  if (!ParamIsString(env, "key", info[0])) {
    return info.This();
  }
  string key = info[0].As<Napi::String>();
  // value
  Napi::Value data = info[1];
  if (data.IsNull()) {
    if (this->uks.find(key) == this->uks.end()) {
      return info.This();
    }
    cairo_user_data_key_t* k = this->uks[key];
    cairo_status_t status =
      cairo_surface_set_user_data(this->surface_, k, nullptr, nullptr);
    if (status != CAIRO_STATUS_SUCCESS) {
      ThrowStatusErrorAsJavaScriptException(
        env, "Fail to set user data.", status);
    }
    return info.This();
  }
  cairo_user_data_key_t* uk =
    (cairo_user_data_key_t*)malloc(sizeof(cairo_user_data_key_t));
  cairo_status_t status =
    cairo_surface_set_user_data(this->surface_, uk, &data, nullptr);
  if (status == CAIRO_STATUS_SUCCESS) {
    this->uks[key] = uk;
  } else {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to set user data.", status);
  }
  return info.This();
}

Napi::Value
CairoSurface::GetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "key", info[0])) {
    return env.Undefined();
  }
  string key = info[0].As<Napi::String>();
  if (this->uks.find(key) == this->uks.end()) {
    return env.Undefined();
  }
  return *(Napi::Value*)cairo_surface_get_user_data(this->surface_,
                                                    this->uks[key]);
}

Napi::Value
CairoSurface::CopyPage(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_surface_copy_page(this->surface_);
  return info.This();
}

Napi::Value
CairoSurface::ShowPage(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_surface_show_page(this->surface_);
  return info.This();
}

Napi::Value
CairoSurface::HasShowTextGlyphs(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_bool_t yes = cairo_surface_has_show_text_glyphs(this->surface_);
  return Napi::Boolean::New(env, yes);
}

Napi::Value
CairoSurface::SetMimeData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  // mime
  if (!ParamIsString(env, "mime", info[0])) {
    return info.This();
  }
  string mime = info[0].As<Napi::String>();
  if (mimes.find(mime) == mimes.end()) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid mime.");
  }
  // data
  if (info[1].IsArrayBuffer()) {
    Napi::ArrayBuffer buffer = info[1].As<Napi::ArrayBuffer>();
    unsigned char* data = (unsigned char*)buffer.Data();
    cairo_status_t status = cairo_surface_set_mime_data(this->surface_,
                                                        mime.c_str(),
                                                        data,
                                                        buffer.ByteLength(),
                                                        nullptr,
                                                        nullptr);
    if (status != CAIRO_STATUS_SUCCESS) {
      ThrowStatusErrorAsJavaScriptException(
        env, "Fail to set mime data.", status);
    }
  } else if (info[1].IsNull()) {
    cairo_status_t status = cairo_surface_set_mime_data(
      this->surface_, mime.c_str(), nullptr, 0, nullptr, nullptr);
    if (status != CAIRO_STATUS_SUCCESS) {
      ThrowStatusErrorAsJavaScriptException(
        env, "Fail to set mime data.", status);
    }
  } else {
    ThrowTypeErrorAsJavaScriptException(env, "Invalid data.");
  }
  return info.This();
}

Napi::Value
CairoSurface::GetMimeData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "mime", info[0])) {
    return env.Undefined();
  }
  string mime = info[0].As<Napi::String>();
  if (mimes.find(mime) == mimes.end()) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid mime.");
  }
  const unsigned char** data = nullptr;
  unsigned long* length = nullptr;
  cairo_surface_get_mime_data(this->surface_, mime.c_str(), data, length);
  if (data == nullptr) {
    return env.Null();
  }
  return data == nullptr ? env.Null()
                         : Napi::ArrayBuffer::New(env, data, *length);
}

Napi::Value
CairoSurface::SupportsMimeType(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "mime", info[0])) {
    return env.Undefined();
  }
  string mime = info[0].As<Napi::String>();
  bool supports =
    cairo_surface_supports_mime_type(this->surface_, mime.c_str());
  return Napi::Boolean::New(env, supports);
}

Napi::Value
CairoSurface::MapToImage(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  cairo_rectangle_int_t* rectPtr = nullptr;
  if (info[0].IsNull()) {
  } else if (ParamIsRectangleInt(env, "extents", info[0])) {
    cairo_rectangle_int_t rect;
    rectPtr = &rect;
    ObjectToRectangleInt(info[0].As<Napi::Object>(), rectPtr);
  } else {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid extents.");
  }
  cairo_surface_t* surface =
    cairo_surface_map_to_image(this->surface_, rectPtr);
  return CairoSurface::NewInstance(surface);
}

Napi::Value
CairoSurface::UnmapImage(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoSurface::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid image.");
  }
  CairoSurface* image =
    Napi::ObjectWrap<CairoSurface>::Unwrap(info[0].As<Napi::Object>());
  cairo_surface_unmap_image(this->surface_, image->surface_);
  return info.This();
}

Napi::Value
CairoSurface::FormatStrideForWidth(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  // format
  if (!CheckCairoFormatParameter(env, info[0])) {
    return env.Undefined();
  }
  int format = info[0].As<Napi::Number>();
  // width
  if (!ParamIsNumber(env, "width", info[1])) {
    return env.Undefined();
  }
  int width = info[1].As<Napi::Number>();
  int stride = cairo_format_stride_for_width((cairo_format_t)format, width);
  return Napi::Number::New(env, stride);
}

Napi::Value
CairoSurface::ImageSurfaceCreate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  if (!CheckCairoFormatParameter(env, info[0]) ||
      !ParamIsNumber(env, "width", info[1]) ||
      !ParamIsNumber(env, "height", info[2])) {
    return env.Undefined();
  }
  int format = info[0].As<Napi::Number>();
  int width = info[1].As<Napi::Number>();
  int height = info[2].As<Napi::Number>();
  cairo_surface_t* surface =
    cairo_image_surface_create((cairo_format_t)format, width, height);
  cairo_status_t status = cairo_surface_status(surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create image surface.", status);
  }
  return CairoSurface::NewInstance(surface);
}

Napi::Value
CairoSurface::ImageSurfaceCreateForData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 5)) {
    return env.Undefined();
  }
  // data
  if (!ParamIsArrayBuffer(env, "data", info[0]) ||
      !CheckCairoFormatParameter(env, info[1]) ||
      !ParamIsNumber(env, "width", info[2]) ||
      !ParamIsNumber(env, "height", info[3]) ||
      !ParamIsNumber(env, "stride", info[4])) {
    return env.Undefined();
  }
  Napi::ArrayBuffer buf = info[0].As<Napi::ArrayBuffer>();
  unsigned char* data = (unsigned char*)buf.Data();
  int format = info[1].As<Napi::Number>();
  int width = info[2].As<Napi::Number>();
  int height = info[3].As<Napi::Number>();
  int stride = info[4].As<Napi::Number>();
  cairo_surface_t* s = cairo_image_surface_create_for_data(
    data, (cairo_format_t)format, width, height, stride);
  cairo_status_t status = cairo_surface_status(s);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create surface.", status);
  }
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoSurface::ImageSurfaceGetData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  // TODO
  return info.This();
}

Napi::Value
CairoSurface::ImageSurfaceGetFormat(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_format_t format = cairo_image_surface_get_format(this->surface_);
  return Napi::Number::New(env, format);
}

Napi::Value
CairoSurface::ImageSurfaceGetWidth(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  int width = cairo_image_surface_get_width(this->surface_);
  return Napi::Number::New(env, width);
}

Napi::Value
CairoSurface::ImageSurfaceGetHeight(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  int height = cairo_image_surface_get_height(this->surface_);
  return Napi::Number::New(env, height);
}

Napi::Value
CairoSurface::ImageSurfaceGetStride(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  int stride = cairo_image_surface_get_stride(this->surface_);
  return Napi::Number::New(env, stride);
}

Napi::Value
CairoSurface::PdfSurfaceCreate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  // filename
  if (!ParamIsString(env, "filename", info[0])) {
    return env.Undefined();
  }
  string filename = info[0].As<Napi::String>();
  // width in points
  if (!ParamIsNumber(env, "width", info[1])) {
    return env.Undefined();
  }
  double width = info[1].As<Napi::Number>();
  // height in points
  if (!ParamIsNumber(env, "height", info[2])) {
    return env.Undefined();
  }
  double height = info[2].As<Napi::Number>();
  cairo_surface_t* s =
    cairo_pdf_surface_create(filename.c_str(), width, height);
  cairo_status_t status = cairo_surface_status(s);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create pdf surface.", status);
  }
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoSurface::PdfSurfaceCreateForStream(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoSurface::PdfSurfaceRestrictToVersion(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1) ||
      !ParamIsNumber(env, "version", info[0])) {
    return info.This();
  }
  int version = info[0].As<Napi::Number>();
  cairo_pdf_surface_restrict_to_version(this->surface_,
                                        (cairo_pdf_version_t)version);
  return info.This();
}

Napi::Value
CairoSurface::PdfGetVersions(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  const cairo_pdf_version_t** versions = nullptr;
  int num_version;
  cairo_pdf_get_versions(versions, &num_version);
  Napi::Int8Array vs;
  for (int i = 0; i < num_version; i++) {
    vs[i] = (int)(*versions[i]);
  }
  return vs;
}

Napi::Value
CairoSurface::PdfVersionToString(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "version", info[0])) {
    return env.Undefined();
  }
  int version = info[0].As<Napi::Number>();
  const char* str = cairo_pdf_version_to_string((cairo_pdf_version_t)version);
  return str == nullptr ? env.Null() : Napi::String::New(env, str);
}

Napi::Value
CairoSurface::PdfSurfaceSetSize(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "width", info[0]) ||
      !ParamIsNumber(env, "height", info[1])) {
    return info.This();
  }
  double width = info[0].As<Napi::Number>();
  double height = info[1].As<Napi::Number>();
  cairo_pdf_surface_set_size(this->surface_, width, height);
  return info.This();
}

Napi::Value
CairoSurface::PdfSurfaceAddOutline(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 4)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "parent", info[0]) ||
      !ParamIsString(env, "name", info[1]) ||
      !ParamIsString(env, "link attributes", info[2]) ||
      !ParamIsNumber(env, "flags", info[3])) {
    return env.Undefined();
  }
  int parent = info[0].As<Napi::Number>();
  string name = info[1].As<Napi::String>();
  string attributes = info[2].As<Napi::String>();
  int flags = info[3].As<Napi::Number>();
  int id = cairo_pdf_surface_add_outline(this->surface_,
                                         parent,
                                         name.c_str(),
                                         attributes.c_str(),
                                         (cairo_pdf_outline_flags_t)flags);
  return Napi::Number::New(env, id);
}

Napi::Value
CairoSurface::PdfSurfaceSetMetadata(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  // metadata
  if (!ParamIsNumber(env, "metadata", info[0])) {
    return info.This();
  }
  int metadata = info[0].As<Napi::Number>();
  // value
  if (!ParamIsString(env, "value", info[1])) {
    return info.This();
  }
  string value = info[1].As<Napi::String>();
  cairo_pdf_surface_set_metadata(
    this->surface_, (cairo_pdf_metadata_t)metadata, value.c_str());
  return info.This();
}

Napi::Value
CairoSurface::PdfSurfaceSetPageLabel(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsString(env, "label", info[0])) {
    return info.This();
  }
  string label = info[0].As<Napi::String>();
  cairo_pdf_surface_set_page_label(this->surface_, label.c_str());
  return info.This();
}

Napi::Value
CairoSurface::PdfSurfaceSetThumbnailSize(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "width", info[0]) ||
      !ParamIsNumber(env, "height", info[1])) {
    return info.This();
  }
  int width = info[0].As<Napi::Number>();
  int height = info[1].As<Napi::Number>();
  cairo_pdf_surface_set_thumbnail_size(this->surface_, width, height);
  return info.This();
}

Napi::Value
CairoSurface::ImageSurfaceCreateFromPng(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "filename", info[0])) {
    return env.Undefined();
  }
  string filename = info[0].As<Napi::String>();
  cairo_surface_t* s = cairo_image_surface_create_from_png(filename.c_str());
  cairo_status_t status = cairo_surface_status(s);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create image surface from png.", status);
  }
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoSurface::ImageSurfaceCreateFromPngStream(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoSurface::WriteToPng(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsString(env, "filename", info[0])) {
    return info.This();
  }
  string filename = info[0].As<Napi::String>();
  cairo_surface_write_to_png(this->surface_, filename.c_str());
  return info.This();
}

Napi::Value
CairoSurface::WriteToPngStream(const Napi::CallbackInfo& info)
{
  // TODO
  return info.This();
}

Napi::Value
CairoSurface::RecordingSurfaceCreate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  // content
  if (!ParamIsNumber(env, "content", info[0])) {
    return env.Undefined();
  }
  int content = info[0].As<Napi::Number>();
  // extents
  if (!ParamIsRectangle(env, "extents", info[1])) {
    return env.Undefined();
  }
  cairo_rectangle_t rect;
  ObjectToRectangle(info[1].As<Napi::Object>(), &rect);
  cairo_surface_t* s =
    cairo_recording_surface_create((cairo_content_t)content, &rect);
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoSurface::RecordingSurfaceInkExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double x, y, w, h;
  cairo_recording_surface_ink_extents(this->surface_, &x, &y, &w, &h);
  Napi::Object result = Napi::Object::New(env);
  result.Set("x", Napi::Number::New(env, x));
  result.Set("y", Napi::Number::New(env, y));
  result.Set("width", Napi::Number::New(env, w));
  result.Set("height", Napi::Number::New(env, h));
  return result;
}

Napi::Value
CairoSurface::RecordingSurfaceGetExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_rectangle_t rect;
  cairo_bool_t success =
    cairo_recording_surface_get_extents(this->surface_, &rect);
  if (!success) {
    return env.Null();
  }
  Napi::Object result = Napi::Object::New(env);
  RectangleToObject(env, &rect, &result);
  return result;
}

Napi::Value
CairoSurface::SvgSurfaceCreate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "filename", info[0]) ||
      !ParamIsNumber(env, "width", info[1]) ||
      !ParamIsNumber(env, "height", info[2])) {
    return env.Undefined();
  }
  string filename = info[0].As<Napi::String>();
  double width = info[1].As<Napi::Number>();
  double height = info[2].As<Napi::Number>();
  cairo_surface_t* s =
    cairo_svg_surface_create(filename.c_str(), width, height);
  cairo_status_t status = cairo_surface_status(s);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create surface from svg.", status);
  }
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoSurface::SvgSurfaceCreateForStream(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoSurface::SvgSurfaceGetDocumentUnit(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_svg_unit_t unit = cairo_svg_surface_get_document_unit(this->surface_);
  if (cairo_surface_status(this->surface_) ==
        CAIRO_STATUS_SURFACE_TYPE_MISMATCH &&
      unit == CAIRO_SVG_UNIT_USER) {
    return ThrowErrorAsJavaScriptException(env, "Not a svg surface.");
  }
  return Napi::Number::New(env, unit);
}

Napi::Value
CairoSurface::SvgSurfaceSetDocumentUnit(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "unit", info[0])) {
    return info.This();
  }
  int unit = info[0].As<Napi::Number>();
  cairo_svg_surface_set_document_unit(this->surface_, (cairo_svg_unit_t)unit);
  return info.This();
}

Napi::Value
CairoSurface::SvgSurfaceRestrictToVersion(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "version", info[0])) {
    return info.This();
  }
  int version = info[0].As<Napi::Number>();
  cairo_svg_surface_restrict_to_version(this->surface_,
                                        (cairo_svg_version_t)version);
  return info.This();
}

Napi::Value
CairoSurface::SvgGetVersions(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  const cairo_svg_version_t** versions = nullptr;
  int num_version;
  cairo_svg_get_versions(versions, &num_version);
  Napi::Int8Array result;
  for (int i = 0; i < num_version; i++) {
    result.Set(i, Napi::Number::New(env, *versions[i]));
  }
  return result;
}

Napi::Value
CairoSurface::SvgVersionToString(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "version", info[0])) {
    return env.Undefined();
  }
  int version = info[0].As<Napi::Number>();
  const char* name = cairo_svg_version_to_string((cairo_svg_version_t)version);
  return name == nullptr ? env.Null() : Napi::String::New(env, name);
}

Napi::Value
CairoSurface::ScriptFromRecordingSurface(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!CairoDevice::HasInstance(info[0])) {
    return ThrowErrorAsJavaScriptException(env, "Invalid script.");
  }
  CairoDevice* script =
    Napi::ObjectWrap<CairoDevice>::Unwrap(info[0].As<Napi::Object>());
  cairo_status_t status =
    cairo_script_from_recording_surface(script->GetDevice(), this->surface_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env,
      "Fail to convert the record operations in recording surface to script.",
      status);
  }
  return info.This();
}

Napi::Value
CairoSurface::ScriptSurfaceCreate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 4)) {
    return env.Undefined();
  }
  if (!CairoDevice::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid script.");
  }
  CairoDevice* script =
    Napi::ObjectWrap<CairoDevice>::Unwrap(info[0].As<Napi::Object>());
  int content = info[1].As<Napi::Number>();
  if (!ParamIsNumber(env, "content", info[1]) ||
      !ParamIsNumber(env, "width", info[2]) ||
      !ParamIsNumber(env, "height", info[3])) {
    return env.Undefined();
  }
  double width = info[2].As<Napi::Number>();
  double height = info[3].As<Napi::Number>();
  cairo_surface_t* s = cairo_script_surface_create(
    script->GetDevice(), (cairo_content_t)content, width, height);
  cairo_status_t status = cairo_surface_status(s);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create surface from script.", status);
  }
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoSurface::ScriptSurfaceCreateForTarget(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  // script
  if (!CairoDevice::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid script.");
  }
  CairoDevice* script =
    Napi::ObjectWrap<CairoDevice>::Unwrap(info[0].As<Napi::Object>());
  // target
  if (!CairoSurface::HasInstance(info[1])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid target.");
  }
  CairoSurface* target =
    Napi::ObjectWrap<CairoSurface>::Unwrap(info[1].As<Napi::Object>());
  cairo_surface_t* s = cairo_script_surface_create_for_target(
    script->GetDevice(), target->GetSurface());
  cairo_status_t status = cairo_surface_status(s);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create script surface for target.", status);
  }
  return CairoSurface::NewInstance(s);
}