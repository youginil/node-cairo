#include "node-cairo-device.h"
#include "cairo-script.h"
#include "node-cairo-utils.h"

using namespace std;

static Napi::FunctionReference* deviceConstructor =
  new Napi::FunctionReference();

Napi::Object
CairoDevice::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "CairoDevice",
    {
      InstanceMethod("reference", &CairoDevice::Reference),
      InstanceMethod("destroy", &CairoDevice::Destroy),
      InstanceMethod("status", &CairoDevice::Status),
      InstanceMethod("finish", &CairoDevice::Finish),
      InstanceMethod("flush", &CairoDevice::Flush),
      InstanceMethod("getType", &CairoDevice::GetType),
      InstanceMethod("getReferenceCount", &CairoDevice::GetReferenceCount),
      InstanceMethod("setUserData", &CairoDevice::SetUserData),
      InstanceMethod("getUserData", &CairoDevice::GetUserData),
      InstanceMethod("acquire", &CairoDevice::Acquire),
      InstanceMethod("release", &CairoDevice::Release),
      InstanceMethod("observerElapsed", &CairoDevice::ObserverElapsed),
      InstanceMethod("observerFillElapsed", &CairoDevice::ObserverFillElapsed),
      InstanceMethod("observerGlyphsElapsed",
                     &CairoDevice::ObserverGlyphsElapsed),
      InstanceMethod("observerPaintElapsed",
                     &CairoDevice::ObserverPaintElapsed),
      InstanceMethod("observerPrint", &CairoDevice::ObserverPrint),
      InstanceMethod("observerStrokeElapsed",
                     &CairoDevice::ObserverStrokeElapsed),
      StaticMethod("scriptCreate", &CairoDevice::ScriptCreate),
      StaticMethod("scriptCreateForStream",
                   &CairoDevice::ScriptCreateForStream),
      InstanceMethod("scriptGetMode", &CairoDevice::ScriptGetMode),
      InstanceMethod("scriptSetMode", &CairoDevice::ScriptSetMode),
      InstanceMethod("scriptWriteComment", &CairoDevice::ScriptWriteComment),
    });
  *deviceConstructor = Napi::Persistent(func);
  exports.Set("CairoDevice", func);
  return exports;
}

CairoDevice::CairoDevice(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoDevice>(info)
{
  this->device_ = nullptr;
}

CairoDevice::~CairoDevice()
{
  if (this->device_) {
    cairo_device_destroy(this->device_);
    this->device_ = nullptr;
  }
  if (this->uks.size() > 0) {
    for (auto iter = this->uks.begin(); iter != this->uks.end(); iter++) {
      free(iter->second);
    }
    this->uks.clear();
  }
}

Napi::Object
CairoDevice::NewInstance(cairo_device_t* device)
{
  Napi::Object obj = deviceConstructor->New({});
  CairoDevice* d = Napi::ObjectWrap<CairoDevice>::Unwrap(obj);
  d->SetDevice(device);
  return obj;
}

bool
CairoDevice::HasInstance(const Napi::Value& value)
{
  if (!value.IsObject()) {
    return false;
  }
  return value.As<Napi::Object>().InstanceOf(deviceConstructor->Value());
}

cairo_device_t*
CairoDevice::GetDevice()
{
  return this->device_;
}

void
CairoDevice::SetDevice(cairo_device_t* device)
{
  this->device_ = device;
}

Napi::Value
CairoDevice::Reference(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_device_reference(this->device_);
  return info.This();
}

Napi::Value
CairoDevice::Destroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  if (this->device_) {
    cairo_device_destroy(this->device_);
    this->device_ = nullptr;
  }
  return info.This();
}

Napi::Value
CairoDevice::Status(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  int status = cairo_device_status(this->device_);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoDevice::Finish(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_device_finish(this->device_);
  return info.This();
}

Napi::Value
CairoDevice::Flush(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_device_flush(this->device_);
  return info.This();
}

Napi::Value
CairoDevice::GetType(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_device_type_t type = cairo_device_get_type(this->device_);
  return Napi::Number::New(env, type);
}

Napi::Value
CairoDevice::GetReferenceCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  unsigned int count = cairo_device_get_reference_count(this->device_);
  return Napi::Number::New(env, count);
}

