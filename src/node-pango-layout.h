#ifndef __NODE_PANGO_LAYOUT_H__
#define __NODE_PANGO_LAYOUT_H__

#include <napi.h>
#include <pango/pangocairo.h>

class NodePangoLayout : public Napi::ObjectWrap<NodePangoLayout>
{
public:
  NodePangoLayout(const Napi::CallbackInfo& info);
  ~NodePangoLayout();

  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(PangoLayout* layout);
  static bool HasInstance(const Napi::Value& v);

  PangoLayout* GetLayout();
  void SetLayout(PangoLayout* layout);

  // cairo
  static Napi::Value CairoCreateLayout(const Napi::CallbackInfo& info);
  Napi::Value CairoUpdateLayout(const Napi::CallbackInfo& info);
  Napi::Value CairoShowLayout(const Napi::CallbackInfo& info);

  // self
  Napi::Value SetText(const Napi::CallbackInfo& info);
  Napi::Value GetText(const Napi::CallbackInfo& info);
  Napi::Value GetCharacterCount(const Napi::CallbackInfo& info);
  Napi::Value SetMarkup(const Napi::CallbackInfo& info);
  Napi::Value SetMarkupWithAccel(const Napi::CallbackInfo& info);
  Napi::Value SetFontDescription(const Napi::CallbackInfo& info);
  Napi::Value GetFontDescription(const Napi::CallbackInfo& info);
  Napi::Value SetWidth(const Napi::CallbackInfo& info);
  Napi::Value GetWidth(const Napi::CallbackInfo& info);
  Napi::Value SetHeight(const Napi::CallbackInfo& info);
  Napi::Value GetHeight(const Napi::CallbackInfo& info);
  Napi::Value SetWrap(const Napi::CallbackInfo& info);
  Napi::Value GetWrap(const Napi::CallbackInfo& info);
  Napi::Value IsWrapped(const Napi::CallbackInfo& info);
  Napi::Value SetEllipsize(const Napi::CallbackInfo& info);
  Napi::Value GetEllipsize(const Napi::CallbackInfo& info);
  Napi::Value IsEllipsized(const Napi::CallbackInfo& info);
  Napi::Value SetIndent(const Napi::CallbackInfo& info);
  Napi::Value GetIndent(const Napi::CallbackInfo& info);
  Napi::Value GetSpacing(const Napi::CallbackInfo& info);
  Napi::Value SetSpacing(const Napi::CallbackInfo& info);
  Napi::Value SetLineSpacing(const Napi::CallbackInfo& info);
  Napi::Value GetLineSpacing(const Napi::CallbackInfo& info);
  Napi::Value SetJustify(const Napi::CallbackInfo& info);
  Napi::Value GetJustify(const Napi::CallbackInfo& info);
  Napi::Value SetAutoDir(const Napi::CallbackInfo& info);
  Napi::Value GetAutoDir(const Napi::CallbackInfo& info);
  Napi::Value SetAlignment(const Napi::CallbackInfo& info);
  Napi::Value GetAlignment(const Napi::CallbackInfo& info);
  Napi::Value SetSingleParagraphMode(const Napi::CallbackInfo& info);
  Napi::Value GetSingleParagraphMode(const Napi::CallbackInfo& info);
  Napi::Value GetUnknownGlyphsCount(const Napi::CallbackInfo& info);
  Napi::Value GetLogAttrs(const Napi::CallbackInfo& info);
  Napi::Value GetLogAttrsReadonly(const Napi::CallbackInfo& info);
  Napi::Value IndexToPos(const Napi::CallbackInfo& info);
  Napi::Value IndexToLineX(const Napi::CallbackInfo& info);
  Napi::Value XYToIndex(const Napi::CallbackInfo& info);
  Napi::Value GetCursorPos(const Napi::CallbackInfo& info);
  Napi::Value MoveCursorVisually(const Napi::CallbackInfo& info);
  Napi::Value GetExtents(const Napi::CallbackInfo& info);
  Napi::Value GetPixelExtents(const Napi::CallbackInfo& info);
  Napi::Value GetSize(const Napi::CallbackInfo& info);
  Napi::Value GetPixelSize(const Napi::CallbackInfo& info);
  Napi::Value GetBaseline(const Napi::CallbackInfo& info);
  Napi::Value GetLineCount(const Napi::CallbackInfo& info);
  Napi::Value GetLine(const Napi::CallbackInfo& info);
  Napi::Value GetLineReadonly(const Napi::CallbackInfo& info);
  Napi::Value GetIter(const Napi::CallbackInfo& info);

private:
  PangoLayout* layout_;
};

#endif