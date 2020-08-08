#include "node-pango-layout.h"
#include "node-cairo-context.h"
#include "node-cairo-utils.h"
#include "node-pango-font-description.h"
#include "node-pango-layout-iter.h"
#include "node-pango-layout-line.h"

using namespace std;

static Napi::FunctionReference* pangoLayoutCtor = new Napi::FunctionReference();

Napi::Object
NodePangoLayout::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "PangoLayout",
    {
      StaticMethod("cairoCreateLayout", &NodePangoLayout::CairoCreateLayout),
      InstanceMethod("cairoUpdateLayout", &NodePangoLayout::CairoUpdateLayout),
      InstanceMethod("cairoShowLayout", &NodePangoLayout::CairoShowLayout),
      InstanceMethod("setText", &NodePangoLayout::SetText),
      InstanceMethod("getText", &NodePangoLayout::GetText),
      InstanceMethod("getCharacterCount", &NodePangoLayout::GetCharacterCount),
      InstanceMethod("setMarkup", &NodePangoLayout::SetMarkup),
      InstanceMethod("setMarkupWithAccel",
                     &NodePangoLayout::SetMarkupWithAccel),
      InstanceMethod("setFontDescription",
                     &NodePangoLayout::SetFontDescription),
      InstanceMethod("getFontDescription",
                     &NodePangoLayout::GetFontDescription),
      InstanceMethod("setWidth", &NodePangoLayout::SetWidth),
      InstanceMethod("getWidth", &NodePangoLayout::GetWidth),
      InstanceMethod("setHeight", &NodePangoLayout::SetHeight),
      InstanceMethod("getHeight", &NodePangoLayout::GetHeight),
      InstanceMethod("setWrap", &NodePangoLayout::SetWrap),
      InstanceMethod("getWrap", &NodePangoLayout::GetWrap),
      InstanceMethod("isWrapped", &NodePangoLayout::IsWrapped),
      InstanceMethod("setEllipsize", &NodePangoLayout::SetEllipsize),
      InstanceMethod("getEllipsize", &NodePangoLayout::GetEllipsize),
      InstanceMethod("isEllipsized", &NodePangoLayout::IsEllipsized),
      InstanceMethod("setIndent", &NodePangoLayout::SetIndent),
      InstanceMethod("getIndent", &NodePangoLayout::GetIndent),
      InstanceMethod("getSpacing", &NodePangoLayout::GetSpacing),
      InstanceMethod("setSpacing", &NodePangoLayout::SetSpacing),
      InstanceMethod("setLineSpacing", &NodePangoLayout::SetLineSpacing),
      InstanceMethod("getLineSpacing", &NodePangoLayout::GetLineSpacing),
      InstanceMethod("setJustify", &NodePangoLayout::SetJustify),
      InstanceMethod("getJustify", &NodePangoLayout::GetJustify),
      InstanceMethod("setAutoDir", &NodePangoLayout::SetAutoDir),
      InstanceMethod("getAutoDir", &NodePangoLayout::GetAutoDir),
      InstanceMethod("setAlignment", &NodePangoLayout::SetAlignment),
      InstanceMethod("getAlignment", &NodePangoLayout::GetAlignment),
      InstanceMethod("setSingleParagraphMode",
                     &NodePangoLayout::SetSingleParagraphMode),
      InstanceMethod("getSingleParagraphMode",
                     &NodePangoLayout::GetSingleParagraphMode),
      InstanceMethod("getUnknownGlyphsCount",
                     &NodePangoLayout::GetUnknownGlyphsCount),
      InstanceMethod("getLogAttrs", &NodePangoLayout::GetLogAttrs),
      InstanceMethod("getLogAttrsReadonly",
                     &NodePangoLayout::GetLogAttrsReadonly),
      InstanceMethod("indexToPos", &NodePangoLayout::IndexToPos),
      InstanceMethod("indexToLineX", &NodePangoLayout::IndexToLineX),
      InstanceMethod("xyToIndex", &NodePangoLayout::XYToIndex),
      InstanceMethod("getCursorPos", &NodePangoLayout::GetCursorPos),
      InstanceMethod("moveCursorVisually",
                     &NodePangoLayout::MoveCursorVisually),
      InstanceMethod("getExtents", &NodePangoLayout::GetExtents),
      InstanceMethod("getPixelExtents", &NodePangoLayout::GetPixelExtents),
      InstanceMethod("getSize", &NodePangoLayout::GetSize),
      InstanceMethod("getPixelSize", &NodePangoLayout::GetPixelSize),
      InstanceMethod("getBaseline", &NodePangoLayout::GetBaseline),
      InstanceMethod("getLineCount", &NodePangoLayout::GetLineCount),
      InstanceMethod("getLine", &NodePangoLayout::GetLine),
      InstanceMethod("getLineReadonly", &NodePangoLayout::GetLineReadonly),
      InstanceMethod("getIter", &NodePangoLayout::GetIter),
    });
  *pangoLayoutCtor = Napi::Persistent(func);
  exports.Set("PangoLayout", func);
  return exports;
}

