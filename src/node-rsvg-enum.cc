#include "node-rsvg-enum.h"
#include "librsvg/rsvg.h"

Napi::Object
InitRsvgEnums(Napi::Env env, Napi::Object exports)
{
  Napi::Object rsvgUnit = Napi::Object::New(env);
  rsvgUnit.Set("PERCENT", Napi::Number::New(env, RSVG_UNIT_PERCENT));
  rsvgUnit.Set("PX", Napi::Number::New(env, RSVG_UNIT_PX));
  rsvgUnit.Set("EM", Napi::Number::New(env, RSVG_UNIT_EM));
  rsvgUnit.Set("EX", Napi::Number::New(env, RSVG_UNIT_EX));
  rsvgUnit.Set("IN", Napi::Number::New(env, RSVG_UNIT_IN));
  rsvgUnit.Set("CM", Napi::Number::New(env, RSVG_UNIT_CM));
  rsvgUnit.Set("MM", Napi::Number::New(env, RSVG_UNIT_MM));
  rsvgUnit.Set("PT", Napi::Number::New(env, RSVG_UNIT_PT));
  rsvgUnit.Set("PC", Napi::Number::New(env, RSVG_UNIT_PC));
  exports.Set("RsvgUnit", rsvgUnit);
  return exports;
}