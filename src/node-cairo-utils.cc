#include "node-cairo-utils.h"

using namespace std;

Napi::Value
ThrowErrorAsJavaScriptException(const Napi::Env& env, const char* message)
{
  Napi::Error::New(env, message).ThrowAsJavaScriptException();
  return env.Undefined();
}

Napi::Value
ThrowTypeErrorAsJavaScriptException(const Napi::Env& env, const char* message)
{
  Napi::TypeError::New(env, message).ThrowAsJavaScriptException();
  return env.Undefined();
}

Napi::Value
ThrowRangeErrorAsJavaScriptException(const Napi::Env& env, const char* message)
{
  Napi::RangeError::New(env, message).ThrowAsJavaScriptException();
  return env.Undefined();
}

Napi::Value
ThrowStatusErrorAsJavaScriptException(const Napi::Env& env,
                                      const char* message,
                                      cairo_status_t status)
{
  Napi::Error::New(
    env,
    (string(message) + string(" ") + cairo_status_to_string(status)).c_str());
  return env.Undefined();
}

bool
CheckArgsNumber(int argsNum, int n, const Napi::Env& env)
{
  if (argsNum != n) {
    ThrowErrorAsJavaScriptException(env, "Wrong number of arguments.");
    return false;
  }
  return true;
}

bool
ParamIsNumber(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsNumber()) {
    return true;
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string(name) + string(" is not a number.")).c_str());
  return false;
}

/*
bool
CheckNumberGreaterThan(const Napi::Env& env,
                       const char* name,
                       const Napi::Value& v,
                       int n,
                       bool equal)
{
  if (!ParamIsNumber( v,  name, env)) {
    return false;
  }
  int value = v.As<Napi::Number>();
  if (equal) {
    if (value < n) {
      ThrowRangeErrorAsJavaScriptException(
        env,
        (string(name) + string(" should greater than or equal to ") +
         to_string(n))
          .c_str());
      return false;
    }
  } else if (value <= n) {
    ThrowRangeErrorAsJavaScriptException(env,
                                         (string(name) +
                                          string(" should greater than ") +
                                          to_string(n))
                                           .c_str());
    return false;
  }
  return true;
}

bool
CheckNumberLessThan(const Napi::Env& env,
                    const char* name,
                    const Napi::Value& v,
                    int n,
                    bool equal)
{
  if (!ParamIsNumber( v,  name, env)) {
    return false;
  }
  int value = v.As<Napi::Number>();
  if (equal) {
    if (value > n) {
      ThrowRangeErrorAsJavaScriptException(
        env,
        (string(name) + string(" should less than or equal to ") +
         to_string(n))
          .c_str());
      return false;
    }
  } else if (value >= n) {
    ThrowRangeErrorAsJavaScriptException(env,
                                         (string(name) +
                                          string(" should less than ") +
                                          to_string(n))
                                           .c_str());
    return false;
  }
  return true;
}
*/

bool
ParamIsObject(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsObject()) {
    return true;
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string(name) + string(" is not object.")).c_str());
  return false;
}

bool
ParamIsBoolean(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsBoolean()) {
    return true;
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string(name) + string(" is not boolean.")).c_str());
  return false;
}

bool
ParamIsString(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsString()) {
    return true;
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string(name) + string(" is not string.")).c_str());
  return false;
}

bool
CheckNonBlankString(const Napi::Env& env,
                    const char* name,
                    const Napi::Value& v)
{
  if (!ParamIsString(v, name, env)) {
    return false;
  }
  string str = v.As<Napi::String>();
  if (str.length() == 0) {
    ThrowRangeErrorAsJavaScriptException(
      env, (string("Length of ") + string(name) + string(" is 0")).c_str());
    return false;
  }
  return true;
}

bool
ParamIsFunction(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsFunction()) {
    return true;
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string(name) + string(" is not Function.")).c_str());
  return false;
}

bool
ParamIsArrayBuffer(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsArrayBuffer()) {
    return true;
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string(name) + string(" is not ArrayBuffer.")).c_str());
  return false;
}

bool
ParamIsRectangleInt(const Napi::Value& v,
                    const char* name,
                    const Napi::Env& env)
{
  if (v.IsObject()) {
    Napi::Object obj = v.As<Napi::Object>();
    if (obj.HasOwnProperty("x") && obj.Get("x").IsBigInt() &&
        obj.HasOwnProperty("y") && obj.Get("y").IsBigInt() &&
        obj.HasOwnProperty("width") && obj.Get("width").IsBigInt() &&
        obj.HasOwnProperty("height") && obj.Get("height").IsBigInt()) {
      return true;
    }
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string("Invalid ") + string(name) + string(".")).c_str());
  return false;
}

