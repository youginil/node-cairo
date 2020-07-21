#ifndef __NODE_CAIRO_DEVICE_H__
#define __NODE_CAIRO_DEVICE_H__

#include "cairo.h"
#include <map>
#include <napi.h>

using namespace std;

class CairoDevice : public Napi::ObjectWrap<CairoDevice>
{
public:
  CairoDevice(const Napi::CallbackInfo& info);
  ~CairoDevice();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_device_t* device);
  static bool HasInstance(const Napi::Value& value);

  cairo_device_t* GetDevice();
  void SetDevice(cairo_device_t* device);

  Napi::Value Reference(const Napi::CallbackInfo& info);
  Napi::Value Destroy(const Napi::CallbackInfo& info);
  Napi::Value Status(const Napi::CallbackInfo& info);
  Napi::Value Finish(const Napi::CallbackInfo& info);
  Napi::Value Flush(const Napi::CallbackInfo& info);
  Napi::Value GetType(const Napi::CallbackInfo& info);
  Napi::Value GetReferenceCount(const Napi::CallbackInfo& info);
  Napi::Value SetUserData(const Napi::CallbackInfo& info);
  Napi::Value GetUserData(const Napi::CallbackInfo& info);
  Napi::Value Acquire(const Napi::CallbackInfo& info);
  Napi::Value Release(const Napi::CallbackInfo& info);
  Napi::Value ObserverElapsed(const Napi::CallbackInfo& info);
  Napi::Value ObserverFillElapsed(const Napi::CallbackInfo& info);
  Napi::Value ObserverGlyphsElapsed(const Napi::CallbackInfo& info);
  Napi::Value ObserverPaintElapsed(const Napi::CallbackInfo& info);
  Napi::Value ObserverPrint(const Napi::CallbackInfo& info);
  Napi::Value ObserverStrokeElapsed(const Napi::CallbackInfo& info);

  // Script Devices
  static Napi::Value ScriptCreate(const Napi::CallbackInfo& info);
  static Napi::Value ScriptCreateForStream(const Napi::CallbackInfo& info);
  Napi::Value ScriptGetMode(const Napi::CallbackInfo& info);
  Napi::Value ScriptSetMode(const Napi::CallbackInfo& info);
  Napi::Value ScriptWriteComment(const Napi::CallbackInfo& info);

private:
  cairo_device_t* device_;
  map<string, cairo_user_data_key_t*> uks;
};

#endif