#include "node-pango-layout-line.h"
#include "node-cairo-utils.h"

static Napi::FunctionReference* pangoLayoutLineCtor =
  new Napi::FunctionReference();

Napi::Object
NodePangoLayoutLine::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "PangoLayoutLine",
    {
      InstanceMethod("ref", &NodePangoLayoutLine::Ref),
      InstanceMethod("unref", &NodePangoLayoutLine::Unref),
      InstanceMethod("getExtents", &NodePangoLayoutLine::GetExtents),
      InstanceMethod("getPixelExtents", &NodePangoLayoutLine::GetPixelExtents),
      InstanceMethod("indexToX", &NodePangoLayoutLine::IndexToX),
      InstanceMethod("xToIndex", &NodePangoLayoutLine::XToIndex),
      InstanceMethod("getXRanges", &NodePangoLayoutLine::GetXRanges),
      InstanceMethod("getHeight", &NodePangoLayoutLine::GetHeight),
    });
  *pangoLayoutLineCtor = Napi::Persistent(func);
  exports.Set("PangoLayoutLine", func);
  return exports;
}

NodePangoLayoutLine::NodePangoLayoutLine(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<NodePangoLayoutLine>(info)
{
  this->line_ = nullptr;
}

NodePangoLayoutLine::~NodePangoLayoutLine() {}

Napi::Object
NodePangoLayoutLine::NewInstance(PangoLayoutLine* line)
{
  Napi::Object obj = pangoLayoutLineCtor->New({});
  NodePangoLayoutLine* l = Napi::ObjectWrap<NodePangoLayoutLine>::Unwrap(obj);
  l->SetLine(line);
  return obj;
}

bool
NodePangoLayoutLine::HasInstance(const Napi::Value& v)
{
  return v.IsObject() &&
         v.As<Napi::Object>().InstanceOf(pangoLayoutLineCtor->Value());
}

PangoLayoutLine*
NodePangoLayoutLine::GetLine()
{
  return this->line_;
}

void
NodePangoLayoutLine::SetLine(PangoLayoutLine* line)
{
  this->line_ = line;
}

Napi::Value
NodePangoLayoutLine::Ref(const Napi::CallbackInfo& info)
{
  pango_layout_line_ref(this->line_);
  return info.This();
}

Napi::Value
NodePangoLayoutLine::Unref(const Napi::CallbackInfo& info)
{
  pango_layout_line_unref(this->line_);
  return info.This();
}

Napi::Value
NodePangoLayoutLine::GetExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle ink, logical;
  PangoRectangle *inkPtr = &ink, *logicalPtr = &logical;
  pango_layout_line_get_extents(this->line_, inkPtr, logicalPtr);
  Napi::Object result = Napi::Object::New(env);
  if (inkPtr) {
    Napi::Object inkObj = Napi::Object::New(env);
    PangoRectangleToObject(env, &ink, &inkObj);
    result.Set("ink", inkObj);
  } else {
    result.Set("ink", env.Null());
  }
  if (logicalPtr) {
    Napi::Object logicalObj = Napi::Object::New(env);
    PangoRectangleToObject(env, &logical, &logicalObj);
    result.Set("logical", logicalObj);
  } else {
    result.Set("logical", env.Null());
  }
  return result;
}

Napi::Value
NodePangoLayoutLine::GetPixelExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle ink, logical;
  PangoRectangle *inkPtr = &ink, *logicalPtr = &logical;
  pango_layout_line_get_pixel_extents(this->line_, inkPtr, logicalPtr);
  Napi::Object result = Napi::Object::New(env);
  if (inkPtr) {
    Napi::Object inkObj = Napi::Object::New(env);
    PangoRectangleToObject(env, &ink, &inkObj);
    result.Set("ink", inkObj);
  } else {
    result.Set("ink", env.Null());
  }
  if (logicalPtr) {
    Napi::Object logicalObj = Napi::Object::New(env);
    PangoRectangleToObject(env, &logical, &logicalObj);
    result.Set("logical", logicalObj);
  } else {
    result.Set("logical", env.Null());
  }
  return result;
}

Napi::Value
NodePangoLayoutLine::IndexToX(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "index", env) ||
      !ParamIsBoolean(info[1], "trailing", env)) {
    return env.Undefined();
  }
  int index = info[0].As<Napi::Number>();
  gboolean trailing = info[1].As<Napi::Boolean>();
  int x;
  pango_layout_line_index_to_x(this->line_, index, trailing, &x);
  return Napi::Number::New(env, x);
}

Napi::Value
NodePangoLayoutLine::XToIndex(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "x", env)) {
    return env.Undefined();
  }
  int x = info[0].As<Napi::Number>();
  int index, trailing;
  pango_layout_line_x_to_index(this->line_, x, &index, &trailing);
  Napi::Object result = Napi::Object::New(env);
  result.Set("index", Napi::Number::New(env, index));
  result.Set("trailing", Napi::Number::New(env, trailing));
  return result;
}

Napi::Value
NodePangoLayoutLine::GetXRanges(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "start index", env) ||
      !ParamIsNumber(info[1], "end index", env)) {
    return env.Undefined();
  }
  int start = info[0].As<Napi::Number>(), end = info[1].As<Napi::Number>();
  int *ranges, n;
  pango_layout_line_get_x_ranges(this->line_, start, end, &ranges, &n);
  Napi::Array result = Napi::Array::New(env, n);
  for (int i = 0; i < n; i++) {
    Napi::Array item = Napi::Array::New(env, 2);
    item.Set("0", Napi::Number::New(env, ranges[2 * i]));
    item.Set("1", Napi::Number::New(env, ranges[2 * i + 1]));
    result.Set(i, item);
  }
  return result;
}

Napi::Value
NodePangoLayoutLine::GetHeight(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int h;
  pango_layout_line_get_height(this->line_, &h);
  return Napi::Number::New(env, h);
}