#include "node-cairo-region.h"
#include "node-cairo-utils.h"

using namespace std;

static Napi::FunctionReference* regionConstructor =
  new Napi::FunctionReference();

Napi::Object
CairoRegion::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func = DefineClass(
    env,
    "CairoRegion",
    {
      StaticMethod("create", &CairoRegion::Create),
      StaticMethod("createRectangle", &CairoRegion::CreateRectangle),
      StaticMethod("createRectangles", &CairoRegion::CreateRectangles),
      InstanceMethod("copy", &CairoRegion::Copy),
      InstanceMethod("reference", &CairoRegion::Reference),
      InstanceMethod("destroy", &CairoRegion::Destroy),
      InstanceMethod("status", &CairoRegion::Status),
      InstanceMethod("getExtents", &CairoRegion::GetExtents),
      InstanceMethod("numRectangles", &CairoRegion::NumRectangles),
      InstanceMethod("getRectangle", &CairoRegion::GetRectangle),
      InstanceMethod("isEmpty", &CairoRegion::IsEmpty),
      InstanceMethod("containsPoint", &CairoRegion::ContainsPoint),
      InstanceMethod("containsRectangle", &CairoRegion::ContainsRectangle),
      InstanceMethod("equal", &CairoRegion::Equal),
      InstanceMethod("translate", &CairoRegion::Translate),
      InstanceMethod("intersect", &CairoRegion::Intersect),
      InstanceMethod("intersectRectangle", &CairoRegion::IntersectRectangle),
      InstanceMethod("subtrancts", &CairoRegion::Subtracts),
      InstanceMethod("subtractsRectangle", &CairoRegion::SubTractsRectangle),
      InstanceMethod("union", &CairoRegion::Union),
      InstanceMethod("unionRectangle", &CairoRegion::UnionRectangle),
      InstanceMethod("xor", &CairoRegion::Xor),
      InstanceMethod("xorRectangle", &CairoRegion::XorRectangle),
    });
  *regionConstructor = Napi::Persistent(func);
  exports.Set("CairoRegion", func);
  return exports;
}

CairoRegion::CairoRegion(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoRegion>(info)
{
  this->region_ = nullptr;
}

CairoRegion::~CairoRegion()
{
  if (this->region_) {
    cairo_region_destroy(this->region_);
    this->region_ = nullptr;
  }
}

Napi::Object
CairoRegion::NewInstance(cairo_region_t* region)
{
  Napi::Object obj = regionConstructor->New({});
  CairoRegion* r = Napi::ObjectWrap<CairoRegion>::Unwrap(obj);
  r->SetRegion(region);
  return obj;
}

bool
CairoRegion::HasInstance(const Napi::Value& value)
{
  if (!value.IsObject()) {
    return false;
  }
  return value.As<Napi::Object>().InstanceOf(regionConstructor->Value());
}

cairo_region_t*
CairoRegion::GetRegion()
{
  return this->region_;
}

void
CairoRegion::SetRegion(cairo_region_t* region)
{
  this->region_ = region;
}

Napi::Value
CairoRegion::Create(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_region_t* region = cairo_region_create();
  cairo_status_t status = cairo_region_status(region);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create region.", status);
  }
  return CairoRegion::NewInstance(region);
}

Napi::Value
CairoRegion::CreateRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsRectangleInt(env, "rectangle", info[0])) {
    return env.Undefined();
  }
  cairo_rectangle_int_t rect;
  ObjectToRectangleInt(info[0].As<Napi::Object>(), &rect);
  cairo_region_t* region = cairo_region_create_rectangle(&rect);
  cairo_status_t status = cairo_region_status(region);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create rectangle region.", status);
  }
  return CairoRegion::NewInstance(region);
}

