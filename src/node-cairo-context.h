#ifndef __NODE_CAIRO_CONTEXT_H__
#define __NODE_CAIRO_CONTEXT_H__

#include "cairo.h"
#include "node-cairo-surface.h"
#include <napi.h>

class CairoContext : public Napi::ObjectWrap<CairoContext>
{
public:
  CairoContext(const Napi::CallbackInfo& info);
  ~CairoContext();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_t* context);
  static bool HasInstance(const Napi::Value& v);

  cairo_t* GetContext();
  void SetContext(cairo_t* ctx);

  static Napi::Value Create(const Napi::CallbackInfo& info);
  Napi::Value Reference(const Napi::CallbackInfo& info);
  Napi::Value Destroy(const Napi::CallbackInfo& info);
  Napi::Value Status(const Napi::CallbackInfo& info);
  Napi::Value Save(const Napi::CallbackInfo& info);
  Napi::Value Restore(const Napi::CallbackInfo& info);
  Napi::Value GetTarget(const Napi::CallbackInfo& info);
  Napi::Value PushGroup(const Napi::CallbackInfo& info);
  Napi::Value PushGroupWithContent(const Napi::CallbackInfo& info);
  Napi::Value PopGroup(const Napi::CallbackInfo& info);
  Napi::Value PopGroupToSource(const Napi::CallbackInfo& info);
  Napi::Value GetGroupTarget(const Napi::CallbackInfo& info);
  Napi::Value SetSourceRgb(const Napi::CallbackInfo& info);
  Napi::Value SetSourceRgba(const Napi::CallbackInfo& info);
  Napi::Value SetSource(const Napi::CallbackInfo& info);
  Napi::Value SetSourceSurface(const Napi::CallbackInfo& info);
  Napi::Value GetSource(const Napi::CallbackInfo& info);
  Napi::Value SetAntialias(const Napi::CallbackInfo& info);
  Napi::Value GetAntialias(const Napi::CallbackInfo& info);
  Napi::Value SetDash(const Napi::CallbackInfo& info);
  Napi::Value GetDashCount(const Napi::CallbackInfo& info);
  Napi::Value GetDash(const Napi::CallbackInfo& info);
  Napi::Value SetFillRule(const Napi::CallbackInfo& info);
  Napi::Value GetFillRule(const Napi::CallbackInfo& info);
  Napi::Value SetLineCap(const Napi::CallbackInfo& info);
  Napi::Value GetLineCap(const Napi::CallbackInfo& info);
  Napi::Value SetLineJoin(const Napi::CallbackInfo& info);
  Napi::Value GetLineJoin(const Napi::CallbackInfo& info);
  Napi::Value SetLineWidth(const Napi::CallbackInfo& info);
  Napi::Value GetLineWidth(const Napi::CallbackInfo& info);
  Napi::Value SetMiterLimit(const Napi::CallbackInfo& info);
  Napi::Value GetMiterLimit(const Napi::CallbackInfo& info);
  Napi::Value SetOperator(const Napi::CallbackInfo& info);
  Napi::Value GetOperator(const Napi::CallbackInfo& info);
  Napi::Value SetTolerance(const Napi::CallbackInfo& info);
  Napi::Value GetTolerance(const Napi::CallbackInfo& info);
  Napi::Value Clip(const Napi::CallbackInfo& info);
  Napi::Value ClipPreserve(const Napi::CallbackInfo& info);
  Napi::Value ClipExtents(const Napi::CallbackInfo& info);
  Napi::Value InClip(const Napi::CallbackInfo& info);
  Napi::Value ResetClip(const Napi::CallbackInfo& info);
  Napi::Value RectangleListDestroy(const Napi::CallbackInfo& info);
  Napi::Value CopyClipRectangleList(const Napi::CallbackInfo& info);
  Napi::Value Fill(const Napi::CallbackInfo& info);
  Napi::Value FillPreserve(const Napi::CallbackInfo& info);
  Napi::Value FillExtents(const Napi::CallbackInfo& info);
  Napi::Value InFill(const Napi::CallbackInfo& info);
  Napi::Value Mask(const Napi::CallbackInfo& info);
  Napi::Value MaskSurface(const Napi::CallbackInfo& info);
  Napi::Value Paint(const Napi::CallbackInfo& info);
  Napi::Value PaintWithAlpha(const Napi::CallbackInfo& info);
  Napi::Value Stroke(const Napi::CallbackInfo& info);
  Napi::Value StrokePreserve(const Napi::CallbackInfo& info);
  Napi::Value StrokeExtents(const Napi::CallbackInfo& info);
  Napi::Value InStroke(const Napi::CallbackInfo& info);
  Napi::Value CopyPage(const Napi::CallbackInfo& info);
  Napi::Value ShowPage(const Napi::CallbackInfo& info);
  Napi::Value GetReferenceCount(const Napi::CallbackInfo& info);
  Napi::Value SetUserData(const Napi::CallbackInfo& info);
  Napi::Value GetUserData(const Napi::CallbackInfo& info);
  // Paths
  Napi::Value CopyPath(const Napi::CallbackInfo& info);
  Napi::Value CopyPathFlat(const Napi::CallbackInfo& info);
  Napi::Value AppendPath(const Napi::CallbackInfo& info);
  Napi::Value HasCurrentPoint(const Napi::CallbackInfo& info);
  Napi::Value NewPath(const Napi::CallbackInfo& info);
  Napi::Value NewSubPath(const Napi::CallbackInfo& info);
  Napi::Value ClosePath(const Napi::CallbackInfo& info);
  Napi::Value Arc(const Napi::CallbackInfo& info);
  Napi::Value ArcNegative(const Napi::CallbackInfo& info);
  Napi::Value CurveTo(const Napi::CallbackInfo& info);
  Napi::Value LineTo(const Napi::CallbackInfo& info);
  Napi::Value MoveTo(const Napi::CallbackInfo& info);
  Napi::Value Rectangle(const Napi::CallbackInfo& info);
  Napi::Value GlyphPath(const Napi::CallbackInfo& info);
  Napi::Value RelCurveTo(const Napi::CallbackInfo& info);
  Napi::Value RelLineTo(const Napi::CallbackInfo& info);
  Napi::Value RelMoveTo(const Napi::CallbackInfo& info);
  Napi::Value PathExtents(const Napi::CallbackInfo& info);
  // Transformations
  Napi::Value Translate(const Napi::CallbackInfo& info);
  Napi::Value Scale(const Napi::CallbackInfo& info);
  Napi::Value Rotate(const Napi::CallbackInfo& info);
  Napi::Value Transform(const Napi::CallbackInfo& info);
  Napi::Value SetMatrix(const Napi::CallbackInfo& info);
  Napi::Value GetMatrix(const Napi::CallbackInfo& info);
  Napi::Value IdentityMatrix(const Napi::CallbackInfo& info);
  Napi::Value UserToDevice(const Napi::CallbackInfo& info);
  Napi::Value UserToDeviceDistance(const Napi::CallbackInfo& info);
  Napi::Value DeviceToUser(const Napi::CallbackInfo& info);
  Napi::Value DeviceToUserDistance(const Napi::CallbackInfo& info);
  // Text
  Napi::Value SelectFontFace(const Napi::CallbackInfo& info);
  Napi::Value SetFontSize(const Napi::CallbackInfo& info);
  Napi::Value SetFontMatrix(const Napi::CallbackInfo& info);
  Napi::Value GetFontMatrix(const Napi::CallbackInfo& info);
  Napi::Value SetFontOptions(const Napi::CallbackInfo& info);
  Napi::Value GetFontOptions(const Napi::CallbackInfo& info);
  Napi::Value SetFontFace(const Napi::CallbackInfo& info);
  Napi::Value GetFontFace(const Napi::CallbackInfo& info);
  Napi::Value SetScaledFont(const Napi::CallbackInfo& info);
  Napi::Value GetScaledFont(const Napi::CallbackInfo& info);
  Napi::Value ShowText(const Napi::CallbackInfo& info);
  Napi::Value ShowGlyphs(const Napi::CallbackInfo& info);
  Napi::Value ShowTextGlyphs(const Napi::CallbackInfo& info);
  Napi::Value FontExtents(const Napi::CallbackInfo& info);
  Napi::Value TextExtents(const Napi::CallbackInfo& info);
  Napi::Value GlyphExtents(const Napi::CallbackInfo& info);

private:
  cairo_t* context_;
};

#endif