void
ObjectToRectangleInt(const Napi::Object& obj, cairo_rectangle_int_t* rect)
{
  rect->x = obj.Get("x").As<Napi::Number>();
  rect->y = obj.Get("y").As<Napi::Number>();
  rect->width = obj.Get("width").As<Napi::Number>();
  rect->height = obj.Get("height").As<Napi::Number>();
}

bool
ParamIsRectangle(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsObject()) {
    Napi::Object obj = v.As<Napi::Object>();
    if (obj.HasOwnProperty("x") && obj.Get("x").IsNumber() &&
        obj.HasOwnProperty("y") && obj.Get("y").IsNumber() &&
        obj.HasOwnProperty("width") && obj.Get("width").IsNumber() &&
        obj.HasOwnProperty("height") && obj.Get("height").IsNumber()) {
      return true;
    }
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string("Invalid ") + string(name)).c_str());
  return false;
}

void
ObjectToRectangle(const Napi::Object& obj, cairo_rectangle_t* rect)
{
  rect->x = obj.Get("x").As<Napi::Number>();
  rect->y = obj.Get("y").As<Napi::Number>();
  rect->width = obj.Get("width").As<Napi::Number>();
  rect->height = obj.Get("height").As<Napi::Number>();
}

void
RectangleToObject(const Napi::Env& env,
                  cairo_rectangle_t* rect,
                  Napi::Object* obj)
{
  obj->Set("x", Napi::Number::New(env, rect->x));
  obj->Set("y", Napi::Number::New(env, rect->y));
  obj->Set("width", Napi::Number::New(env, rect->width));
  obj->Set("height", Napi::Number::New(env, rect->height));
}

bool
CheckCairoFormatParameter(const Napi::Env& env, const Napi::Value& v)
{
  if (!v.IsNumber()) {
    ThrowTypeErrorAsJavaScriptException(env, "Invalid format.");
    return false;
  }
  int format = v.As<Napi::Number>();
  if (format != CAIRO_FORMAT_INVALID && format != CAIRO_FORMAT_ARGB32 &&
      format != CAIRO_FORMAT_RGB24 && format != CAIRO_FORMAT_A8 &&
      format != CAIRO_FORMAT_A1 && format != CAIRO_FORMAT_RGB16_565 &&
      format != CAIRO_FORMAT_RGB30) {
    ThrowTypeErrorAsJavaScriptException(env, "Invalid cairo format.");
    return false;
  }
  return true;
}

bool
ParamIsArray(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsArray()) {
    return true;
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string("Invalid ") + string(name)).c_str());
  return false;
}

bool
ParamIsMatrix(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsObject()) {
    Napi::Object obj = v.As<Napi::Object>();
    if (obj.Get("xx").IsNumber() && obj.Get("yx").IsNumber() &&
        obj.Get("xy").IsNumber() && obj.Get("yy").IsNumber() &&
        obj.Get("x0").IsNumber() && obj.Get("y0").IsNumber()) {
      return true;
    }
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string("Invalid ") + string(name)).c_str());
  return false;
}

void
ObjectToMatrix(const Napi::Object& obj, cairo_matrix_t* matrix)
{
  matrix->xx = obj.Get("xx").As<Napi::Number>();
  matrix->yx = obj.Get("yx").As<Napi::Number>();
  matrix->xy = obj.Get("xy").As<Napi::Number>();
  matrix->yy = obj.Get("yy").As<Napi::Number>();
  matrix->x0 = obj.Get("x0").As<Napi::Number>();
  matrix->y0 = obj.Get("y0").As<Napi::Number>();
}

void
MatrixToObject(const Napi::Env& env, cairo_matrix_t* matrix, Napi::Object* obj)
{
  obj->Set("xx", Napi::Number::New(env, matrix->xx));
  obj->Set("yx", Napi::Number::New(env, matrix->yx));
  obj->Set("xy", Napi::Number::New(env, matrix->xy));
  obj->Set("yy", Napi::Number::New(env, matrix->yy));
  obj->Set("x0", Napi::Number::New(env, matrix->x0));
  obj->Set("y0", Napi::Number::New(env, matrix->y0));
}

bool
ParamIsFontExtents(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsObject()) {
    Napi::Object obj = v.As<Napi::Object>();
    if (obj.Get("ascent").IsNumber() && obj.Get("descent").IsNumber() &&
        obj.Get("height").IsNumber() && obj.Get("xAdvance") &&
        obj.Get("yAdvance").IsNumber()) {
      return true;
    }
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string("Invalid ") + string(name)).c_str());
  return false;
}

