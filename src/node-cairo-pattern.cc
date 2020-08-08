#include "node-cairo-pattern.h"
#include "node-cairo-path.h"
#include "node-cairo-surface.h"
#include "node-cairo-utils.h"

using namespace std;

static Napi::FunctionReference* patternConstructor =
  new Napi::FunctionReference();

Napi::Object
CairoPattern::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "CairoPattern",
    {
      InstanceMethod("addColorStopRgb", &CairoPattern::AddColorStopRgb),
      InstanceMethod("addColorStopRgba", &CairoPattern::AddColorStopRgba),
      InstanceMethod("getColorStopCount", &CairoPattern::GetColorStopCount),
      InstanceMethod("getColorStopRgba", &CairoPattern::GetColorStopRgba),
      StaticMethod("createRgb", &CairoPattern::CreateRgb),
      StaticMethod("createRgba", &CairoPattern::CreateRgba),
      InstanceMethod("getRgba", &CairoPattern::GetRgba),
      StaticMethod("createForSurface", &CairoPattern::CreateForSurface),
      InstanceMethod("getSurface", &CairoPattern::GetSurface),
      StaticMethod("createLinear", &CairoPattern::CreateLinear),
      InstanceMethod("getLinearPoints", &CairoPattern::GetLinearPoints),
      StaticMethod("createRadial", &CairoPattern::CreateRadial),
      InstanceMethod("getRadialCircles", &CairoPattern::GetRadialCircles),
      StaticMethod("createMesh", &CairoPattern::CreateMesh),
      InstanceMethod("meshPatternBeginPath",
                     &CairoPattern::MeshPatternBeginPath),
      InstanceMethod("meshPatternEndPath", &CairoPattern::MeshPatternEndPath),
      InstanceMethod("meshPatternMoveTo", &CairoPattern::MeshPatternMoveTo),
      InstanceMethod("meshPatternLineTo", &CairoPattern::MeshPatternLineTo),
      InstanceMethod("meshPatternCurveTo", &CairoPattern::MeshPatternCurveTo),
      InstanceMethod("meshPatternSetControlPoint",
                     &CairoPattern::MeshPatternSetControlPoint),
      InstanceMethod("meshPatternSetCornerColorRgb",
                     &CairoPattern::MeshPatternSetCornerColorRgb),
      InstanceMethod("meshPatternSetCornerColorRgba",
                     &CairoPattern::MeshPatternSetCornerColorRgba),
      InstanceMethod("meshPatternGetPatchCount",
                     &CairoPattern::MeshPatternGetPatchCount),
      InstanceMethod("meshPatternGetPath", &CairoPattern::MeshPatternGetPath),
      InstanceMethod("meshPatternGetControlPoint",
                     &CairoPattern::MeshPatternGetControlPoint),
      InstanceMethod("meshPatternGetCornerColorRgba",
                     &CairoPattern::MeshPatternGetCornerColorRgba),
      InstanceMethod("reference", &CairoPattern::Reference),
      InstanceMethod("destroy", &CairoPattern::Destroy),
      InstanceMethod("status", &CairoPattern::Status),
      InstanceMethod("setExtend", &CairoPattern::SetExtend),
      InstanceMethod("getExtend", &CairoPattern::GetExtend),
      InstanceMethod("setFilter", &CairoPattern::SetFilter),
      InstanceMethod("getFilter", &CairoPattern::GetFilter),
      InstanceMethod("setMatrix", &CairoPattern::SetMatrix),
      InstanceMethod("getMatrix", &CairoPattern::GetMatrix),
      InstanceMethod("getType", &CairoPattern::GetType),
      InstanceMethod("getReferenceCount", &CairoPattern::GetReferenceCount),
      InstanceMethod("setUserData", &CairoPattern::SetUserData),
      InstanceMethod("getUserData", &CairoPattern::GetUserData),
    });
  *patternConstructor = Napi::Persistent(func);
  exports.Set("CairoPattern", func);
  return exports;
}

