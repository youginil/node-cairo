#ifndef __NODE_CAIRO_REGION_H__
#define __NODE_CAIRO_REGION_H__

#include "cairo.h"
#include <napi.h>

class CairoRegion : public Napi::ObjectWrap<CairoRegion>
{
public:
  CairoRegion(const Napi::CallbackInfo& info);
  ~CairoRegion();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_region_t* region);
  static bool HasInstance(const Napi::Value& value);

  cairo_region_t* GetRegion();
  void SetRegion(cairo_region_t* region);

  static Napi::Value Create(const Napi::CallbackInfo& info);
  static Napi::Value CreateRectangle(const Napi::CallbackInfo& info);
  static Napi::Value CreateRectangles(const Napi::CallbackInfo& info);
  Napi::Value Copy(const Napi::CallbackInfo& info);
  Napi::Value Reference(const Napi::CallbackInfo& info);
  Napi::Value Destroy(const Napi::CallbackInfo& info);
  Napi::Value Status(const Napi::CallbackInfo& info);
  Napi::Value GetExtents(const Napi::CallbackInfo& info);
  Napi::Value NumRectangles(const Napi::CallbackInfo& info);
  Napi::Value GetRectangle(const Napi::CallbackInfo& info);
  Napi::Value IsEmpty(const Napi::CallbackInfo& info);
  Napi::Value ContainsPoint(const Napi::CallbackInfo& info);
  Napi::Value ContainsRectangle(const Napi::CallbackInfo& info);
  Napi::Value Equal(const Napi::CallbackInfo& info);
  Napi::Value Translate(const Napi::CallbackInfo& info);
  Napi::Value Intersect(const Napi::CallbackInfo& info);
  Napi::Value IntersectRectangle(const Napi::CallbackInfo& info);
  Napi::Value Subtracts(const Napi::CallbackInfo& info);
  Napi::Value SubTractsRectangle(const Napi::CallbackInfo& info);
  Napi::Value Union(const Napi::CallbackInfo& info);
  Napi::Value UnionRectangle(const Napi::CallbackInfo& info);
  Napi::Value Xor(const Napi::CallbackInfo& info);
  Napi::Value XorRectangle(const Napi::CallbackInfo& info);

private:
  cairo_region_t* region_;
};

#endif