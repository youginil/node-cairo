#include "node-pango-layout-iter.h"
#include "node-cairo-utils.h"
#include "node-pango-layout-line.h"
#include "node-pango-layout.h"

static Napi::FunctionReference* pangoLayoutIterCtor =
  new Napi::FunctionReference();

Napi::Object
NodePangoLayoutIter::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "PangoLayoutIter",
    {
      InstanceMethod("copy", &NodePangoLayoutIter::Copy),
      InstanceMethod("free", &NodePangoLayoutIter::Free),
      InstanceMethod("nextRun", &NodePangoLayoutIter::NextRun),
      InstanceMethod("nextChar", &NodePangoLayoutIter::NextChar),
      InstanceMethod("nextCluster", &NodePangoLayoutIter::NextCluster),
      InstanceMethod("nextLine", &NodePangoLayoutIter::NextLine),
      InstanceMethod("atLastLine", &NodePangoLayoutIter::AtLastLine),
      InstanceMethod("getIndex", &NodePangoLayoutIter::GetIndex),
      InstanceMethod("getBaseline", &NodePangoLayoutIter::GetBaseline),
      InstanceMethod("getLine", &NodePangoLayoutIter::GetLine),
      InstanceMethod("getLineReadonly", &NodePangoLayoutIter::GetLineReadonly),
      InstanceMethod("getLayout", &NodePangoLayoutIter::GetLayout),
      InstanceMethod("getCharExtents", &NodePangoLayoutIter::GetCharExtents),
      InstanceMethod("getClusterExtents",
                     &NodePangoLayoutIter::GetClusterExtents),
      InstanceMethod("getRunExtents", &NodePangoLayoutIter::GetRunExtents),
      InstanceMethod("getLineYRange", &NodePangoLayoutIter::GetLineYRange),
      InstanceMethod("getLineExtents", &NodePangoLayoutIter::GetLineExtents),
      InstanceMethod("getLayoutExtents",
                     &NodePangoLayoutIter::GetLayoutExtents),
    });
  *pangoLayoutIterCtor = Napi::Persistent(func);
  exports.Set("PangoLayoutIter", func);
  return exports;
}

NodePangoLayoutIter::NodePangoLayoutIter(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<NodePangoLayoutIter>(info)
{
  this->iter_ = nullptr;
}

NodePangoLayoutIter::~NodePangoLayoutIter()
{
  if (this->iter_) {
    pango_layout_iter_free(this->iter_);
    this->iter_ = nullptr;
  }
}

Napi::Object
NodePangoLayoutIter::NewInstance(PangoLayoutIter* iter)
{
  Napi::Object obj = pangoLayoutIterCtor->New({});
  NodePangoLayoutIter* it = Napi::ObjectWrap<NodePangoLayoutIter>::Unwrap(obj);
  it->SetIter(iter);
  return obj;
}

bool
NodePangoLayoutIter::HasInstance(const Napi::Value& v)
{
  return v.IsObject() &&
         v.As<Napi::Object>().InstanceOf(pangoLayoutIterCtor->Value());
}

PangoLayoutIter*
NodePangoLayoutIter::GetIter()
{
  return this->iter_;
}

void
NodePangoLayoutIter::SetIter(PangoLayoutIter* iter)
{
  this->iter_ = iter;
}

Napi::Value
NodePangoLayoutIter::Copy(const Napi::CallbackInfo& info)
{
  PangoLayoutIter* iter = pango_layout_iter_copy(this->iter_);
  return NodePangoLayoutIter::NewInstance(iter);
}

Napi::Value
NodePangoLayoutIter::Free(const Napi::CallbackInfo& info)
{
  if (this->iter_) {
    pango_layout_iter_free(this->iter_);
    this->iter_ = nullptr;
  }
  return info.This();
}

Napi::Value
NodePangoLayoutIter::NextRun(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean success = pango_layout_iter_next_run(this->iter_);
  return Napi::Boolean::New(env, success);
}

Napi::Value
NodePangoLayoutIter::NextChar(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean success = pango_layout_iter_next_char(this->iter_);
  return Napi::Boolean::New(env, success);
}

Napi::Value
NodePangoLayoutIter::NextCluster(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean success = pango_layout_iter_next_cluster(this->iter_);
  return Napi::Boolean::New(env, success);
}

Napi::Value
NodePangoLayoutIter::NextLine(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean success = pango_layout_iter_next_line(this->iter_);
  return Napi::Boolean::New(env, success);
}

Napi::Value
NodePangoLayoutIter::AtLastLine(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean y = pango_layout_iter_at_last_line(this->iter_);
  return Napi::Boolean::New(env, y);
}

Napi::Value
NodePangoLayoutIter::GetIndex(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int index = pango_layout_iter_get_index(this->iter_);
  return Napi::Number::New(env, index);
}

Napi::Value
NodePangoLayoutIter::GetBaseline(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int y = pango_layout_iter_get_baseline(this->iter_);
  return Napi::Number::New(env, y);
}

Napi::Value
NodePangoLayoutIter::GetLine(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoLayoutLine* line = pango_layout_iter_get_line(this->iter_);
  if (!line) {
    return env.Null();
  }
  return NodePangoLayoutLine::NewInstance(line);
}

Napi::Value
NodePangoLayoutIter::GetLineReadonly(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoLayoutLine* line = pango_layout_iter_get_line_readonly(this->iter_);
  if (!line) {
    return env.Null();
  }
  return NodePangoLayoutLine::NewInstance(line);
}

Napi::Value
NodePangoLayoutIter::GetLayout(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoLayout* layout = pango_layout_iter_get_layout(this->iter_);
  if (!layout) {
    return env.Null();
  }
  return NodePangoLayout::NewInstance(layout);
}

Napi::Value
NodePangoLayoutIter::GetCharExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle rect;
  pango_layout_iter_get_char_extents(this->iter_, &rect);
  Napi::Object result = Napi::Object::New(env);
  PangoRectangleToObject(env, &rect, &result);
  return result;
}

Napi::Value
NodePangoLayoutIter::GetClusterExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle ink, logical;
  PangoRectangle *inkPtr = &ink, *logicalPtr = &logical;
  pango_layout_iter_get_cluster_extents(this->iter_, inkPtr, logicalPtr);
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
NodePangoLayoutIter::GetRunExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle ink, logical;
  PangoRectangle *inkPtr = &ink, *logicalPtr = &logical;
  pango_layout_iter_get_run_extents(this->iter_, inkPtr, logicalPtr);
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
NodePangoLayoutIter::GetLineYRange(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int y0, y1;
  pango_layout_iter_get_line_yrange(this->iter_, &y0, &y1);
  Napi::Array result = Napi::Array::New(env, 2);
  result.Set("0", Napi::Number::New(env, y0));
  result.Set("1", Napi::Number::New(env, y1));
  return result;
}

Napi::Value
NodePangoLayoutIter::GetLineExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle ink, logical;
  PangoRectangle *inkPtr = &ink, *logicalPtr = &logical;
  pango_layout_iter_get_line_extents(this->iter_, inkPtr, logicalPtr);
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
NodePangoLayoutIter::GetLayoutExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle ink, logical;
  PangoRectangle *inkPtr = &ink, *logicalPtr = &logical;
  pango_layout_iter_get_layout_extents(this->iter_, inkPtr, logicalPtr);
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