CairoPattern::CairoPattern(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoPattern>(info)
{
  this->pattern_ = nullptr;
}

CairoPattern::~CairoPattern()
{
  if (this->pattern_) {
    cairo_pattern_destroy(this->pattern_);
    this->pattern_ = nullptr;
  }
}

cairo_pattern_t*
CairoPattern::GetPattern()
{
  return this->pattern_;
}

void
CairoPattern::SetPattern(cairo_pattern_t* pattern)
{
  this->pattern_ = pattern;
}

Napi::Object
CairoPattern::NewInstance(cairo_pattern_t* pattern)
{
  Napi::Object obj = patternConstructor->New({});
  CairoPattern* p = Napi::ObjectWrap<CairoPattern>::Unwrap(obj);
  p->SetPattern(pattern);
  cairo_pattern_reference(pattern);
  return obj;
}

bool
CairoPattern::HasInstance(const Napi::Value& value)
{
  if (!value.IsObject()) {
    return false;
  }
  return value.As<Napi::Object>().InstanceOf(patternConstructor->Value());
}

Napi::Value
CairoPattern::AddColorStopRgb(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  4, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "offset", env) ||
      !ParamIsNumber( info[1],  "red", env) ||
      !ParamIsNumber( info[2],  "green", env) ||
      !ParamIsNumber( info[3],  "blue", env)) {
    return info.This();
  }
  double offset = info[0].As<Napi::Number>();
  double red = info[1].As<Napi::Number>();
  double green = info[2].As<Napi::Number>();
  double blue = info[3].As<Napi::Number>();
  cairo_pattern_add_color_stop_rgb(this->pattern_, offset, red, green, blue);
  return info.This();
}

Napi::Value
CairoPattern::AddColorStopRgba(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  5, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "offset", env) ||
      !ParamIsNumber( info[1],  "red", env) ||
      !ParamIsNumber( info[2],  "green", env) ||
      !ParamIsNumber( info[3],  "blue", env) ||
      !ParamIsNumber( info[4],  "alpha", env)) {
    return info.This();
  }
  double offset = info[0].As<Napi::Number>();
  double red = info[1].As<Napi::Number>();
  double green = info[2].As<Napi::Number>();
  double blue = info[3].As<Napi::Number>();
  double alpha = info[4].As<Napi::Number>();
  cairo_pattern_add_color_stop_rgba(
    this->pattern_, offset, red, green, blue, alpha);
  return info.This();
}

Napi::Value
CairoPattern::GetColorStopCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  int count;
  cairo_status_t status =
    cairo_pattern_get_color_stop_count(this->pattern_, &count);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get color stop count.", status);
  }
  return Napi::Number::New(env, count);
}

Napi::Value
CairoPattern::GetColorStopRgba(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber( info[0],  "index", env)) {
    return env.Undefined();
  }
  int index = info[0].As<Napi::Number>();
  double offset, red, green, blue, alpha;
  cairo_pattern_get_color_stop_rgba(
    this->pattern_, index, &offset, &red, &green, &blue, &alpha);
  Napi::Object result = Napi::Object::New(env);
  result.Set("offset", Napi::Number::New(env, offset));
  result.Set("r", Napi::Number::New(env, red));
  result.Set("g", Napi::Number::New(env, green));
  result.Set("b", Napi::Number::New(env, blue));
  result.Set("a", Napi::Number::New(env, alpha));
  return result;
}

Napi::Value
CairoPattern::CreateRgb(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  3, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber( info[0],  "red", env) ||
      !ParamIsNumber( info[1],  "green", env) ||
      !ParamIsNumber( info[2],  "blue", env)) {
    return env.Undefined();
  }
  double r = info[0].As<Napi::Number>();
  double g = info[1].As<Napi::Number>();
  double b = info[2].As<Napi::Number>();
  cairo_pattern_t* p = cairo_pattern_create_rgb(r, g, b);
  cairo_status_t status = cairo_pattern_status(p);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create rgb pattern.", status);
  }
  return CairoPattern::NewInstance(p);
}
Napi::Value
CairoPattern::CreateRgba(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  4, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber( info[0],  "red", env) ||
      !ParamIsNumber( info[1],  "green", env) ||
      !ParamIsNumber( info[2],  "blue", env)) {
    return env.Undefined();
  }
  double r = info[0].As<Napi::Number>();
  double g = info[1].As<Napi::Number>();
  double b = info[2].As<Napi::Number>();
  double a = info[3].As<Napi::Number>();
  cairo_pattern_t* p = cairo_pattern_create_rgba(r, g, b, a);
  cairo_status_t status = cairo_pattern_status(p);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create rgba pattern.", status);
  }
  return CairoPattern::NewInstance(p);
}

Napi::Value
CairoPattern::GetRgba(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  double r, g, b, a;
  cairo_pattern_get_rgba(this->pattern_, &r, &g, &b, &a);
  Napi::Object result = Napi::Object::New(env);
  result.Set("r", Napi::Number::New(env, r));
  result.Set("g", Napi::Number::New(env, g));
  result.Set("b", Napi::Number::New(env, b));
  result.Set("a", Napi::Number::New(env, a));
  return result;
}

