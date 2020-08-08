#include "./node-cairo-matrix.h"
#include "./node-cairo-utils.h"

Napi::Object
InitMatrix(Napi::Env env, Napi::Object exports)
{
  exports.Set("matrixInit", Napi::Function::New(env, MatrixInit));
  exports.Set("matrixInitIdentity",
              Napi::Function::New(env, MatrixInitIdentity));
  exports.Set("matrixInitTranslate",
              Napi::Function::New(env, MatrixInitTranslate));
  exports.Set("matrixInitScale", Napi::Function::New(env, MatrixInitScale));
  exports.Set("matrixInitRotate", Napi::Function::New(env, MatrixInitRotate));
  exports.Set("matrixTranslate", Napi::Function::New(env, MatrixTranslate));
  exports.Set("matrixScale", Napi::Function::New(env, MatrixScale));
  exports.Set("matrixRotate", Napi::Function::New(env, MatrixRotate));
  exports.Set("matrixInvert", Napi::Function::New(env, MatrixInvert));
  exports.Set("matrixMultiply", Napi::Function::New(env, MatrixMultiply));
  exports.Set("matrixTransformDistance",
              Napi::Function::New(env, MatrixTransformDistance));
  exports.Set("matrixTransformPoint",
              Napi::Function::New(env, MatrixTransformPoint));
  return exports;
}

Napi::Value
MatrixInit(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 6, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "xx", env) ||
      !ParamIsNumber(info[1], "yx", env) ||
      !ParamIsNumber(info[2], "xy", env) ||
      !ParamIsNumber(info[3], "yy", env) ||
      !ParamIsNumber(info[4], "x0", env) ||
      !ParamIsNumber(info[5], "y0", env)) {
    return env.Undefined();
  }
  double xx = info[0].As<Napi::Number>();
  double yx = info[1].As<Napi::Number>();
  double xy = info[2].As<Napi::Number>();
  double yy = info[3].As<Napi::Number>();
  double x0 = info[4].As<Napi::Number>();
  double y0 = info[5].As<Napi::Number>();
  cairo_matrix_t matrix;
  cairo_matrix_init(&matrix, xx, yx, xy, yy, x0, y0);
  Napi::Object result = Napi::Object::New(env);
  MatrixToObject(env, &matrix, &result);
  return result;
}

Napi::Value
MatrixInitIdentity(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(info[0], "matrix", env)) {
    return env.Undefined();
  }
  Napi::Object obj = info[0].As<Napi::Object>();
  cairo_matrix_t matrix;
  ObjectToMatrix(obj, &matrix);
  cairo_matrix_init_identity(&matrix);
  MatrixToObject(env, &matrix, &obj);
  return env.Undefined();
}

Napi::Value
MatrixInitTranslate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "translateX", env) ||
      !ParamIsNumber(info[1], "translateY", env)) {
    return env.Undefined();
  }
  double tx = info[0].As<Napi::Number>();
  double ty = info[1].As<Napi::Number>();
  cairo_matrix_t matrix;
  cairo_matrix_init_translate(&matrix, tx, ty);
  Napi::Object result = Napi::Object::New(env);
  MatrixToObject(env, &matrix, &result);
  return result;
}

Napi::Value
MatrixInitScale(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "scaleX", env) ||
      !ParamIsNumber(info[1], "scaleY", env)) {
    return env.Undefined();
  }
  double sx = info[0].As<Napi::Number>();
  double sy = info[1].As<Napi::Number>();
  cairo_matrix_t matrix;
  cairo_matrix_init_scale(&matrix, sx, sy);
  Napi::Object result;
  MatrixToObject(env, &matrix, &result);
  return result;
}

Napi::Value
MatrixInitRotate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(info[0], "rotate angle", env)) {
    return env.Undefined();
  }
  double angle = info[0].As<Napi::Number>();
  cairo_matrix_t matrix;
  cairo_matrix_init_rotate(&matrix, angle);
  Napi::Object result = Napi::Object::New(env);
  MatrixToObject(env, &matrix, &result);
  return result;
}

