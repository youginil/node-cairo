#include "node-cairo-context.h"
#include "node-cairo-font-face.h"
#include "node-cairo-font-options.h"
#include "node-cairo-path.h"
#include "node-cairo-pattern.h"
#include "node-cairo-scaled-font.h"
#include "node-cairo-utils.h"

static Napi::FunctionReference* contextConstructor =
  new Napi::FunctionReference();

Napi::Object
CairoContext::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "CairoContext",
    {
      StaticMethod("create", &CairoContext::Create),
      InstanceMethod("reference", &CairoContext::Reference),
      InstanceMethod("destroy", &CairoContext::Destroy),
      InstanceMethod("status", &CairoContext::Status),
      InstanceMethod("save", &CairoContext::Save),
      InstanceMethod("restore", &CairoContext::Restore),
      InstanceMethod("getTarget", &CairoContext::GetTarget),
      InstanceMethod("pushGroup", &CairoContext::PushGroup),
      InstanceMethod("pushGroupWithContent",
                     &CairoContext::PushGroupWithContent),
      InstanceMethod("popGroup", &CairoContext::PopGroup),
      InstanceMethod("popGroupToSource", &CairoContext::PopGroupToSource),
      InstanceMethod("getGroupTarget", &CairoContext::GetGroupTarget),
      InstanceMethod("setSourceRgb", &CairoContext::SetSourceRgb),
      InstanceMethod("setSourceRgba", &CairoContext::SetSourceRgba),
      InstanceMethod("setSource", &CairoContext::SetSource),
      InstanceMethod("setSourceSurface", &CairoContext::SetSourceSurface),
      InstanceMethod("getSource", &CairoContext::GetSource),
      InstanceMethod("setAntialias", &CairoContext::SetAntialias),
      InstanceMethod("getAntialias", &CairoContext::GetAntialias),
      InstanceMethod("setDash", &CairoContext::SetDash),
      InstanceMethod("getDashCount", &CairoContext::GetDashCount),
      InstanceMethod("getDash", &CairoContext::GetDash),
      InstanceMethod("setFillRule", &CairoContext::SetFillRule),
      InstanceMethod("getFillRule", &CairoContext::GetFillRule),
      InstanceMethod("setLineCap", &CairoContext::SetLineCap),
      InstanceMethod("getLineCap", &CairoContext::GetLineCap),
      InstanceMethod("setLineJoin", &CairoContext::SetLineJoin),
      InstanceMethod("getLineJoin", &CairoContext::GetLineJoin),
      InstanceMethod("setLineWidth", &CairoContext::SetLineWidth),
      InstanceMethod("getLineWidth", &CairoContext::GetLineWidth),
      InstanceMethod("setMiterLimit", &CairoContext::SetMiterLimit),
      InstanceMethod("getMiterLimit", &CairoContext::GetMiterLimit),
      InstanceMethod("setOperator", &CairoContext::SetOperator),
      InstanceMethod("getOperator", &CairoContext::GetOperator),
      InstanceMethod("setTolerance", &CairoContext::SetTolerance),
      InstanceMethod("getTolerance", &CairoContext::GetTolerance),
      InstanceMethod("clip", &CairoContext::Clip),
      InstanceMethod("clipPreserve", &CairoContext::ClipPreserve),
      InstanceMethod("clipExtents", &CairoContext::ClipExtents),
      InstanceMethod("inClip", &CairoContext::InClip),
      InstanceMethod("resetClip", &CairoContext::ResetClip),
      InstanceMethod("rectangleListDestroy",
                     &CairoContext::RectangleListDestroy),
      InstanceMethod("copyClipRectangleList",
                     &CairoContext::CopyClipRectangleList),
      InstanceMethod("fill", &CairoContext::Fill),
      InstanceMethod("fillPreserve", &CairoContext::FillPreserve),
      InstanceMethod("fillExtents", &CairoContext::FillExtents),
      InstanceMethod("inFill", &CairoContext::InFill),
      InstanceMethod("mask", &CairoContext::Mask),
      InstanceMethod("maskSurface", &CairoContext::MaskSurface),
      InstanceMethod("paint", &CairoContext::Paint),
      InstanceMethod("paintWithAlpha", &CairoContext::PaintWithAlpha),
      InstanceMethod("stroke", &CairoContext::Stroke),
      InstanceMethod("strokePreserve", &CairoContext::StrokePreserve),
      InstanceMethod("strokeExtents", &CairoContext::StrokeExtents),
      InstanceMethod("InStroke", &CairoContext::InStroke),
      InstanceMethod("copyPage", &CairoContext::CopyPage),
      InstanceMethod("showPage", &CairoContext::ShowPage),
      InstanceMethod("getReferenceCount", &CairoContext::GetReferenceCount),
      InstanceMethod("setUserData", &CairoContext::SetUserData),
      InstanceMethod("getUserData", &CairoContext::GetUserData),
      InstanceMethod("copyPath", &CairoContext::CopyPath),
      InstanceMethod("copyPathFlat", &CairoContext::CopyPathFlat),
      InstanceMethod("appendPath", &CairoContext::AppendPath),
      InstanceMethod("hasCurrentPath", &CairoContext::HasCurrentPoint),
      InstanceMethod("newPath", &CairoContext::NewPath),
      InstanceMethod("newSubPath", &CairoContext::NewSubPath),
      InstanceMethod("closePath", &CairoContext::ClosePath),
      InstanceMethod("arc", &CairoContext::Arc),
      InstanceMethod("arcNegative", &CairoContext::ArcNegative),
      InstanceMethod("curveTo", &CairoContext::CurveTo),
      InstanceMethod("lineTo", &CairoContext::LineTo),
      InstanceMethod("moveTo", &CairoContext::MoveTo),
      InstanceMethod("rectangle", &CairoContext::Rectangle),
      InstanceMethod("glyphPath", &CairoContext::GlyphPath),
      InstanceMethod("relCurveTo", &CairoContext::RelCurveTo),
      InstanceMethod("relLineTo", &CairoContext::RelLineTo),
      InstanceMethod("relMoveTo", &CairoContext::RelMoveTo),
      InstanceMethod("pathExtents", &CairoContext::PathExtents),
      InstanceMethod("translate", &CairoContext::Translate),
      InstanceMethod("scale", &CairoContext::Scale),
      InstanceMethod("rotate", &CairoContext::Rotate),
      InstanceMethod("transform", &CairoContext::Transform),
      InstanceMethod("setMatrix", &CairoContext::SetMatrix),
      InstanceMethod("getMatrix", &CairoContext::GetMatrix),
      InstanceMethod("identityMatrix", &CairoContext::IdentityMatrix),
      InstanceMethod("userToDevice", &CairoContext::UserToDevice),
      InstanceMethod("userToDeviceDistance",
                     &CairoContext::UserToDeviceDistance),
      InstanceMethod("deviceToUser", &CairoContext::DeviceToUser),
      InstanceMethod("deviceToUserDistance",
                     &CairoContext::DeviceToUserDistance),
      InstanceMethod("selectFontFace", &CairoContext::SelectFontFace),
      InstanceMethod("setFontSize", &CairoContext::SetFontSize),
      InstanceMethod("setFontMatrix", &CairoContext::SetFontMatrix),
      InstanceMethod("getFontMatrix", &CairoContext::GetFontMatrix),
      InstanceMethod("setFontOptions", &CairoContext::SetFontOptions),
      InstanceMethod("getFontOptions", &CairoContext::GetFontOptions),
      InstanceMethod("setFontFace", &CairoContext::SetFontFace),
      InstanceMethod("getFontFace", &CairoContext::GetFontFace),
      InstanceMethod("setScaledFont", &CairoContext::SetScaledFont),
      InstanceMethod("getScaledFont", &CairoContext::GetScaledFont),
      InstanceMethod("showText", &CairoContext::ShowText),
      InstanceMethod("showGlyphs", &CairoContext::ShowGlyphs),
      InstanceMethod("showTextGlyphs", &CairoContext::ShowTextGlyphs),
      InstanceMethod("fontExtents", &CairoContext::FontExtents),
      InstanceMethod("textExtents", &CairoContext::TextExtents),
      InstanceMethod("glyphExtents", &CairoContext::GlyphExtents),
    });
  *contextConstructor = Napi::Persistent(func);
  exports.Set("CairoContext", func);
  return exports;
}

