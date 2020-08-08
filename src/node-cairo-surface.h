#ifndef __NODE_CAIRO_SURFACE_H__
#define __NODE_CAIRO_SURFACE_H__

#include "cairo.h"
#include "node-cairo-device.h"
#include <map>
#include <napi.h>

using namespace std;

class CairoSurface : public Napi::ObjectWrap<CairoSurface>
{
public:
  CairoSurface(const Napi::CallbackInfo& info);
  ~CairoSurface();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(cairo_surface_t* s);
  static bool HasInstance(const Napi::Value& v);

  cairo_surface_t* GetSurface();
  void SetSurface(cairo_surface_t* s);

  CairoDevice* GetDeviceInstance();
  Napi::Value CreateSimilar(const Napi::CallbackInfo& info);
  Napi::Value CreateSimilarImage(const Napi::CallbackInfo& info);
  Napi::Value CreateForRectangle(const Napi::CallbackInfo& info);
  Napi::Value Reference(const Napi::CallbackInfo& info);
  Napi::Value Destroy(const Napi::CallbackInfo& info);
  Napi::Value Status(const Napi::CallbackInfo& info);
  Napi::Value Finish(const Napi::CallbackInfo& info);
  Napi::Value Flush(const Napi::CallbackInfo& info);
  Napi::Value GetDevice(const Napi::CallbackInfo& info);
  Napi::Value GetFontOptions(const Napi::CallbackInfo& info);
  Napi::Value GetContent(const Napi::CallbackInfo& info);
  Napi::Value MarkDirty(const Napi::CallbackInfo& info);
  Napi::Value MarkDirtyRectangle(const Napi::CallbackInfo& info);
  Napi::Value SetDeviceOffset(const Napi::CallbackInfo& info);
  Napi::Value GetDeviceOffset(const Napi::CallbackInfo& info);
  Napi::Value GetDeviceScale(const Napi::CallbackInfo& info);
  Napi::Value SetDeviceScale(const Napi::CallbackInfo& info);
  Napi::Value SetFallbackResolution(const Napi::CallbackInfo& info);
  Napi::Value GetFallbackResolution(const Napi::CallbackInfo& info);
  Napi::Value GetType(const Napi::CallbackInfo& info);
  Napi::Value GetReferenceCount(const Napi::CallbackInfo& info);
  Napi::Value SetUserData(const Napi::CallbackInfo& info);
  Napi::Value GetUserData(const Napi::CallbackInfo& info);
  Napi::Value CopyPage(const Napi::CallbackInfo& info);
  Napi::Value ShowPage(const Napi::CallbackInfo& info);
  Napi::Value HasShowTextGlyphs(const Napi::CallbackInfo& info);
  Napi::Value SetMimeData(const Napi::CallbackInfo& info);
  Napi::Value GetMimeData(const Napi::CallbackInfo& info);
  Napi::Value SupportsMimeType(const Napi::CallbackInfo& info);
  Napi::Value MapToImage(const Napi::CallbackInfo& info);
  Napi::Value UnmapImage(const Napi::CallbackInfo& info);

  // Image Surfaces
  static Napi::Value FormatStrideForWidth(const Napi::CallbackInfo& info);
  static Napi::Value ImageSurfaceCreate(const Napi::CallbackInfo& info);
  static Napi::Value ImageSurfaceCreateForData(const Napi::CallbackInfo& info);
  Napi::Value ImageSurfaceGetData(const Napi::CallbackInfo& info);
  Napi::Value ImageSurfaceGetFormat(const Napi::CallbackInfo& info);
  Napi::Value ImageSurfaceGetWidth(const Napi::CallbackInfo& info);
  Napi::Value ImageSurfaceGetHeight(const Napi::CallbackInfo& info);
  Napi::Value ImageSurfaceGetStride(const Napi::CallbackInfo& info);

  // PDF Surfaces
  static Napi::Value PdfSurfaceCreate(const Napi::CallbackInfo& info);
  static Napi::Value PdfSurfaceCreateForStream(const Napi::CallbackInfo& info);
  Napi::Value PdfSurfaceRestrictToVersion(const Napi::CallbackInfo& info);
  static Napi::Value PdfGetVersions(const Napi::CallbackInfo& info);
  static Napi::Value PdfVersionToString(const Napi::CallbackInfo& info);
  Napi::Value PdfSurfaceSetSize(const Napi::CallbackInfo& info);
  Napi::Value PdfSurfaceAddOutline(const Napi::CallbackInfo& info);
  Napi::Value PdfSurfaceSetMetadata(const Napi::CallbackInfo& info);
  Napi::Value PdfSurfaceSetPageLabel(const Napi::CallbackInfo& info);
  Napi::Value PdfSurfaceSetThumbnailSize(const Napi::CallbackInfo& info);

  // PNG support
  static Napi::Value ImageSurfaceCreateFromPng(const Napi::CallbackInfo& info);
  static Napi::Value ImageSurfaceCreateFromPngStream(
    const Napi::CallbackInfo& info);
  Napi::Value WriteToPng(const Napi::CallbackInfo& info);
  Napi::Value WriteToPngStream(const Napi::CallbackInfo& info);

  // TODO PostScript Surfaces

  // Recording Surfaces
  static Napi::Value RecordingSurfaceCreate(const Napi::CallbackInfo& info);
  Napi::Value RecordingSurfaceInkExtents(const Napi::CallbackInfo& info);
  Napi::Value RecordingSurfaceGetExtents(const Napi::CallbackInfo& info);

  // TODO Win32 Surfaces

  // SVG Surfaces
  static Napi::Value SvgSurfaceCreate(const Napi::CallbackInfo& info);
  static Napi::Value SvgSurfaceCreateForStream(const Napi::CallbackInfo& info);
  Napi::Value SvgSurfaceGetDocumentUnit(const Napi::CallbackInfo& info);
  Napi::Value SvgSurfaceSetDocumentUnit(const Napi::CallbackInfo& info);
  Napi::Value SvgSurfaceRestrictToVersion(const Napi::CallbackInfo& info);
  static Napi::Value SvgGetVersions(const Napi::CallbackInfo& info);
  static Napi::Value SvgVersionToString(const Napi::CallbackInfo& info);

  // TODO Quartz Surfaces
  // TODO XCB Surfaces
  // TODO XLib Surfaces
  // XLib-XRender Backend

  // Script Surfaces
  Napi::Value ScriptFromRecordingSurface(const Napi::CallbackInfo& info);
  static Napi::Value ScriptSurfaceCreate(const Napi::CallbackInfo& info);
  static Napi::Value ScriptSurfaceCreateForTarget(
    const Napi::CallbackInfo& info);

private:
  cairo_surface_t* surface_;
  map<string, cairo_user_data_key_t*> uks;
};

#endif