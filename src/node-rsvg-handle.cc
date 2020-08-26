#include "node-rsvg-handle.h"
#include "node-cairo-context.h"
#include "node-cairo-utils.h"

using namespace std;

static Napi::FunctionReference* rsvgHandleCtor = new Napi::FunctionReference();

Napi::Object
NodeRsvgHandle::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "RsvgHandle",
    {
      StaticMethod("newFromFile", &NodeRsvgHandle::NewFromFile),
      InstanceMethod("getIntrinsicDimensions",
                     &NodeRsvgHandle::GetIntrinsicDimensions),
      InstanceMethod("renderDocument", &NodeRsvgHandle::RenderDocument),
      InstanceMethod("setStylesheet", &NodeRsvgHandle::SetStylesheet),
    });
  *rsvgHandleCtor = Napi::Persistent(func);
  exports.Set("RsvgHandle", func);
  return exports;
}

NodeRsvgHandle::NodeRsvgHandle(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<NodeRsvgHandle>(info)
{
  this->handle_ = nullptr;
}

NodeRsvgHandle::~NodeRsvgHandle() {}

Napi::Object
NodeRsvgHandle::NewInstance(RsvgHandle* handle)
{
  Napi::Object obj = rsvgHandleCtor->New({});
  NodeRsvgHandle* h = Napi::ObjectWrap<NodeRsvgHandle>::Unwrap(obj);
  h->handle_ = handle;
  return obj;
}

bool
NodeRsvgHandle::HasInstance(const Napi::Value& v)
{
  return v.IsObject() &&
         v.As<Napi::Object>().InstanceOf(rsvgHandleCtor->Value());
}

void
NodeRsvgHandle::SetHandle(RsvgHandle* handle)
{
  this->handle_ = handle;
}

RsvgHandle*
NodeRsvgHandle::GetHandle()
{
  return this->handle_;
}

Napi::Value
NodeRsvgHandle::NewFromFile(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsString(info[0], "filename", env)) {
    return env.Undefined();
  }
  string filename = info[0].As<Napi::String>();
  GError** err = nullptr;
  RsvgHandle* handle = rsvg_handle_new_from_file(filename.c_str(), err);
  if (err != nullptr) {
    return ThrowErrorAsJavaScriptException(
      env, "Fail to create RsvgHandle from file.");
  }
  return NodeRsvgHandle::NewInstance(handle);
}

Napi::Value
NodeRsvgHandle::GetIntrinsicDimensions(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 0, env)) {
    return env.Undefined();
  }
  gboolean hasWidth, hasHeight, hasViewbox;
  RsvgLength width, height;
  RsvgRectangle viewbox;
  rsvg_handle_get_intrinsic_dimensions(this->handle_,
                                       &hasWidth,
                                       &width,
                                       &hasHeight,
                                       &height,
                                       &hasViewbox,
                                       &viewbox);
  Napi::Object result = Napi::Object::New(env);
  if (hasWidth) {
    Napi::Object w = Napi::Object::New(env);
    RsvgLengthToObject(env, &width, &w);
    result.Set("width", w);
  } else {
    result.Set("width", env.Null());
  }
  if (hasHeight) {
    Napi::Object h = Napi::Object::New(env);
    RsvgLengthToObject(env, &height, &h);
    result.Set("height", h);
  } else {
    result.Set("height", env.Null());
  }
  if (hasViewbox) {
    Napi::Object vb = Napi::Object::New(env);
    RsvgRectangleToObject(env, &viewbox, &vb);
    result.Set("viewbox", vb);
  } else {
    result.Set("viewbox", env.Null());
  }
  return result;
}

Napi::Value
NodeRsvgHandle::RenderDocument(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!CairoContext::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid CairoContext");
  }
  CairoContext* ctx =
    Napi::ObjectWrap<CairoContext>::Unwrap(info[0].As<Napi::Object>());
  if (!ParamIsRsvgRectangle(info[1], "viewport", env)) {
    return env.Undefined();
  }
  Napi::Object rectObj = info[1].As<Napi::Object>();
  RsvgRectangle rect;
  ObjectToRsvgRectangle(env, &rectObj, &rect);
  GError** err = nullptr;
  gboolean success =
    rsvg_handle_render_document(this->handle_, ctx->GetContext(), &rect, err);
  if (!success || err != nullptr) {
    return ThrowErrorAsJavaScriptException(env, "Fail to render SVG document");
  }
  return info.This();
}

Napi::Value
NodeRsvgHandle::SetStylesheet(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  string css = info[0].As<Napi::String>();
  GError** err = nullptr;
  gboolean success = rsvg_handle_set_stylesheet(
    this->handle_, (guint8*)(css.c_str()), css.length(), err);
  if (!success) {
    ThrowErrorAsJavaScriptException(env, (*err)->message);
  }
  return info.This();
}