CairoContext::CairoContext(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoContext>(info)
{
  this->context_ = nullptr;
}

CairoContext::~CairoContext()
{
  if (this->context_) {
    cairo_destroy(this->context_);
    this->context_ = nullptr;
  }
}

Napi::Object
CairoContext::NewInstance(cairo_t* context)
{
  Napi::Object obj = contextConstructor->New({});
  CairoContext* ctx = Napi::ObjectWrap<CairoContext>::Unwrap(obj);
  ctx->SetContext(context);
  return obj;
}

bool
CairoContext::HasInstance(const Napi::Value& v)
{
  return v.IsObject() &&
         v.As<Napi::Object>().InstanceOf(contextConstructor->Value());
}

cairo_t*
CairoContext::GetContext()
{
  return this->context_;
}

void
CairoContext::SetContext(cairo_t* ctx)
{
  this->context_ = ctx;
}

Napi::Value
CairoContext::Create(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  // target surface
  if (!CairoSurface::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid target surface");
  }
  CairoSurface* surface =
    Napi::ObjectWrap<CairoSurface>::Unwrap(info[0].As<Napi::Object>());
  cairo_t* context = cairo_create(surface->GetSurface());
  return CairoContext::NewInstance(context);
}

Napi::Value
CairoContext::Reference(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_reference(this->context_);
  return info.This();
}

Napi::Value
CairoContext::Destroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  if (this->context_) {
    cairo_destroy(this->context_);
    this->context_ = nullptr;
  }
  return info.This();
}