NodePangoLayout::NodePangoLayout(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<NodePangoLayout>(info)
{
  this->layout_ = nullptr;
}

NodePangoLayout::~NodePangoLayout()
{
  if (this->layout_) {
    g_object_unref(this->layout_);
    this->layout_ = nullptr;
  }
}

Napi::Object
NodePangoLayout::NewInstance(PangoLayout* layout)
{
  Napi::Object obj = pangoLayoutCtor->New({});
  NodePangoLayout* pl = Napi::ObjectWrap<NodePangoLayout>::Unwrap(obj);
  pl->SetLayout(layout);
  return obj;
}

bool
NodePangoLayout::HasInstance(const Napi::Value& v)
{
  return v.IsObject() &&
         v.As<Napi::Object>().InstanceOf(pangoLayoutCtor->Value());
}

PangoLayout*
NodePangoLayout::GetLayout()
{
  return this->layout_;
}

void
NodePangoLayout::SetLayout(PangoLayout* layout)
{
  this->layout_ = layout;
}

Napi::Value
NodePangoLayout::CairoCreateLayout(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!CairoContext::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid CairoContext");
  }
  CairoContext* ctx =
    Napi::ObjectWrap<CairoContext>::Unwrap(info[0].As<Napi::Object>());
  PangoLayout* layout = pango_cairo_create_layout(ctx->GetContext());
  return NodePangoLayout::NewInstance(layout);
}

Napi::Value
NodePangoLayout::CairoUpdateLayout(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!CairoContext::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid CairoContext");
  }
  CairoContext* ctx =
    Napi::ObjectWrap<CairoContext>::Unwrap(info[0].As<Napi::Object>());
  pango_cairo_update_layout(ctx->GetContext(), this->layout_);
  return info.This();
}

Napi::Value
NodePangoLayout::CairoShowLayout(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!CairoContext::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid CairoContext");
  }
  CairoContext* ctx =
    Napi::ObjectWrap<CairoContext>::Unwrap(info[0].As<Napi::Object>());
  pango_cairo_show_layout(ctx->GetContext(), this->layout_);
  return info.This();
}

Napi::Value
NodePangoLayout::SetText(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsString(info[0], "text", env)) {
    return env.Undefined();
  }
  string text = info[0].As<Napi::String>();
  pango_layout_set_text(this->layout_, text.c_str(), text.length());
  return info.This();
}

Napi::Value
NodePangoLayout::GetText(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  const char* text = pango_layout_get_text(this->layout_);
  return Napi::String::New(env, text);
}

Napi::Value
NodePangoLayout::GetCharacterCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gint c = pango_layout_get_character_count(this->layout_);
  return Napi::Number::New(env, c);
}

Napi::Value
NodePangoLayout::SetMarkup(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsString(info[0], "markup", env)) {
    return env.Undefined();
  }
  string markup = info[0].As<Napi::String>();
  pango_layout_set_markup(this->layout_, markup.c_str(), markup.length());
  return info.This();
}

Napi::Value
NodePangoLayout::SetMarkupWithAccel(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsString(info[0], "markup", env) ||
      !ParamIsNumber(info[1], "accelerator marker", env)) {
    return env.Undefined();
  }
  string markup = info[0].As<Napi::String>();
  gunichar accelMarker = info[1].As<Napi::Number>();
  gunichar accelChar;
  pango_layout_set_markup_with_accel(
    this->layout_, markup.c_str(), markup.length(), accelMarker, &accelChar);
  return Napi::Number::New(env, accelChar);
}

Napi::Value
NodePangoLayout::SetFontDescription(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!NodePangoFontDescription::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env,
                                               "Invalid PangoFontDescription");
  }
  NodePangoFontDescription* desc =
    Napi::ObjectWrap<NodePangoFontDescription>::Unwrap(
      info[0].As<Napi::Object>());
  pango_layout_set_font_description(this->layout_, desc->GetDescription());
  return info.This();
}