Napi::Value
CairoPattern::CreateForSurface(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  1, env)) {
    return env.Undefined();
  }
  if (!CairoSurface::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid surface.");
  }
  CairoSurface* surface =
    Napi::ObjectWrap<CairoSurface>::Unwrap(info[0].As<Napi::Object>());
  cairo_pattern_t* p = cairo_pattern_create_for_surface(surface->GetSurface());
  cairo_status_t status = cairo_pattern_status(p);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create pattern for surface.", status);
  }
  return CairoPattern::NewInstance(p);
}

Napi::Value
CairoPattern::GetSurface(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  cairo_surface_t* surface = nullptr;
  cairo_status_t status = cairo_pattern_get_surface(this->pattern_, &surface);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get surface.", status);
  }
  return surface == nullptr ? env.Null() : CairoSurface::NewInstance(surface);
}

Napi::Value
CairoPattern::CreateLinear(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  4, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber( info[0],  "start x", env) ||
      !ParamIsNumber( info[1],  "start y", env) ||
      !ParamIsNumber( info[2],  "end x", env) ||
      !ParamIsNumber( info[3],  "end y", env)) {
    return env.Undefined();
  }
  double x0 = info[0].As<Napi::Number>();
  double y0 = info[1].As<Napi::Number>();
  double x1 = info[2].As<Napi::Number>();
  double y1 = info[3].As<Napi::Number>();
  cairo_pattern_t* p = cairo_pattern_create_linear(x0, y0, x1, y1);
  cairo_status_t status = cairo_pattern_status(p);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create linear pattern.", status);
  }
  return CairoPattern::NewInstance(p);
}

Napi::Value
CairoPattern::GetLinearPoints(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  double *x0 = nullptr, *y0 = nullptr, *x1 = nullptr, *y1 = nullptr;
  cairo_status_t status =
    cairo_pattern_get_linear_points(this->pattern_, x0, y0, x1, y1);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get linear points.", status);
  }
  if (x0 == nullptr) {
    return env.Null();
  }
  Napi::Object result = Napi::Object::New(env);
  result.Set("x0", Napi::Number::New(env, *x0));
  result.Set("y0", Napi::Number::New(env, *y0));
  result.Set("x1", Napi::Number::New(env, *x1));
  result.Set("y1", Napi::Number::New(env, *y1));
  return result;
}

Napi::Value
CairoPattern::CreateRadial(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  6, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber( info[0],  "start x", env) ||
      !ParamIsNumber( info[1],  "start y", env) ||
      !ParamIsNumber( info[2],  "start radius", env) ||
      !ParamIsNumber( info[3],  "end x", env) ||
      !ParamIsNumber( info[4],  "end y", env) ||
      !ParamIsNumber( info[5],  "end radius", env)) {
    return env.Undefined();
  }
  double x0 = info[0].As<Napi::Number>();
  double y0 = info[1].As<Napi::Number>();
  double r0 = info[2].As<Napi::Number>();
  double x1 = info[3].As<Napi::Number>();
  double y1 = info[4].As<Napi::Number>();
  double r1 = info[5].As<Napi::Number>();
  cairo_pattern_t* p = cairo_pattern_create_radial(x0, y0, r0, x1, y1, r1);
  cairo_status_t status = cairo_pattern_status(p);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create radial pattern.", status);
  }
  return CairoPattern::NewInstance(p);
}

Napi::Value
CairoPattern::GetRadialCircles(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  double *x0 = nullptr, *y0 = nullptr, *r0 = nullptr, *x1 = nullptr,
         *y1 = nullptr, *r1 = nullptr;
  cairo_status_t status =
    cairo_pattern_get_radial_circles(this->pattern_, x0, y0, r0, x1, y1, r1);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get radial cirles.", status);
  }
  if (x0 == nullptr) {
    return env.Null();
  }
  Napi::Object result = Napi::Object::New(env);
  result.Set("x0", Napi::Number::New(env, *x0));
  result.Set("y0", Napi::Number::New(env, *y0));
  result.Set("r0", Napi::Number::New(env, *r0));
  result.Set("x1", Napi::Number::New(env, *x1));
  result.Set("y1", Napi::Number::New(env, *y1));
  result.Set("r1", Napi::Number::New(env, *r1));
  return result;
}

