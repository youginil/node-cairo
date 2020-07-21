#ifndef __NODE_CAIRO_PATH_H__
#define __NODE_CAIRO_PATH_H__

#include "cairo.h"
#include "node-cairo-context.h"
#include <napi.h>

class CairoPath : public Napi::ObjectWrap<CairoPath>
{
public:
  CairoPath(const Napi::CallbackInfo& info);
  ~CairoPath();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_path_t* path);
  static bool HasInstance(const Napi::Value& value);

  cairo_path_t* GetPath();
  void SetPath(cairo_path_t* path);

  Napi::Value Destroy(const Napi::CallbackInfo& info);

private:
  cairo_path_t* path_;
};

#endif