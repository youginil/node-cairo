#ifndef __NODE_RSVG_HANDLE__
#define __NODE_RSVG_HANDLE__

#include <librsvg/rsvg.h>
#include <napi.h>

class NodeRsvgHandle : public Napi::ObjectWrap<NodeRsvgHandle>
{
public:
  NodeRsvgHandle(const Napi::CallbackInfo& info);
  ~NodeRsvgHandle();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(RsvgHandle* handle);
  static bool HasInstance(const Napi::Value& v);

  void SetHandle(RsvgHandle* handle);
  RsvgHandle* GetHandle();

  static Napi::Value NewFromFile(const Napi::CallbackInfo& info);
  Napi::Value GetIntrinsicDimensions(const Napi::CallbackInfo& info);
  Napi::Value RenderDocument(const Napi::CallbackInfo& info);
  Napi::Value SetStylesheet(const Napi::CallbackInfo& info);

private:
  RsvgHandle* handle_;
};

#endif