Napi::Value
CairoContext::Status(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_status_t status = cairo_status(this->context_);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoContext::Save(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_save(this->context_);
  return info.This();
}

Napi::Value
CairoContext::Restore(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_restore(this->context_);
  return info.This();
}

Napi::Value
CairoContext::GetTarget(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_surface_t* s = cairo_get_target(this->context_);
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoContext::PushGroup(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_push_group(this->context_);
  return info.This();
}

Napi::Value
CairoContext::PushGroupWithContent(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "content", info[0])) {
    info.This();
  }
  int content = info[0].As<Napi::Number>();
  cairo_push_group_with_content(this->context_, (cairo_content_t)content);
  return info.This();
}

Napi::Value
CairoContext::PopGroup(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_pattern_t* pattern = cairo_pop_group(this->context_);
  return CairoPattern::NewInstance(pattern);
}

Napi::Value
CairoContext::PopGroupToSource(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_pop_group_to_source(this->context_);
  return info.This();
}

Napi::Value
CairoContext::GetGroupTarget(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_surface_t* s = cairo_get_group_target(this->context_);
  cairo_status_t status = cairo_surface_status(s);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get group target.", status);
  }
  return CairoSurface::NewInstance(s);
}

Napi::Value
CairoContext::SetSourceRgb(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return info.This();
  }
  // color
  if (!info[0].IsNumber() || !info[1].IsNumber() || !info[2].IsNumber()) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid color.");
  }
  double r = info[0].As<Napi::Number>();
  double g = info[1].As<Napi::Number>();
  double b = info[2].As<Napi::Number>();
  cairo_set_source_rgb(this->context_, r, g, b);
  return info.This();
}

Napi::Value
CairoContext::SetSourceRgba(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 4)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "r", info[0]) || !ParamIsNumber(env, "g", info[1]) ||
      !ParamIsNumber(env, "b", info[2]) || !ParamIsNumber(env, "a", info[3])) {
    return info.This();
  }
  double r = info[0].As<Napi::Number>();
  double g = info[0].As<Napi::Number>();
  double b = info[0].As<Napi::Number>();
  double a = info[0].As<Napi::Number>();
  cairo_set_source_rgba(this->context_, r, g, b, a);
  return info.This();
}

Napi::Value
CairoContext::SetSource(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoPattern::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid source.");
  }
  CairoPattern* pattern =
    Napi::ObjectWrap<CairoPattern>::Unwrap(info[0].As<Napi::Object>());
  cairo_set_source(this->context_, pattern->GetPattern());
  return info.This();
}

Napi::Value
CairoContext::SetSourceSurface(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return info.This();
  }
  // surface
  if (!CairoSurface::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid surface.");
  }
  CairoSurface* s =
    Napi::ObjectWrap<CairoSurface>::Unwrap(info[0].As<Napi::Object>());
  // x, y
  if (!ParamIsNumber(env, "x", info[1]) || !ParamIsNumber(env, "y", info[2])) {
    return info.This();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_set_source_surface(this->context_, s->GetSurface(), x, y);
  return info.This();
}

Napi::Value
CairoContext::GetSource(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_pattern_t* pattern = cairo_get_source(this->context_);
  return CairoPattern::NewInstance(pattern);
}

Napi::Value
CairoContext::SetAntialias(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "antialias", info[0])) {
    return info.This();
  }
  int antialias = info[0].As<Napi::Number>();
  cairo_set_antialias(this->context_, (cairo_antialias_t)antialias);
  return info.This();
}

Napi::Value
CairoContext::GetAntialias(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_antialias_t antialias = cairo_get_antialias(this->context_);
  return Napi::Number::New(env, antialias);
}