void
ObjectToFontExtents(const Napi::Object& obj, cairo_font_extents_t* extents)
{
  extents->ascent = obj.Get("ascent").As<Napi::Number>();
  extents->descent = obj.Get("descent").As<Napi::Number>();
  extents->height = obj.Get("height").As<Napi::Number>();
  extents->max_x_advance = obj.Get("xAdvance").As<Napi::Number>();
  extents->max_y_advance = obj.Get("yAdvance").As<Napi::Number>();
}

void
FontExtentsToObject(const Napi::Env& env,
                    cairo_font_extents_t* extents,
                    Napi::Object* obj)
{
  obj->Set("ascent", Napi::Number::New(env, extents->ascent));
  obj->Set("descent", Napi::Number::New(env, extents->descent));
  obj->Set("height", Napi::Number::New(env, extents->height));
  obj->Set("xAdvance", Napi::Number::New(env, extents->max_x_advance));
  obj->Set("yAdvance", Napi::Number::New(env, extents->max_y_advance));
}

bool
ParamIsTextExtents(const Napi::Value& v, const char* name, const Napi::Env& env)
{
  if (v.IsObject()) {
    Napi::Object obj = v.As<Napi::Object>();
    if (obj.Get("xBearing").IsNumber() && obj.Get("yBearing").IsNumber() &&
        obj.Get("width").IsNumber() && obj.Get("height").IsNumber() &&
        obj.Get("xAdvance").IsNumber() && obj.Get("yAdvance").IsNumber()) {
      return true;
    }
  }
  ThrowTypeErrorAsJavaScriptException(
    env, (string("Invalid ") + string(name) + string(".")).c_str());
  return false;
}

void
ObjectToTextExtents(const Napi::Object& obj, cairo_text_extents_t* extents)
{
  extents->x_bearing = obj.Get("xBearing").As<Napi::Number>();
  extents->y_bearing = obj.Get("yBearing").As<Napi::Number>();
  extents->width = obj.Get("width").As<Napi::Number>();
  extents->height = obj.Get("height").As<Napi::Number>();
  extents->x_advance = obj.Get("xAdvance").As<Napi::Number>();
  extents->y_advance = obj.Get("yAdvance").As<Napi::Number>();
}

void
TextExtentsToObject(const Napi::Env& env,
                    cairo_text_extents_t* extents,
                    Napi::Object* obj)
{
  obj->Set("xBearing", Napi::Number::New(env, extents->x_bearing));
  obj->Set("yBearing", Napi::Number::New(env, extents->y_bearing));
  obj->Set("width", Napi::Number::New(env, extents->width));
  obj->Set("height", Napi::Number::New(env, extents->height));
  obj->Set("xAdvance", Napi::Number::New(env, extents->x_advance));
  obj->Set("yAdvance", Napi::Number::New(env, extents->y_advance));
}

void
ObjectToGlyph(const Napi::Object& obj, cairo_glyph_t* glyph)
{
  glyph->index = obj.Get("index").As<Napi::Number>().Uint32Value();
  glyph->x = obj.Get("x").As<Napi::Number>();
  glyph->y = obj.Get("y").As<Napi::Number>();
}

void
GlyphToObject(const Napi::Env& env, cairo_glyph_t* glyph, Napi::Object* obj)
{
  obj->Set("index", Napi::Number::New(env, glyph->index));
  obj->Set("x", Napi::Number::New(env, glyph->x));
  obj->Set("y", Napi::Number::New(env, glyph->y));
}

void
TextClusterToObject(const Napi::Env& env,
                    cairo_text_cluster_t* cluster,
                    Napi::Object* obj)
{
  obj->Set("bytes", Napi::Number::New(env, cluster->num_bytes));
  obj->Set("glyphs", Napi::Number::New(env, cluster->num_glyphs));
}

Napi::Value
PangoLogAttrToValue(const Napi::Env& env, const PangoLogAttr* attr)
{
  int n = 0;
  n |= attr->is_line_break << 12;
  n |= attr->is_mandatory_break << 11;
  n |= attr->is_char_break << 10;
  n |= attr->is_white << 9;
  n |= attr->is_cursor_position << 8;
  n |= attr->is_word_start << 7;
  n |= attr->is_word_end << 6;
  n |= attr->is_sentence_boundary << 5;
  n |= attr->is_sentence_start << 4;
  n |= attr->is_sentence_end << 3;
  n |= attr->backspace_deletes_character << 2;
  n |= attr->is_expandable_space << 1;
  n |= attr->is_word_boundary;
  return Napi::Number::New(env, n);
}

void
PangoRectangleToObject(const Napi::Env& env,
                       PangoRectangle* rect,
                       Napi::Object* obj)
{
  obj->Set("x", Napi::Number::New(env, rect->x));
  obj->Set("y", Napi::Number::New(env, rect->y));
  obj->Set("width", Napi::Number::New(env, rect->width));
  obj->Set("height", Napi::Number::New(env, rect->height));
}