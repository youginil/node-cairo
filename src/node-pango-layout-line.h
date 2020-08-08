#ifndef __NODE_PANGO_LAYOUT_LINE_H__
#define __NODE_PANGO_LAYOUT_LINE_H__

#include <napi.h>
#include <pango/pangocairo.h>

class NodePangoLayoutLine : public Napi::ObjectWrap<NodePangoLayoutLine>
{
public:
  NodePangoLayoutLine(const Napi::CallbackInfo& info);
  ~NodePangoLayoutLine();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(PangoLayoutLine* line);
  static bool HasInstance(const Napi::Value& v);

  PangoLayoutLine* GetLine();
  void SetLine(PangoLayoutLine* line);

  Napi::Value Ref(const Napi::CallbackInfo& info);
  Napi::Value Unref(const Napi::CallbackInfo& info);
  Napi::Value GetExtents(const Napi::CallbackInfo& info);
  Napi::Value GetPixelExtents(const Napi::CallbackInfo& info);
  Napi::Value IndexToX(const Napi::CallbackInfo& info);
  Napi::Value XToIndex(const Napi::CallbackInfo& info);
  Napi::Value GetXRanges(const Napi::CallbackInfo& info);
  Napi::Value GetHeight(const Napi::CallbackInfo& info);

private:
  PangoLayoutLine* line_;
};

#endif