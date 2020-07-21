#ifndef __NODE_CAIRO_PATTERN_H__
#define __NODE_CAIRO_PATTERN_H__

#include "cairo.h"
#include <napi.h>

class CairoPattern : public Napi::ObjectWrap<CairoPattern>
{
public:
  CairoPattern(const Napi::CallbackInfo& info);
  ~CairoPattern();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_pattern_t* pattern);
  static bool HasInstance(const Napi::Value& value);

  cairo_pattern_t* GetPattern();
  void SetPattern(cairo_pattern_t* pattern);

  Napi::Value AddColorStopRgb(const Napi::CallbackInfo& info);
  Napi::Value AddColorStopRgba(const Napi::CallbackInfo& info);
  Napi::Value GetColorStopCount(const Napi::CallbackInfo& info);
  Napi::Value GetColorStopRgba(const Napi::CallbackInfo& info);
  static Napi::Value CreateRgb(const Napi::CallbackInfo& info);
  static Napi::Value CreateRgba(const Napi::CallbackInfo& info);
  Napi::Value GetRgba(const Napi::CallbackInfo& info);
  static Napi::Value CreateForSurface(const Napi::CallbackInfo& info);
  Napi::Value GetSurface(const Napi::CallbackInfo& info);
  static Napi::Value CreateLinear(const Napi::CallbackInfo& info);
  Napi::Value GetLinearPoints(const Napi::CallbackInfo& info);
  static Napi::Value CreateRadial(const Napi::CallbackInfo& info);
  Napi::Value GetRadialCircles(const Napi::CallbackInfo& info);
  static Napi::Value CreateMesh(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternBeginPath(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternEndPath(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternMoveTo(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternLineTo(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternCurveTo(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternSetControlPoint(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternSetCornerColorRgb(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternSetCornerColorRgba(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternGetPatchCount(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternGetPath(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternGetControlPoint(const Napi::CallbackInfo& info);
  Napi::Value MeshPatternGetCornerColorRgba(const Napi::CallbackInfo& info);
  Napi::Value Reference(const Napi::CallbackInfo& info);
  Napi::Value Destroy(const Napi::CallbackInfo& info);
  Napi::Value Status(const Napi::CallbackInfo& info);
  Napi::Value SetExtend(const Napi::CallbackInfo& info);
  Napi::Value GetExtend(const Napi::CallbackInfo& info);
  Napi::Value SetFilter(const Napi::CallbackInfo& info);
  Napi::Value GetFilter(const Napi::CallbackInfo& info);
  Napi::Value SetMatrix(const Napi::CallbackInfo& info);
  Napi::Value GetMatrix(const Napi::CallbackInfo& info);
  Napi::Value GetType(const Napi::CallbackInfo& info);
  Napi::Value GetReferenceCount(const Napi::CallbackInfo& info);
  Napi::Value SetUserData(const Napi::CallbackInfo& info);
  Napi::Value GetUserData(const Napi::CallbackInfo& info);

private:
  cairo_pattern_t* pattern_;
};

#endif