Napi::Value
CairoPattern::CreateMesh(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  cairo_pattern_t* p = cairo_pattern_create_mesh();
  cairo_status_t status = cairo_pattern_status(p);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create mesh.", status);
  }
  return CairoPattern::NewInstance(p);
}

Napi::Value
CairoPattern::MeshPatternBeginPath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return info.This();
  }
  cairo_mesh_pattern_begin_patch(this->pattern_);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to begin mesh path.", status);
  }
  return info.This();
}

Napi::Value
CairoPattern::MeshPatternEndPath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return info.This();
  }
  cairo_mesh_pattern_end_patch(this->pattern_);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to end mesh path.", status);
  }
  return info.This();
}

Napi::Value
CairoPattern::MeshPatternMoveTo(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  2, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "x", env) || !ParamIsNumber( info[1],  "y", env)) {
    return info.This();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_mesh_pattern_move_to(this->pattern_, x, y);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(env, "Fail to move mesh.", status);
  }
  return info.This();
}

Napi::Value
CairoPattern::MeshPatternLineTo(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  2, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "x", env) || !ParamIsNumber( info[1],  "y", env)) {
    return info.This();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_mesh_pattern_line_to(this->pattern_, x, y);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to draw mesh line.", status);
  }
  return info.This();
}
Napi::Value
CairoPattern::MeshPatternCurveTo(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  6, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "x1", env) ||
      !ParamIsNumber( info[1],  "y1", env) ||
      !ParamIsNumber( info[2],  "x2", env) ||
      !ParamIsNumber( info[3],  "y2", env) ||
      !ParamIsNumber( info[4],  "x3", env) ||
      !ParamIsNumber( info[5],  "y3", env)) {
    return info.This();
  }
  double x1 = info[0].As<Napi::Number>();
  double y1 = info[1].As<Napi::Number>();
  double x2 = info[2].As<Napi::Number>();
  double y2 = info[3].As<Napi::Number>();
  double x3 = info[4].As<Napi::Number>();
  double y3 = info[5].As<Napi::Number>();
  cairo_mesh_pattern_curve_to(this->pattern_, x1, y1, x2, y2, x3, y3);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to make mesh curve.", status);
  }
  return info.This();
}

Napi::Value
CairoPattern::MeshPatternSetControlPoint(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  3, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "point num", env) ||
      !ParamIsNumber( info[1],  "x", env) || !ParamIsNumber( info[2],  "y", env)) {
    return info.This();
  }
  unsigned int num = info[0].As<Napi::Number>();
  double x = info[1].As<Napi::Number>();
  double y = info[2].As<Napi::Number>();
  cairo_mesh_pattern_set_control_point(this->pattern_, num, x, y);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to set control point for mesh.", status);
  }
  return info.This();
}

Napi::Value
CairoPattern::MeshPatternSetCornerColorRgb(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  4, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "corner num", env) ||
      !ParamIsNumber( info[1],  "red", env) ||
      !ParamIsNumber( info[2],  "green", env) ||
      !ParamIsNumber( info[3],  "blue", env)) {
    return info.This();
  }
  unsigned int num = info[0].As<Napi::Number>();
  double r = info[1].As<Napi::Number>();
  double g = info[2].As<Napi::Number>();
  double b = info[3].As<Napi::Number>();
  cairo_mesh_pattern_set_corner_color_rgb(this->pattern_, num, r, g, b);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to set corner color for mesh.", status);
  }
  return info.This();
}

Napi::Value
CairoPattern::MeshPatternSetCornerColorRgba(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  5, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "corner num", env) ||
      !ParamIsNumber( info[1],  "red", env) ||
      !ParamIsNumber( info[2],  "green", env) ||
      !ParamIsNumber( info[3],  "blue", env) ||
      !ParamIsNumber( info[4],  "alpha", env)) {
    return info.This();
  }
  unsigned int num = info[0].As<Napi::Number>();
  double r = info[1].As<Napi::Number>();
  double g = info[2].As<Napi::Number>();
  double b = info[3].As<Napi::Number>();
  double a = info[4].As<Napi::Number>();
  cairo_mesh_pattern_set_corner_color_rgba(this->pattern_, num, r, g, b, a);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to set corner color for mesh.", status);
  }
  return info.This();
}

Napi::Value
CairoPattern::MeshPatternGetPatchCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  unsigned int* count = nullptr;
  cairo_mesh_pattern_get_patch_count(this->pattern_, count);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get patch count.", status);
  }
  return count == nullptr ? Napi::Number::New(env, 0)
                          : Napi::Number::New(env, *count);
}