Napi::Value
MatrixTranslate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 3, env)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(info[0], "matrix", env) ||
      !ParamIsNumber(info[1], "translateX", env) ||
      !ParamIsNumber(info[2], "translateY", env)) {
    return env.Undefined();
  }
  Napi::Object obj = info[0].As<Napi::Object>();
  double tx = info[1].As<Napi::Number>();
  double ty = info[2].As<Napi::Number>();
  cairo_matrix_t matrix;
  cairo_matrix_t* mp = &matrix;
  ObjectToMatrix(obj, &matrix);
  cairo_matrix_translate(mp, tx, ty);
  MatrixToObject(env, mp, &obj);
  return env.Undefined();
}

Napi::Value
MatrixScale(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 3, env)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(info[0], "matrix", env) ||
      !ParamIsNumber(info[1], "scaleX", env) ||
      !ParamIsNumber(info[2], "scaleY", env)) {
    return env.Undefined();
  }
  Napi::Object obj = info[0].As<Napi::Object>();
  cairo_matrix_t matrix;
  ObjectToMatrix(obj, &matrix);
  double sx = info[1].As<Napi::Number>();
  double sy = info[2].As<Napi::Number>();
  cairo_matrix_scale(&matrix, sx, sy);
  MatrixToObject(env, &matrix, &obj);
  return env.Undefined();
}

Napi::Value
MatrixRotate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(info[0], "matrix", env) ||
      !ParamIsNumber(info[1], "rotate angle", env)) {
    return env.Undefined();
  }
  Napi::Object obj = info[0].As<Napi::Object>();
  cairo_matrix_t matrix;
  ObjectToMatrix(obj, &matrix);
  double angle = info[1].As<Napi::Number>();
  cairo_matrix_rotate(&matrix, angle);
  MatrixToObject(env, &matrix, &obj);
  return env.Undefined();
}

Napi::Value
MatrixInvert(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 1, env)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(info[1], "matrix", env)) {
    return env.Undefined();
  }
  Napi::Object obj = info[0].As<Napi::Object>();
  cairo_matrix_t matrix;
  cairo_status_t status = cairo_matrix_invert(&matrix);
  if (status != CAIRO_STATUS_SUCCESS) {
    ThrowStatusErrorAsJavaScriptException(env, "Fail to invert matrix", status);
  }
  MatrixToObject(env, &matrix, &obj);
  return env.Undefined();
}

Napi::Value
MatrixMultiply(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 2, env)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(info[0], "matrix a", env) ||
      !ParamIsMatrix(info[0], "matrix b", env)) {
    return env.Undefined();
  }
  cairo_matrix_t a, b, c;
  ObjectToMatrix(info[0].As<Napi::Object>(), &a);
  ObjectToMatrix(info[1].As<Napi::Object>(), &b);
  cairo_matrix_multiply(&c, &a, &b);
  Napi::Object result = Napi::Object::New(env);
  MatrixToObject(env, &c, &result);
  return result;
}

Napi::Value
MatrixTransformDistance(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 3, env)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(info[0], "matrix", env) ||
      !ParamIsNumber(info[1], "dx", env) ||
      !ParamIsNumber(info[2], "dy", env)) {
    return env.Undefined();
  }
  cairo_matrix_t m;
  ObjectToMatrix(info[0].As<Napi::Object>(), &m);
  double dx = info[1].As<Napi::Number>();
  double dy = info[2].As<Napi::Number>();
  cairo_matrix_transform_distance(&m, &dx, &dy);
  Napi::Float64Array result = Napi::Float64Array::New(env, 2);
  result.Set(Napi::Number::New(env, 0), dx);
  result.Set(Napi::Number::New(env, 1), dy);
  return result;
}

Napi::Value
MatrixTransformPoint(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgsNumber(info.Length(), 3, env)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(info[0], "matrix", env) ||
      !ParamIsNumber(info[1], "x", env) || !ParamIsNumber(info[2], "y", env)) {
    return env.Undefined();
  }
  cairo_matrix_t m;
  ObjectToMatrix(info[0].As<Napi::Object>(), &m);
  double x = info[1].As<Napi::Number>();
  double y = info[2].As<Napi::Number>();
  cairo_matrix_transform_point(&m, &x, &y);
  Napi::Float64Array result = Napi::Float64Array::New(env, 2);
  result.Set(Napi::Number::New(env, 0), x);
  result.Set(Napi::Number::New(env, 1), y);
  return result;
}