Napi::Value
CairoContext::SetDash(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  // dashes
  if (!ParamIsArray(env, "dashes", info[0])) {
    return info.This();
  }
  Napi::Float64Array dashes = info[0].As<Napi::Float64Array>();
  // offset
  if (!ParamIsNumber(env, "offset", info[1])) {
    return info.This();
  }
  double offset = info[1].As<Napi::Number>();
  cairo_set_dash(this->context_, dashes.Data(), dashes.ElementLength(), offset);
  return info.This();
}

Napi::Value
CairoContext::GetDashCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  int count = cairo_get_dash_count(this->context_);
  return Napi::Number::New(env, count);
}

Napi::Value
CairoContext::GetDash(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  int count = cairo_get_dash_count(this->context_);
  if (count == 0) {
    return env.Null();
  }
  Napi::Float64Array dashes = Napi::Float64Array::New(env, count);
  double offset;
  cairo_get_dash(this->context_, dashes.Data(), &offset);
  Napi::Object result;
  result.Set("dashes", dashes);
  result.Set("offset", Napi::Number::New(env, offset));
  return result;
}

Napi::Value
CairoContext::SetFillRule(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "fill rule", info[0])) {
    return info.This();
  }
  int rule = info[0].As<Napi::Number>();
  cairo_set_fill_rule(this->context_, (cairo_fill_rule_t)rule);
  return info.This();
}

Napi::Value
CairoContext::GetFillRule(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_fill_rule_t rule = cairo_get_fill_rule(this->context_);
  return Napi::Number::New(env, rule);
}

Napi::Value
CairoContext::SetLineCap(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  int cap = info[0].As<Napi::Number>();
  cairo_set_line_cap(this->context_, (cairo_line_cap_t)cap);
  return info.This();
}

Napi::Value
CairoContext::GetLineCap(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_line_cap_t cap = cairo_get_line_cap(this->context_);
  return Napi::Number::New(env, cap);
}

Napi::Value
CairoContext::SetLineJoin(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "line join type", info[0])) {
    return info.This();
  }
  int join = info[0].As<Napi::Number>();
  cairo_set_line_join(this->context_, (cairo_line_join_t)join);
  return info.This();
}

Napi::Value
CairoContext::GetLineJoin(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_line_join_t join = cairo_get_line_join(this->context_);
  return Napi::Number::New(env, join);
}

Napi::Value
CairoContext::SetLineWidth(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  // width
  if (!ParamIsNumber(env, "width", info[0])) {
    return info.This();
  }
  double width = info[0].As<Napi::Number>();
  cairo_set_line_width(this->context_, width);
  return info.This();
}

Napi::Value
CairoContext::GetLineWidth(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double width = cairo_get_line_width(this->context_);
  return Napi::Number::New(env, width);
}

Napi::Value
CairoContext::SetMiterLimit(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "miter limit", info[0])) {
    return info.This();
  }
  double limit = info[0].As<Napi::Number>();
  cairo_set_miter_limit(this->context_, limit);
  return info.This();
}

Napi::Value
CairoContext::GetMiterLimit(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double limit = cairo_get_miter_limit(this->context_);
  return Napi::Number::New(env, limit);
}

Napi::Value
CairoContext::SetOperator(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  int op = info[0].As<Napi::Number>();
  cairo_set_operator(this->context_, (cairo_operator_t)op);
  return info.This();
}

Napi::Value
CairoContext::GetOperator(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_operator_t op = cairo_get_operator(this->context_);
  return Napi::Number::New(env, op);
}

Napi::Value
CairoContext::SetTolerance(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "tolerance", info[0])) {
    return info.This();
  }
  double tolerance = info[0].As<Napi::Number>();
  cairo_set_tolerance(this->context_, tolerance);
  return info.This();
}

Napi::Value
CairoContext::GetTolerance(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double tolerance = cairo_get_tolerance(this->context_);
  return Napi::Number::New(env, tolerance);
}

Napi::Value
CairoContext::Clip(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_clip(this->context_);
  return info.This();
}

Napi::Value
CairoContext::ClipPreserve(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_clip_preserve(this->context_);
  return info.This();
}

Napi::Value
CairoContext::ClipExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double x1, y1, x2, y2;
  cairo_clip_extents(this->context_, &x1, &y1, &x2, &y2);
  Napi::Object result;
  result.Set("x1", Napi::Number::New(env, x1));
  result.Set("y1", Napi::Number::New(env, y1));
  result.Set("x2", Napi::Number::New(env, x2));
  result.Set("y2", Napi::Number::New(env, y2));
  return result;
}