Napi::Value
CairoRegion::CreateRectangles(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsArray(env, "rectangles", info[0])) {
    return env.Undefined();
  }
  Napi::Array arr = info[0].As<Napi::Array>();
  vector<cairo_rectangle_int_t> rectangles;
  for (uint32_t i = 0; i < arr.Length(); i++) {
    Napi::Object item = arr.Get(i).As<Napi::Object>();
    rectangles.push_back(cairo_rectangle_int_t{
      .x = item.Get("x").As<Napi::Number>(),
      .y = item.Get("y").As<Napi::Number>(),
      .width = item.Get("width").As<Napi::Number>(),
      .height = item.Get("height").As<Napi::Number>(),
    });
  }
  cairo_region_t* region =
    cairo_region_create_rectangles(rectangles.data(), rectangles.size());
  cairo_status_t status = cairo_region_status(region);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to create rectangles region.", status);
  }
  return CairoRegion::NewInstance(region);
}

Napi::Value
CairoRegion::Copy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_region_t* region = cairo_region_copy(this->region_);
  cairo_status_t status = cairo_region_status(region);
  if (status != CAIRO_STATUS_SUCCESS) {
    return ThrowStatusErrorAsJavaScriptException(
      env, "Fail to copy region.", status);
  }
  return CairoRegion::NewInstance(region);
}

Napi::Value
CairoRegion::Reference(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_region_reference(this->region_);
  return info.This();
}

Napi::Value
CairoRegion::Destroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_region_destroy(this->region_);
  return info.This();
}

Napi::Value
CairoRegion::Status(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_status_t status = cairo_region_status(this->region_);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoRegion::GetExtents(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_rectangle_int_t extents;
  cairo_region_get_extents(this->region_, &extents);
  Napi::Object result = Napi::Object::New(env);
  result.Set("x", Napi::Number::New(env, extents.x));
  result.Set("y", Napi::Number::New(env, extents.y));
  result.Set("width", Napi::Number::New(env, extents.width));
  result.Set("height", Napi::Number::New(env, extents.height));
  return result;
}

Napi::Value
CairoRegion::NumRectangles(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  int num = cairo_region_num_rectangles(this->region_);
  return Napi::Number::New(env, num);
}

Napi::Value
CairoRegion::GetRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "rectangle index", info[0])) {
    return env.Undefined();
  }
  int index = info[0].As<Napi::Number>();
  cairo_rectangle_int_t rect;
  cairo_region_get_rectangle(this->region_, index, &rect);
  Napi::Object result = Napi::Object::New(env);
  result.Set("x", Napi::Number::New(env, rect.x));
  result.Set("y", Napi::Number::New(env, rect.y));
  result.Set("width", Napi::Number::New(env, rect.width));
  result.Set("height", Napi::Number::New(env, rect.height));
  return result;
}

Napi::Value
CairoRegion::IsEmpty(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 0)) {
    return env.Undefined();
  }
  cairo_bool_t empty = cairo_region_is_empty(this->region_);
  return Napi::Boolean::New(env, empty);
}

Napi::Value
CairoRegion::ContainsPoint(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  int x = info[0].As<Napi::Number>();
  int y = info[1].As<Napi::Number>();
  cairo_bool_t in = cairo_region_contains_point(this->region_, x, y);
  return Napi::Boolean::New(env, in);
}

Napi::Value
CairoRegion::ContainsRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsRectangleInt(env, "rectangle", info[0])) {
    return env.Undefined();
  }
  cairo_rectangle_int_t rect;
  ObjectToRectangleInt(info[0].As<Napi::Object>(), &rect);
  cairo_region_overlap_t overlap =
    cairo_region_contains_rectangle(this->region_, &rect);
  return Napi::Number::New(env, overlap);
}

Napi::Value
CairoRegion::Equal(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  cairo_region_t *a, *b;
  if (info[0].IsNull()) {
    a = nullptr;
  } else if (CairoRegion::HasInstance(info[0])) {
    CairoRegion* r =
      Napi::ObjectWrap<CairoRegion>::Unwrap(info[0].As<Napi::Object>());
    a = r->GetRegion();
  } else {
    return ThrowTypeErrorAsJavaScriptException(env,
                                               "Invalid the first region.");
  }
  if (info[1].IsNull()) {
    b = nullptr;
  } else if (CairoRegion::HasInstance(info[1])) {
    CairoRegion* r =
      Napi::ObjectWrap<CairoRegion>::Unwrap(info[1].As<Napi::Object>());
    b = r->GetRegion();
  } else {
    return ThrowTypeErrorAsJavaScriptException(env,
                                               "Invalid the second region.");
  }
  cairo_bool_t eq = cairo_region_equal(a, b);
  return Napi::Boolean::New(env, eq);
}

