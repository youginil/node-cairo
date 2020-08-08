#ifndef __NODE_PANGO_LAYOUT_ITER_H__
#define __NODE_PANGO_LAYOUT_ITER_H__

#include <napi.h>
#include <pango/pangocairo.h>

class NodePangoLayoutIter : public Napi::ObjectWrap<NodePangoLayoutIter>
{
public:
  NodePangoLayoutIter(const Napi::CallbackInfo& info);
  ~NodePangoLayoutIter();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(PangoLayoutIter* iter);
  static bool HasInstance(const Napi::Value& v);

  PangoLayoutIter* GetIter();
  void SetIter(PangoLayoutIter* iter);

  Napi::Value Copy(const Napi::CallbackInfo& info);
  Napi::Value Free(const Napi::CallbackInfo& info);
  Napi::Value NextRun(const Napi::CallbackInfo& info);
  Napi::Value NextChar(const Napi::CallbackInfo& info);
  Napi::Value NextCluster(const Napi::CallbackInfo& info);
  Napi::Value NextLine(const Napi::CallbackInfo& info);
  Napi::Value AtLastLine(const Napi::CallbackInfo& info);
  Napi::Value GetIndex(const Napi::CallbackInfo& info);
  Napi::Value GetBaseline(const Napi::CallbackInfo& info);
  Napi::Value GetLine(const Napi::CallbackInfo& info);
  Napi::Value GetLineReadonly(const Napi::CallbackInfo& info);
  Napi::Value GetLayout(const Napi::CallbackInfo& info);
  Napi::Value GetCharExtents(const Napi::CallbackInfo& info);
  Napi::Value GetClusterExtents(const Napi::CallbackInfo& info);
  Napi::Value GetRunExtents(const Napi::CallbackInfo& info);
  Napi::Value GetLineYRange(const Napi::CallbackInfo& info);
  Napi::Value GetLineExtents(const Napi::CallbackInfo& info);
  Napi::Value GetLayoutExtents(const Napi::CallbackInfo& info);

private:
  PangoLayoutIter* iter_;
};

#endif