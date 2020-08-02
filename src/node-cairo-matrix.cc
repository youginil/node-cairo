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
  if (!CheckArgumentsNumber(env, info.Length(), 6)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "xx", info[0]) ||
      !ParamIsNumber(env, "yx", info[1]) ||
      !ParamIsNumber(env, "xy", info[2]) ||
      !ParamIsNumber(env, "yy", info[3]) ||
      !ParamIsNumber(env, "x0", info[4]) ||
      !ParamIsNumber(env, "y0", info[5])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[0])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "translateX", info[0]) ||
      !ParamIsNumber(env, "translateY", info[1])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "scaleX", info[0]) ||
      !ParamIsNumber(env, "scaleY", info[1])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "rotate angle", info[0])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[0]) ||
      !ParamIsNumber(env, "translateX", info[1]) ||
      !ParamIsNumber(env, "translateY", info[2])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[0]) ||
      !ParamIsNumber(env, "scaleX", info[1]) ||
      !ParamIsNumber(env, "scaleY", info[2])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[0]) ||
      !ParamIsNumber(env, "rotate angle", info[1])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[1])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix a", info[0]) ||
      !ParamIsMatrix(env, "matrix b", info[0])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[0]) ||
      !ParamIsNumber(env, "dx", info[1]) ||
      !ParamIsNumber(env, "dy", info[2])) {
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
  if (!CheckArgumentsNumber(env, info.Length(), 3)) {
    return env.Undefined();
  }
  if (!ParamIsMatrix(env, "matrix", info[0]) ||
      !ParamIsNumber(env, "x", info[1]) || !ParamIsNumber(env, "y", info[2])) {
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