Napi::Value
CairoContext::InClip(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_bool_t in = cairo_in_clip(this->context_, x, y);
  return Napi::Boolean::New(env, in);
}

Napi::Value
CairoContext::ResetClip(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_reset_clip(this->context_);
  return info.This();
}

Napi::Value
CairoContext::RectangleListDestroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoContext::CopyClipRectangleList(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoContext::Fill(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_fill(this->context_);
  return info.This();
}

Napi::Value
CairoContext::FillPreserve(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_fill_preserve(this->context_);
  return info.This();
}

Napi::Value
CairoContext::FillExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double x1, y1, x2, y2;
  cairo_fill_extents(this->context_, &x1, &y1, &x2, &y2);
  Napi::Object result;
  result.Set("x1", Napi::Number::New(env, x1));
  result.Set("y1", Napi::Number::New(env, y1));
  result.Set("x2", Napi::Number::New(env, x2));
  result.Set("y2", Napi::Number::New(env, y2));
  return result;
}

Napi::Value
CairoContext::InFill(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_bool_t in = cairo_in_fill(this->context_, x, y);
  return Napi::Boolean::New(env, in);
}

Napi::Value
CairoContext::Mask(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!CairoPattern::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid pattern.");
  }
  CairoPattern* p =
    Napi::ObjectWrap<CairoPattern>::Unwrap(info[0].As<Napi::Object>());
  cairo_mask(this->context_, p->GetPattern());
  return info.This();
}

Napi::Value
CairoContext::MaskSurface(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return info.This();
  }
  if (!CairoSurface::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid surface.");
  }
  CairoSurface* surface =
    Napi::ObjectWrap<CairoSurface>::Unwrap(info[0].As<Napi::Object>());
  if (!ParamIsNumber(env, "x", info[1]) || !ParamIsNumber(env, "y", info[2])) {
    return info.This();
  }
  double x = info[1].As<Napi::Number>();
  double y = info[2].As<Napi::Number>();
  cairo_mask_surface(this->context_, surface->GetSurface(), x, y);
  return info.This();
}

Napi::Value
CairoContext::Paint(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_paint(this->context_);
  return info.This();
}

Napi::Value
CairoContext::PaintWithAlpha(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "alpha", info[0])) {
    return info.This();
  }
  double alpha = info[0].As<Napi::Number>();
  cairo_paint_with_alpha(this->context_, alpha);
  return info.This();
}

Napi::Value
CairoContext::Stroke(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_stroke(this->context_);
  return info.This();
}

Napi::Value
CairoContext::StrokePreserve(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_stroke_preserve(this->context_);
  return info.This();
}

Napi::Value
CairoContext::StrokeExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double x1, y1, x2, y2;
  cairo_stroke_extents(this->context_, &x1, &y1, &x2, &y2);
  Napi::Object result;
  result.Set("x1", Napi::Number::New(env, x1));
  result.Set("y1", Napi::Number::New(env, y1));
  result.Set("x2", Napi::Number::New(env, x2));
  result.Set("y2", Napi::Number::New(env, y2));
  return result;
}

Napi::Value
CairoContext::InStroke(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_bool_t in = cairo_in_stroke(this->context_, x, y);
  return Napi::Boolean::New(env, in);
}

Napi::Value
CairoContext::CopyPage(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_copy_page(this->context_);
  return info.This();
}

Napi::Value
CairoContext::ShowPage(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_show_page(this->context_);
  return info.This();
}

Napi::Value
CairoContext::GetReferenceCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  unsigned int count = cairo_get_reference_count(this->context_);
  return Napi::Number::New(env, count);
}

Napi::Value
CairoContext::SetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoContext::GetUserData(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoContext::CopyPath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_path_t* path = cairo_copy_path(this->context_);
  if (path->data == nullptr && path->num_data == 0) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to copy path.", path->status);
  }
  return CairoPath::NewInstance(path);
}

Napi::Value
CairoContext::CopyPathFlat(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_path_t* path = cairo_copy_path_flat(this->context_);
  if (path->data == nullptr && path->num_data == 0) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to copy path flat.", path->status);
  }
  return CairoPath::NewInstance(path);
}

Napi::Value
CairoContext::AppendPath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!CairoPath::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid path.");
  }
  CairoPath* path =
    Napi::ObjectWrap<CairoPath>::Unwrap(info[0].As<Napi::Object>());
  cairo_append_path(this->context_, path->GetPath());
  return info.This();
}