Napi::Value
CairoDevice::SetUserData(const Napi::CallbackInfo& info)
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
  // data
  Napi::Value data = info[1];
  if (data.IsNull()) {
    if (this->uks.find(key) != this->uks.end()) {
      cairo_user_data_key_t* k = this->uks[key];
      cairo_status_t status =
        cairo_device_set_user_data(this->device_, k, nullptr, nullptr);
      if (status != CAIRO_STATUS_SUCCESS) {
        return ThrowStatusErrorAsJavaScriptException(
          env, "Fail to remove user data on device.", status);
      }
      this->uks.erase(key);
    }
  } else {
    cairo_user_data_key_t* k =
      (cairo_user_data_key_t*)malloc(sizeof(cairo_user_data_key_t));
    if (cairo_device_set_user_data(this->device_, k, &data, nullptr) !=
        CAIRO_STATUS_SUCCESS) {
      return ThrowErrorAsJavaScriptException(
        env, "Fail to set user data on device.");
    }
    this->uks[key] = k;
  }
  return info.This();
}

Napi::Value
CairoDevice::GetUserData(const Napi::CallbackInfo& info)
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
    return env.Null();
  }
  cairo_user_data_key_t* k = this->uks[key];
  Napi::Value* data =
    (Napi::Value*)cairo_device_get_user_data(this->device_, k);
  return *data;
}

Napi::Value
CairoDevice::Acquire(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_status_t status = cairo_device_acquire(this->device_);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to acquire device.", status);
  }
  return info.This();
}

Napi::Value
CairoDevice::Release(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  cairo_device_release(this->device_);
  return info.This();
}

Napi::Value
CairoDevice::ObserverElapsed(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return info.This();
  }
  double t = cairo_device_observer_elapsed(this->device_);
  return Napi::Number::New(env, t);
}

Napi::Value
CairoDevice::ObserverFillElapsed(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double t = cairo_device_observer_fill_elapsed(this->device_);
  return Napi::Number::New(env, t);
}

Napi::Value
CairoDevice::ObserverGlyphsElapsed(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double t = cairo_device_observer_glyphs_elapsed(this->device_);
  return Napi::Number::New(env, t);
}

Napi::Value
CairoDevice::ObserverPaintElapsed(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double t = cairo_device_observer_paint_elapsed(this->device_);
  return Napi::Number::New(env, t);
}

Napi::Value
CairoDevice::ObserverPrint(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoDevice::ObserverStrokeElapsed(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  double t = cairo_device_observer_stroke_elapsed(this->device_);
  return Napi::Number::New(env, t);
}

Napi::Value
CairoDevice::ScriptCreate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsString(env, "filename", info[0])) {
    return env.Undefined();
  }
  string filename = info[0].As<Napi::String>();
  cairo_device_t* d = cairo_script_create(filename.c_str());
  cairo_status_t status = cairo_device_status(d);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create script device.", status);
  }
  return CairoDevice::NewInstance(d);
}

Napi::Value
CairoDevice::ScriptCreateForStream(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  // TODO
  return env.Undefined();
}

Napi::Value
CairoDevice::ScriptGetMode(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_script_mode_t mode = cairo_script_get_mode(this->device_);
  return Napi::Number::New(env, mode);
}

Napi::Value
CairoDevice::ScriptSetMode(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsNumber(env, "mode", info[0])) {
    return info.This();
  }
  int mode = info[0].As<Napi::Number>();
  cairo_script_set_mode(this->device_, (cairo_script_mode_t)mode);
  return info.This();
}

Napi::Value
CairoDevice::ScriptWriteComment(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return info.This();
  }
  if (!ParamIsString(env, "comment", info[0])) {
    return info.This();
  }
  string comment = info[0].As<Napi::String>();
  cairo_script_write_comment(this->device_, comment.c_str(), comment.size());
  return info.This();
}