Napi::Value
NodePangoLayout::GetFontDescription(const Napi::CallbackInfo& info)
{
  // todo Cannot initiliaze NodePangoFontDescripton by const pointer
  Napi::Env env = info.Env();
  return env.Undefined();
}

Napi::Value
NodePangoLayout::SetWidth(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "width", env)) {
    return env.Undefined();
  }
  int w = info[0].As<Napi::Number>();
  pango_layout_set_width(this->layout_, w);
  return info.This();
}

Napi::Value
NodePangoLayout::GetWidth(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int w = pango_layout_get_width(this->layout_);
  return Napi::Number::New(env, w);
}

Napi::Value
NodePangoLayout::SetHeight(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  int h = info[0].As<Napi::Number>();
  pango_layout_set_height(this->layout_, h);
  return info.This();
}

Napi::Value
NodePangoLayout::GetHeight(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int h = pango_layout_get_height(this->layout_);
  return Napi::Number::New(env, h);
}

Napi::Value
NodePangoLayout::SetWrap(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "wrap mode", env)) {
    return env.Undefined();
  }
  PangoWrapMode mode = (PangoWrapMode)(int)info[0].As<Napi::Number>();
  pango_layout_set_wrap(this->layout_, mode);
  return info.This();
}

Napi::Value
NodePangoLayout::GetWrap(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoWrapMode mode = pango_layout_get_wrap(this->layout_);
  return Napi::Number::New(env, mode);
}

Napi::Value
NodePangoLayout::IsWrapped(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean wrapped = pango_layout_is_wrapped(this->layout_);
  return Napi::Boolean::New(env, wrapped);
}

Napi::Value
NodePangoLayout::SetEllipsize(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "ellipsize mode", env)) {
    return env.Undefined();
  }
  PangoEllipsizeMode mode = (PangoEllipsizeMode)(int)info[0].As<Napi::Number>();
  pango_layout_set_ellipsize(this->layout_, mode);
  return info.This();
}

Napi::Value
NodePangoLayout::GetEllipsize(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoEllipsizeMode mode = pango_layout_get_ellipsize(this->layout_);
  return Napi::Number::New(env, mode);
}

Napi::Value
NodePangoLayout::IsEllipsized(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean ellipsized = pango_layout_is_ellipsized(this->layout_);
  return Napi::Boolean::New(env, ellipsized);
}

Napi::Value
NodePangoLayout::SetIndent(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  int d = info[0].As<Napi::Number>();
  pango_layout_set_indent(this->layout_, d);
  return info.This();
}

Napi::Value
NodePangoLayout::GetIndent(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int d = pango_layout_get_indent(this->layout_);
  return Napi::Number::New(env, d);
}

Napi::Value
NodePangoLayout::GetSpacing(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int d = pango_layout_get_spacing(this->layout_);
  return Napi::Number::New(env, d);
}

Napi::Value
NodePangoLayout::SetSpacing(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "spacing", env)) {
    return env.Undefined();
  }
  int d = info[0].As<Napi::Number>();
  pango_layout_set_spacing(this->layout_, d);
  return info.This();
}

Napi::Value
NodePangoLayout::SetLineSpacing(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "line spacing", env)) {
    return env.Undefined();
  }
  float d = info[0].As<Napi::Number>();
  pango_layout_set_line_spacing(this->layout_, d);
  return info.This();
}

Napi::Value
NodePangoLayout::GetLineSpacing(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  float d = pango_layout_get_line_spacing(this->layout_);
  return Napi::Number::New(env, d);
}

Napi::Value
NodePangoLayout::SetJustify(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsBoolean(info[0], "justify", env)) {
    return env.Undefined();
  }
  bool isJustify = info[0].As<Napi::Boolean>();
  pango_layout_set_justify(this->layout_, isJustify);
  return info.This();
}

Napi::Value
NodePangoLayout::GetJustify(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean isJustify = pango_layout_get_justify(this->layout_);
  return Napi::Boolean::New(env, isJustify);
}

Napi::Value
NodePangoLayout::SetAutoDir(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsBoolean(info[0], "auto direction", env)) {
    return env.Undefined();
  }
  gboolean autoDir = info[0].As<Napi::Boolean>();
  pango_layout_set_auto_dir(this->layout_, autoDir);
  return info.This();
}

Napi::Value
NodePangoLayout::GetAutoDir(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean autoDir = pango_layout_get_auto_dir(this->layout_);
  return Napi::Boolean::New(env, autoDir);
}