Napi::Value
CairoContext::HasCurrentPoint(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_bool_t has = cairo_has_current_point(this->context_);
  return Napi::Boolean::New(env, has);
}

Napi::Value
CairoContext::NewPath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_new_path(this->context_);
  return info.This();
}

Napi::Value
CairoContext::NewSubPath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_new_sub_path(this->context_);
  return info.This();
}

Napi::Value
CairoContext::ClosePath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_close_path(this->context_);
  return info.This();
}

Napi::Value
CairoContext::Arc(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 5)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1]) ||
      !ParamIsNumber(env, "radius", info[2]) ||
      !ParamIsNumber(env, "start angle", info[3]) ||
      !ParamIsNumber(env, "end angle", info[4])) {
    return info.This();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  double radius = info[2].As<Napi::Number>();
  double start = info[3].As<Napi::Number>();
  double end = info[4].As<Napi::Number>();
  cairo_arc(this->context_, x, y, radius, start, end);
  return info.This();
}

Napi::Value
CairoContext::ArcNegative(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 5)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1]) ||
      !ParamIsNumber(env, "radius", info[2]) ||
      !ParamIsNumber(env, "start angle", info[3]) ||
      !ParamIsNumber(env, "end angle", info[4])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  double radius = info[2].As<Napi::Number>();
  double start = info[3].As<Napi::Number>();
  double end = info[4].As<Napi::Number>();
  cairo_arc_negative(this->context_, x, y, radius, start, end);
  return info.This();
}

Napi::Value
CairoContext::CurveTo(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 6)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "x1", info[0]) ||
      !ParamIsNumber(env, "y1", info[1]) ||
      !ParamIsNumber(env, "x2", info[2]) ||
      !ParamIsNumber(env, "y2", info[3]) ||
      !ParamIsNumber(env, "x3", info[4]) ||
      !ParamIsNumber(env, "y3", info[5])) {
    return info.This();
  }
  double x1 = info[0].As<Napi::Number>();
  double y1 = info[1].As<Napi::Number>();
  double x2 = info[2].As<Napi::Number>();
  double y2 = info[3].As<Napi::Number>();
  double x3 = info[4].As<Napi::Number>();
  double y3 = info[5].As<Napi::Number>();
  cairo_curve_to(this->context_, x1, y1, x2, y2, x3, y3);
  return info.This();
}

Napi::Value
CairoContext::LineTo(const Napi::CallbackInfo& info)
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
  cairo_line_to(this->context_, x, y);
  return info.This();
}

Napi::Value
CairoContext::MoveTo(const Napi::CallbackInfo& info)
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
  cairo_move_to(this->context_, x, y);
  return info.This();
}

Napi::Value
CairoContext::Rectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 4)) {
    return info.This();
  }
  // x
  if (!ParamIsNumber(env, "x", info[0])) {
    return info.This();
  }
  double x = info[0].As<Napi::Number>();
  // y
  if (!ParamIsNumber(env, "y", info[1])) {
    return info.This();
  }
  double y = info[1].As<Napi::Number>();
  // width
  if (!ParamIsNumber(env, "width", info[2])) {
    return info.This();
  }
  double width = info[2].As<Napi::Number>();
  // height
  if (!ParamIsNumber(env, "height", info[3])) {
    return info.This();
  }
  double height = info[3].As<Napi::Number>();
  cairo_rectangle(this->context_, x, y, width, height);
  return info.This();
}

Napi::Value
CairoContext::GlyphPath(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsArray(env, "glyphs", info[0])) {
    return info.This();
  }
  Napi::Array glyphs = info[0].As<Napi::Array>();
  vector<cairo_glyph_t> gs;
  for (uint32_t i = 0; i < glyphs.Length(); i++) {
    Napi::Object g = glyphs.Get(i).As<Napi::Object>();
    gs.push_back(
      cairo_glyph_t{ .index = g.Get("index").As<Napi::Number>().Uint32Value(),
                     .x = g.Get("x").As<Napi::Number>(),
                     .y = g.Get("y").As<Napi::Number>() });
  }
  cairo_glyph_path(this->context_, gs.data(), gs.size());
  return info.This();
}