Napi::Value
CairoPattern::MeshPatternGetPath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber( info[0],  "path num", env)) {
    return env.Undefined();
  }
  unsigned int num = info[0].As<Napi::Number>();
  cairo_path_t* path = cairo_mesh_pattern_get_path(this->pattern_, num);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get mesh.", status);
  }
  return CairoPath::NewInstance(path);
}

Napi::Value
CairoPattern::MeshPatternGetControlPoint(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  2, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber( info[0],  "patch num", env) ||
      !ParamIsNumber( info[1],  "point num", env)) {
    return env.Undefined();
  }
  unsigned int patchNum = info[0].As<Napi::Number>();
  unsigned int pointNum = info[1].As<Napi::Number>();
  double *x = nullptr, *y = nullptr;
  cairo_mesh_pattern_get_control_point(
    this->pattern_, patchNum, pointNum, x, y);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get control point.", status);
  }
  Napi::Object result = Napi::Object::New(env);
  result.Set("x", Napi::Number::New(env, *x));
  result.Set("y", Napi::Number::New(env, *y));
  return result;
}

Napi::Value
CairoPattern::MeshPatternGetCornerColorRgba(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  2, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber( info[0],  "patch num", env) ||
      !ParamIsNumber( info[1],  "corner num", env)) {
    return env.Undefined();
  }
  unsigned int patchNum = info[0].As<Napi::Number>();
  unsigned int cornerNum = info[1].As<Napi::Number>();
  double *r = nullptr, *g = nullptr, *b = nullptr, *a = nullptr;
  cairo_mesh_pattern_get_corner_color_rgba(
    this->pattern_, patchNum, cornerNum, r, g, b, a);
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get corner color.", status);
  }
  Napi::Object result = Napi::Object::New(env);
  result.Set("r", Napi::Number::New(env, *r));
  result.Set("g", Napi::Number::New(env, *g));
  result.Set("b", Napi::Number::New(env, *b));
  result.Set("a", Napi::Number::New(env, *a));
  return result;
}

Napi::Value
CairoPattern::Reference(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return info.This();
  }
  cairo_pattern_reference(this->pattern_);
  return info.This();
}

Napi::Value
CairoPattern::Destroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  if (this->pattern_) {
    cairo_pattern_destroy(this->pattern_);
    this->pattern_ = nullptr;
  }
  return info.This();
}

Napi::Value
CairoPattern::Status(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  cairo_status_t status = cairo_pattern_status(this->pattern_);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoPattern::SetExtend(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  1, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "extend", env)) {
    return info.This();
  }
  int extend = info[0].As<Napi::Number>();
  cairo_pattern_set_extend(this->pattern_, (cairo_extend_t)extend);
  return info.This();
}

Napi::Value
CairoPattern::GetExtend(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  cairo_extend_t extend = cairo_pattern_get_extend(this->pattern_);
  return Napi::Number::New(env, extend);
}

Napi::Value
CairoPattern::SetFilter(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  1, env)) {
    return info.This();
  }
  if (!ParamIsNumber( info[0],  "filter", env)) {
    return info.This();
  }
  int filter = info[0].As<Napi::Number>();
  cairo_pattern_set_filter(this->pattern_, (cairo_filter_t)filter);
  return info.This();
}

Napi::Value
CairoPattern::GetFilter(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  cairo_filter_t filter = cairo_pattern_get_filter(this->pattern_);
  return Napi::Number::New(env, filter);
}

Napi::Value
CairoPattern::SetMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  1, env)) {
    return info.This();
  }
  if (!ParamIsMatrix( info[0],  "matrix", env)) {
    return info.This();
  }
  cairo_matrix_t matrix;
  ObjectToMatrix(info[0].As<Napi::Object>(), &matrix);
  cairo_pattern_set_matrix(this->pattern_, &matrix);
  return info.This();
}

Napi::Value
CairoPattern::GetMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  cairo_pattern_get_matrix(this->pattern_, &matrix);
  Napi::Object result = Napi::Object::New(env);
  MatrixToObject(env, &matrix, &result);
  return result;
}

Napi::Value
CairoPattern::GetType(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  cairo_pattern_type_t type = cairo_pattern_get_type(this->pattern_);
  return Napi::Number::New(env, type);
}

Napi::Value
CairoPattern::GetReferenceCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber( info.Length(),  0, env)) {
    return env.Undefined();
  }
  unsigned int count = cairo_pattern_get_reference_count(this->pattern_);
  return Napi::Number::New(env, count);
}

Napi::Value
CairoPattern::SetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoPattern::GetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}