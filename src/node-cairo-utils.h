#ifndef __NODE_CAIRO_UTILS_H__
#define __NODE_CAIRO_UTILS_H__

#include "cairo.h"
#include <napi.h>

Napi::Value
ThrowErrorAsJavaScriptException(const Napi::Env& env, const char* message);

Napi::Value
ThrowTypeErrorAsJavaScriptException(const Napi::Env& env, const char* message);

Napi::Value
ThrowRangeErrorAsJavaScriptException(const Napi::Env& env, const char* message);

Napi::Value
ThrowStatusErrorAsJavaScriptException(const Napi::Env& env,
                                      const char* message,
                                      cairo_status_t status);

bool
CheckArgumentsNumber(const Napi::Env& env, int argsNum, int n);

bool
ParamIsNumber(const Napi::Env& env, const char* name, const Napi::Value& v);
/*
bool
CheckNumberGreaterThan(const Napi::Env& env,
const char* name,
const Napi::Value& v,
const int n,
const bool equal);
bool
CheckNumberLessThan(const Napi::Env& env,
const char* name,
const Napi::Value& v,
const int n,
const bool equal);
*/
bool
ParamIsObject(const Napi::Env& env, const char* name, const Napi::Value& v);
bool
ParamIsString(const Napi::Env& env, const char* name, const Napi::Value& v);
bool
CheckNonBlankString(const Napi::Env& env,
                    const char* name,
                    const Napi::Value& v);

bool
ParamIsFunction(const Napi::Env& env, const char* name, const Napi::Value& v);

bool
ParamIsArrayBuffer(const Napi::Env& env,
                   const char* name,
                   const Napi::Value& v);

bool
ParamIsRectangleInt(const Napi::Env& env,
                    const char* name,
                    const Napi::Value& v);

void
ObjectToRectangleInt(const Napi::Object& obj, cairo_rectangle_int_t* rect);

bool
ParamIsRectangle(const Napi::Env& env, const char* name, const Napi::Value& v);

void
ObjectToRectangle(const Napi::Object& obj, cairo_rectangle_t* rect);

void
RectangleToObject(const Napi::Env& env,
                  const cairo_rectangle_t* rect,
                  Napi::Object* obj);

bool
CheckCairoFormatParameter(const Napi::Env& env, const Napi::Value& v);

bool
ParamIsArray(const Napi::Env& env, const char* name, const Napi::Value& v);

bool
ParamIsMatrix(const Napi::Env& env, const char* name, const Napi::Value& v);

void
ObjectToMatrix(const Napi::Object& obj, cairo_matrix_t* matrix);

void
MatrixToObject(const Napi::Env& env, cairo_matrix_t* matrix, Napi::Object* obj);

bool
ParamIsFontExtents(const Napi::Env& env,
                   const char* name,
                   const Napi::Value& v);

void
ObjectToFontExtents(const Napi::Object& obj, cairo_font_extents_t* extents);

void
FontExtentsToObject(const Napi::Env& env,
                    cairo_font_extents_t* extents,
                    Napi::Object* obj);

bool
ParamIsTextExtents(const Napi::Env& env,
                   const char* name,
                   const Napi::Value& v);

void
ObjectToTextExtents(const Napi::Object& obj, cairo_text_extents_t* extents);

void
TextExtentsToObject(const Napi::Env& env,
                    cairo_text_extents_t* extents,
                    Napi::Object* obj);

void
ObjectToGlyph(const Napi::Object& obj, cairo_glyph_t* glyph);

void
GlyphToObject(const Napi::Env& env, cairo_glyph_t* glyph, Napi::Object* obj);

void
TextClusterToObject(const Napi::Env& env,
                    cairo_text_cluster_t* cluster,
                    Napi::Object* obj);

#endif