Napi::Value
CairoContext::RelCurveTo(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 6)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "dx1", info[0]) ||
      !ParamIsNumber(env, "dy1", info[1]) ||
      !ParamIsNumber(env, "dx2", info[2]) ||
      !ParamIsNumber(env, "dy2", info[3]) ||
      !ParamIsNumber(env, "dx3", info[4]) ||
      !ParamIsNumber(env, "dy3", info[5])) {
    return info.This();
  }
  double dx1 = info[0].As<Napi::Number>();
  double dy1 = info[1].As<Napi::Number>();
  double dx2 = info[2].As<Napi::Number>();
  double dy2 = info[3].As<Napi::Number>();
  double dx3 = info[4].As<Napi::Number>();
  double dy3 = info[5].As<Napi::Number>();
  cairo_rel_curve_to(this->context_, dx1, dy1, dx2, dy2, dx3, dy3);
  return info.This();
}

Napi::Value
CairoContext::RelLineTo(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "dx", info[0]) ||
      !ParamIsNumber(env, "dy", info[1])) {
    return info.This();
  }
  double dx = info[0].As<Napi::Number>();
  double dy = info[1].As<Napi::Number>();
  cairo_rel_line_to(this->context_, dx, dy);
  return info.This();
}

Napi::Value
CairoContext::RelMoveTo(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "dx", info[0]) ||
      !ParamIsNumber(env, "dy", info[1])) {
    return info.This();
  }
  double dx = info[0].As<Napi::Number>();
  double dy = info[1].As<Napi::Number>();
  cairo_rel_move_to(this->context_, dx, dy);
  return info.This();
}

Napi::Value
CairoContext::PathExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double x1, y1, x2, y2;
  cairo_path_extents(this->context_, &x1, &y1, &x2, &y2);
  Napi::Object result;
  result.Set("x1", Napi::Number::New(env, x1));
  result.Set("y1", Napi::Number::New(env, y1));
  result.Set("x2", Napi::Number::New(env, x2));
  result.Set("y2", Napi::Number::New(env, y2));
  return result;
}

Napi::Value
CairoContext::Translate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_translate(this->context_, x, y);
  return info.This();
}

Napi::Value
CairoContext::Scale(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_scale(this->context_, x, y);
  return info.This();
}

Napi::Value
CairoContext::Rotate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "angle", info[0])) {
    return env.Undefined();
  }
  double angle = info[0].As<Napi::Number>();
  cairo_rotate(this->context_, angle);
  return info.This();
}

Napi::Value
CairoContext::Transform(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[0])) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  ObjectToMatrix(info[0].As<Napi::Object>(), &matrix);
  cairo_transform(this->context_, &matrix);
  return info.This();
}

Napi::Value
CairoContext::SetMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[0])) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  ObjectToMatrix(info[0].As<Napi::Object>(), &matrix);
  cairo_set_matrix(this->context_, &matrix);
  return info.This();
}

Napi::Value
CairoContext::GetMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  cairo_get_matrix(this->context_, &matrix);
  Napi::Object result;
  MatrixToObject(env, matrix, &result);
  return result;
}

Napi::Value
CairoContext::IdentityMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_identity_matrix(this->context_);
  return info.This();
}

Napi::Value
CairoContext::UserToDevice(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_user_to_device(this->context_, &x, &y);
  Napi::Object result;
  result.Set("x", Napi::Number::New(env, x));
  result.Set("y", Napi::Number::New(env, y));
  return result;
}

Napi::Value
CairoContext::UserToDeviceDistance(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "dx", info[0]) ||
      !ParamIsNumber(env, "dy", info[1])) {
    return env.Undefined();
  }
  double dx = info[0].As<Napi::Number>();
  double dy = info[1].As<Napi::Number>();
  cairo_user_to_device_distance(this->context_, &dx, &dy);
  Napi::Object result;
  result.Set("dx", Napi::Number::New(env, dx));
  result.Set("dy", Napi::Number::New(env, dy));
  return result;
}

Napi::Value
CairoContext::DeviceToUser(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  double x = info[0].As<Napi::Number>();
  double y = info[1].As<Napi::Number>();
  cairo_device_to_user(this->context_, &x, &y);
  Napi::Object result;
  result.Set("x", Napi::Number::New(env, x));
  result.Set("y", Napi::Number::New(env, y));
  return result;
}

Napi::Value
CairoContext::DeviceToUserDistance(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "dx", info[0]) ||
      !ParamIsNumber(env, "dy", info[1])) {
    return env.Undefined();
  }
  double dx = info[0].As<Napi::Number>();
  double dy = info[1].As<Napi::Number>();
  Napi::Object result;
  result.Set("dx", Napi::Number::New(env, dx));
  result.Set("dy", Napi::Number::New(env, dy));
  return result;
}

