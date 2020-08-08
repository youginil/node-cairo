#ifndef __NODE_PANGO_FONT_DESCRIPTION__
#define __NODE_PANGO_FONT_DESCRIPTION__

#include <napi.h>
#include <pango/pangocairo.h>

class NodePangoFontDescription
  : public Napi::ObjectWrap<NodePangoFontDescription>
{
public:
  NodePangoFontDescription(const Napi::CallbackInfo& info);
  ~NodePangoFontDescription();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(PangoFontDescription* description);
  static bool HasInstance(const Napi::Value& v);

  const PangoFontDescription* GetDescription();
  void SetDescription(PangoFontDescription* description);

  static Napi::Value FromString(const Napi::CallbackInfo& info);
  Napi::Value Free(const Napi::CallbackInfo& info);

private:
  PangoFontDescription* description_;
};

#endif