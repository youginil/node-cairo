#include "node-pango-font-description.h"
#include "node-cairo-utils.h"

using namespace std;

static Napi::FunctionReference* fontDescriptionCtor =
  new Napi::FunctionReference();

Napi::Object
NodePangoFontDescription::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "PangoFontDescription",
    {
      StaticMethod("fromString", &NodePangoFontDescription::FromString),
      InstanceMethod("free", &NodePangoFontDescription::Free),
    });
  *fontDescriptionCtor = Napi::Persistent(func);
  exports.Set("PangoFontDescription", func);
  return exports;
}

NodePangoFontDescription::NodePangoFontDescription(
  const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<NodePangoFontDescription>(info)
{
  this->description_ = nullptr;
}

NodePangoFontDescription::~NodePangoFontDescription()
{
  if (this->description_) {
    pango_font_description_free(this->description_);
    this->description_ = nullptr;
  }
}

Napi::Object
NodePangoFontDescription::NewInstance(PangoFontDescription* description)
{
  Napi::Object obj = fontDescriptionCtor->New({});
  NodePangoFontDescription* desc =
    Napi::ObjectWrap<NodePangoFontDescription>::Unwrap(obj);
  desc->SetDescription(description);
  return obj;
}

bool
NodePangoFontDescription::HasInstance(const Napi::Value& v)
{
  return v.IsObject() &&
         v.As<Napi::Object>().InstanceOf(fontDescriptionCtor->Value());
}

const PangoFontDescription*
NodePangoFontDescription::GetDescription()
{
  return this->description_;
}

void
NodePangoFontDescription::SetDescription(PangoFontDescription* description)
{
  this->description_ = description;
}

Napi::Value
NodePangoFontDescription::FromString(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env) ||
      !ParamIsString(info[0], "font", env)) {
    return env.Undefined();
  }
  string str = info[0].As<Napi::String>();
  PangoFontDescription* desc = pango_font_description_from_string(str.c_str());
  return NodePangoFontDescription::NewInstance(desc);
}

Napi::Value
NodePangoFontDescription::Free(const Napi::CallbackInfo& info)
{
  if (this->description_) {
    pango_font_description_free(this->description_);
    this->description_ = nullptr;
  }
  return info.This();
}