Napi::Value
NodePangoLayout::SetAlignment(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "alignment", env)) {
    return env.Undefined();
  }
  PangoAlignment align = (PangoAlignment)(int)info[0].As<Napi::Number>();
  pango_layout_set_alignment(this->layout_, align);
  return info.This();
}

Napi::Value
NodePangoLayout::GetAlignment(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoAlignment align = pango_layout_get_alignment(this->layout_);
  return Napi::Number::New(env, align);
}

Napi::Value
NodePangoLayout::SetSingleParagraphMode(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsBoolean(info[0], "setting", env)) {
    return env.Undefined();
  }
  gboolean setting = info[0].As<Napi::Boolean>();
  pango_layout_set_single_paragraph_mode(this->layout_, setting);
  return info.This();
}

Napi::Value
NodePangoLayout::GetSingleParagraphMode(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gboolean setting = pango_layout_get_single_paragraph_mode(this->layout_);
  return Napi::Boolean::New(env, setting);
}

Napi::Value
NodePangoLayout::GetUnknownGlyphsCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int c = pango_layout_get_unknown_glyphs_count(this->layout_);
  return Napi::Number::New(env, c);
}

Napi::Value
NodePangoLayout::GetLogAttrs(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoLogAttr** attrs = nullptr;
  gint n;
  pango_layout_get_log_attrs(this->layout_, attrs, &n);
  Napi::Int32Array result = Napi::Int32Array::New(env, n);
  for (int i = 0; i < n; i++) {
    result.Set(i, PangoLogAttrToValue(env, attrs[i]));
  }
  g_free(attrs);
  return result;
}

Napi::Value
NodePangoLayout::GetLogAttrsReadonly(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  gint c;
  const PangoLogAttr* attr =
    pango_layout_get_log_attrs_readonly(this->layout_, &c);
  Napi::Int32Array result = Napi::Int32Array::New(env, c);
  for (int i = 0; i < c; i++) {
    result.Set(i, PangoLogAttrToValue(env, &attr[i]));
  }
  return result;
}

Napi::Value
NodePangoLayout::IndexToPos(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "index", env)) {
    return env.Undefined();
  }
  int index = info[0].As<Napi::Number>();
  PangoRectangle rect;
  pango_layout_index_to_pos(this->layout_, index, &rect);
  Napi::Object result = Napi::Object::New(env);
  PangoRectangleToObject(env, &rect, &result);
  return result;
}

Napi::Value
NodePangoLayout::IndexToLineX(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "index", env) ||
      !ParamIsBoolean(info[1], "trailing", env)) {
    return env.Undefined();
  }
  int index = info[0].As<Napi::Number>();
  bool trailing = info[1].As<Napi::Boolean>();
  int line, x;
  pango_layout_index_to_line_x(this->layout_, index, trailing, &line, &x);
  Napi::Object result = Napi::Object::New(env);
  result.Set("line", Napi::Number::New(env, line));
  result.Set("x", Napi::Number::New(env, x));
  return result;
}

Napi::Value
NodePangoLayout::XYToIndex(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "x", env) || !ParamIsNumber(info[1], "y", env)) {
    return env.Undefined();
  }
  int x = info[0].As<Napi::Number>();
  int y = info[1].As<Napi::Number>();
  int index, trailing;
  gboolean inside =
    pango_layout_xy_to_index(this->layout_, x, y, &index, &trailing);
  Napi::Object result = Napi::Object::New(env);
  result.Set("index", Napi::Number::New(env, index));
  result.Set("trailing", Napi::Number::New(env, trailing));
  result.Set("inside", Napi::Boolean::New(env, inside));
  return result;
}

Napi::Value
NodePangoLayout::GetCursorPos(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "index", env)) {
    return env.Undefined();
  }
  int index = info[0].As<Napi::Number>();
  PangoRectangle strongPos, weakPos;
  pango_layout_get_cursor_pos(this->layout_, index, &strongPos, &weakPos);
  Napi::Object strong = Napi::Object::New(env);
  PangoRectangleToObject(env, &strongPos, &strong);
  Napi::Object weak = Napi::Object::New(env);
  PangoRectangleToObject(env, &weakPos, &weak);
  Napi::Object result = Napi::Object::New(env);
  result.Set("strongPos", strong);
  result.Set("weakPos", weak);
  return result;
}