Napi::Value
CairoRegion::Translate(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 2)) {
    return env.Undefined();
  }
  if (!ParamIsNumber(env, "x", info[0]) || !ParamIsNumber(env, "y", info[1])) {
    return env.Undefined();
  }
  int x = info[0].As<Napi::Number>();
  int y = info[1].As<Napi::Number>();
  cairo_region_translate(this->region_, x, y);
  return info.This();
}

Napi::Value
CairoRegion::Intersect(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoRegion::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid region.");
  }
  CairoRegion* other =
    Napi::ObjectWrap<CairoRegion>::Unwrap(info[1].As<Napi::Object>());
  cairo_status_t status =
    cairo_region_intersect(this->region_, other->GetRegion());
  return Napi::Number::New(env, status);
}

Napi::Value
CairoRegion::IntersectRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsRectangleInt(env, "rectangle", info[0])) {
    return env.Undefined();
  }
  cairo_rectangle_int_t rect;
  ObjectToRectangleInt(info[0].As<Napi::Object>(), &rect);
  cairo_status_t status =
    cairo_region_intersect_rectangle(this->region_, &rect);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoRegion::Subtracts(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoRegion::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid region.");
  }
  CairoRegion* r =
    Napi::ObjectWrap<CairoRegion>::Unwrap(info[0].As<Napi::Object>());
  cairo_status_t status = cairo_region_subtract(this->region_, r->GetRegion());
  return Napi::Number::New(env, status);
}

Napi::Value
CairoRegion::SubTractsRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsRectangleInt(env, "rectangle", info[0])) {
    return env.Undefined();
  }
  cairo_rectangle_int_t rect;
  ObjectToRectangleInt(info[0].As<Napi::Object>(), &rect);
  cairo_status_t status = cairo_region_subtract_rectangle(this->region_, &rect);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoRegion::Union(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoRegion::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid region.");
  }
  CairoRegion* r =
    Napi::ObjectWrap<CairoRegion>::Unwrap(info[0].As<Napi::Object>());
  cairo_status_t status = cairo_region_union(this->region_, r->GetRegion());
  return Napi::Number::New(env, status);
}

Napi::Value
CairoRegion::UnionRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsRectangleInt(env, "rectangle", info[0])) {
    return env.Undefined();
  }
  cairo_rectangle_int_t rect;
  ObjectToRectangleInt(info[0].As<Napi::Object>(), &rect);
  cairo_status_t status = cairo_region_union_rectangle(this->region_, &rect);
  return Napi::Number::New(env, status);
}

Napi::Value
CairoRegion::Xor(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!CairoRegion::HasInstance(info[0])) {
    return ThrowTypeErrorAsJavaScriptException(env, "Invalid region.");
  }
  CairoRegion* r =
    Napi::ObjectWrap<CairoRegion>::Unwrap(info[0].As<Napi::Object>());
  cairo_status_t status = cairo_region_xor(this->region_, r->GetRegion());
  return Napi::Number::New(env, status);
}

Napi::Value
CairoRegion::XorRectangle(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (!CheckArgumentsNumber(env, info.Length(), 1)) {
    return env.Undefined();
  }
  if (!ParamIsRectangleInt(env, "rectangle", info[0])) {
    return env.Undefined();
  }
  cairo_rectangle_int_t rect;
  ObjectToRectangleInt(info[0].As<Napi::Object>(), &rect);
  cairo_status_t status = cairo_region_xor_rectangle(this->region_, &rect);
  return Napi::Number::New(env, status);
}