Napi::Value
CairoContext::SelectFontFace(const Napi::CallbackInfo& info)
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
  cairo_select_font_face(this->context_,
                         family.c_str(),
                         (cairo_font_slant_t)slant,
                         (cairo_font_weight_t)weight);
  return info.This();
}

Napi::Value
CairoContext::SetFontSize(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "font size", info[0])) {
    return env.Undefined();
  }
  double size = info[0].As<Napi::Number>();
  cairo_set_font_size(this->context_, size);
  return info.This();
}

Napi::Value
CairoContext::SetFontMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1) ||
      !ParamIsMatrix(env, "matrix", info[0])) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  ObjectToMatrix(info[0].As<Napi::Object>(), &matrix);
  cairo_set_font_matrix(this->context_, &matrix);
  return info.This();
}

Napi::Value
CairoContext::GetFontMatrix(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_matrix_t matrix;
  cairo_get_font_matrix(this->context_, &matrix);
  Napi::Object result;
  MatrixToObject(env, matrix, &result);
  return result;
}

Napi::Value
CairoContext::SetFontOptions(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoFontOptions::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid font options.");
  }
  CairoFontOptions* options =
    Napi::ObjectWrap<CairoFontOptions>::Unwrap(info[0].As<Napi::Object>());
  cairo_set_font_options(this->context_, options->GetOptions());
  return info.This();
}

Napi::Value
CairoContext::GetFontOptions(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_options_t* options = cairo_font_options_create();
  cairo_get_font_options(this->context_, options);
  return CairoFontOptions::NewInstance(options);
}

Napi::Value
CairoContext::SetFontFace(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoFontFace::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid font face.");
  }
  CairoFontFace* face =
    Napi::ObjectWrap<CairoFontFace>::Unwrap(info[0].As<Napi::Object>());
  cairo_set_font_face(this->context_, face->GetFontFace());
  return info.This();
}

Napi::Value
CairoContext::GetFontFace(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_face_t* face = cairo_get_font_face(this->context_);
  cairo_status_t status = cairo_font_face_status(face);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get font face.", status);
  }
  return CairoFontFace::NewInstance(face);
}

Napi::Value
CairoContext::SetScaledFont(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoScaledFont::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid scaled font.");
  }
  CairoScaledFont* sf =
    Napi::ObjectWrap<CairoScaledFont>::Unwrap(info[0].As<Napi::Object>());
  cairo_set_scaled_font(this->context_, sf->GetScaledFont());
  return info.This();
}

Napi::Value
CairoContext::GetScaledFont(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_scaled_font_t* sf = cairo_get_scaled_font(this->context_);
  cairo_status_t status = cairo_scaled_font_status(sf);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to get scaled font.", status);
  }
  return CairoScaledFont::NewInstance(sf);
}

Napi::Value
CairoContext::ShowText(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1) ||
      !ParamIsString(env, "text", info[0])) {
    return env.Undefined();
  }
  string text = info[0].As<Napi::String>();
  cairo_show_text(this->context_, text.c_str());
  return info.This();
}

Napi::Value
CairoContext::ShowGlyphs(const Napi::CallbackInfo& info)
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
    Napi::Object obj = arr.Get(i).As<Napi::Object>();
    cairo_glyph_t g;
    ObjectToGlyph(obj, &g);
    glyphs.push_back(g);
  }
  cairo_show_glyphs(this->context_, glyphs.data(), glyphs.size());
  return info.This();
}

Napi::Value
CairoContext::ShowTextGlyphs(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoContext::FontExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_font_extents_t extents;
  cairo_font_extents(this->context_, &extents);
  Napi::Object result;
  FontExtentsToObject(env, extents, &result);
  return result;
}

Napi::Value
CairoContext::TextExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1) ||
      !ParamIsString(env, "text", info[0])) {
    return env.Undefined();
  }
  string text = info[0].As<Napi::String>();
  cairo_text_extents_t extents;
  cairo_text_extents(this->context_, text.c_str(), &extents);
  Napi::Object result;
  TextExtentsToObject(env, &extents, &result);
  return result;
}

Napi::Value
CairoContext::GlyphExtents(const Napi::CallbackInfo& info)
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
    Napi::Object obj = arr.Get(i).As<Napi::Object>();
    cairo_glyph_t g;
    ObjectToGlyph(obj, &g);
    glyphs.push_back(g);
  }
  cairo_text_extents_t extents;
  cairo_glyph_extents(this->context_, glyphs.data(), glyphs.size(), &extents);
  Napi::Object result;
  TextExtentsToObject(env, &extents, &result);
  return result;
}