Napi::Value
NodePangoLayout::MoveCursorVisually(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 4, env)) {
    return env.Undefined();
  }
  if (!ParamIsBoolean(info[0], "strong", env) ||
      !ParamIsNumber(info[1], "index", env) ||
      !ParamIsNumber(info[2], "trailing", env) ||
      !ParamIsNumber(info[3], "direction", env)) {
    return env.Undefined();
  }
  gboolean strong = info[0].As<Napi::Number>();
  int index = info[1].As<Napi::Number>();
  int trailing = info[2].As<Napi::Number>();
  int direction = info[3].As<Napi::Number>();
  int newIndex, newTrailing;
  pango_layout_move_cursor_visually(
    this->layout_, strong, index, trailing, direction, &newIndex, &newTrailing);
  Napi::Object result = Napi::Object::New(env);
  result.Set("index", Napi::Number::New(env, newIndex));
  result.Set("trailing", Napi::Number::New(env, newTrailing));
  return result;
}

Napi::Value
NodePangoLayout::GetExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle ink, logical;
  PangoRectangle *inkPtr = &ink, *logicalPtr = &logical;
  pango_layout_get_extents(this->layout_, inkPtr, logicalPtr);
  Napi::Object result = Napi::Object::New(env);
  if (inkPtr) {
    Napi::Object inkObj = Napi::Object::New(env);
    PangoRectangleToObject(env, &ink, &inkObj);
    result.Set("ink", inkObj);
  } else {
    result.Set("ink", env.Null());
  }
  if (logicalPtr) {
    Napi::Object logicalObj = Napi::Object::New(env);
    PangoRectangleToObject(env, &logical, &logicalObj);
    result.Set("logical", logicalObj);
  } else {
    result.Set("logical", env.Null());
  }
  return result;
}

Napi::Value
NodePangoLayout::GetPixelExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  PangoRectangle ink, logical;
  PangoRectangle *inkPtr = &ink, *logicalPtr = &logical;
  pango_layout_get_pixel_extents(this->layout_, inkPtr, logicalPtr);
  Napi::Object result = Napi::Object::New(env);
  if (inkPtr) {
    Napi::Object inkObj = Napi::Object::New(env);
    PangoRectangleToObject(env, &ink, &inkObj);
    result.Set("ink", inkObj);
  } else {
    result.Set("ink", env.Null());
  }
  if (logicalPtr) {
    Napi::Object logicalObj = Napi::Object::New(env);
    PangoRectangleToObject(env, &logical, &logicalObj);
    result.Set("logical", logicalObj);
  } else {
    result.Set("logical", env.Null());
  }
  return result;
}

Napi::Value
NodePangoLayout::GetSize(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int w, h;
  pango_layout_get_size(this->layout_, &w, &h);
  Napi::Array result = Napi::Array::New(env, 2);
  result.Set("0", Napi::Number::New(env, w));
  result.Set("1", Napi::Number::New(env, h));
  return result;
}

Napi::Value
NodePangoLayout::GetPixelSize(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int w, h;
  pango_layout_get_pixel_size(this->layout_, &w, &h);
  Napi::Array result = Napi::Array::New(env, 2);
  result.Set("0", Napi::Number::New(env, w));
  result.Set("1", Napi::Number::New(env, h));
  return result;
}

Napi::Value
NodePangoLayout::GetBaseline(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int y = pango_layout_get_baseline(this->layout_);
  return Napi::Number::New(env, y);
}

Napi::Value
NodePangoLayout::GetLineCount(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  int c = pango_layout_get_line_count(this->layout_);
  return Napi::Number::New(env, c);
}

Napi::Value
NodePangoLayout::GetLine(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "line", env)) {
    return env.Undefined();
  }
  int index = info[0].As<Napi::Number>();
  PangoLayoutLine* line = pango_layout_get_line(this->layout_, index);
  if (!line) {
    return env.Null();
  }
  return NodePangoLayoutLine::NewInstance(line);
}

Napi::Value
NodePangoLayout::GetLineReadonly(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "line", env)) {
    return env.Undefined();
  }
  int index = info[0].As<Napi::Number>();
  PangoLayoutLine* line = pango_layout_get_line_readonly(this->layout_, index);
  if (!line) {
    return env.Null();
  }
  return NodePangoLayoutLine::NewInstance(line);
}

Napi::Value
NodePangoLayout::GetIter(const Napi::CallbackInfo& info)
{
  PangoLayoutIter* iter = pango_layout_get_iter(this->layout_);
  return NodePangoLayoutIter::NewInstance(iter);
}