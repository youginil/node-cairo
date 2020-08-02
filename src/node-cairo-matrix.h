#ifndef __NODE_CAIRO_MATRIX_H__
#define __NODE_CAIRO_MATRIX_H__

#include <cairo.h>
#include <napi.h>

Napi::Object
InitMatrix(Napi::Env env, Napi::Object exports);

Napi::Value
MatrixInit(const Napi::CallbackInfo& info);

Napi::Value
MatrixInitIdentity(const Napi::CallbackInfo& info);

Napi::Value
MatrixInitTranslate(const Napi::CallbackInfo& info);

Napi::Value
MatrixInitScale(const Napi::CallbackInfo& info);

Napi::Value
MatrixInitRotate(const Napi::CallbackInfo& info);

Napi::Value
MatrixTranslate(const Napi::CallbackInfo& info);

Napi::Value
MatrixScale(const Napi::CallbackInfo& info);

Napi::Value
MatrixRotate(const Napi::CallbackInfo& info);

Napi::Value
MatrixInvert(const Napi::CallbackInfo& info);

Napi::Value
MatrixMultiply(const Napi::CallbackInfo& info);

Napi::Value
MatrixTransformDistance(const Napi::CallbackInfo& info);

Napi::Value
MatrixTransformPoint(const Napi::CallbackInfo& info);

#endif