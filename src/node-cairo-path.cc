#include "node-cairo-path.h"
#include "node-cairo-utils.h"

Napi::FunctionReference* pathConstructor = new Napi::FunctionReference();

Napi::Object
CairoPath::Init(Napi::Env env, Napi::Object exports)
{
  Napi::Function func =
    DefineClass(env,
                "CairoPath",
                {
                  InstanceMethod("destroy", &CairoPath::Destroy),
                });
  *pathConstructor = Napi::Persistent(func);
  exports.Set("CairoPath", func);
  return exports;
}

CairoPath::CairoPath(const Napi::CallbackInfo& info)
  : Napi::ObjectWrap<CairoPath>(info)
{
  this->path_ = nullptr;
}

CairoPath::~CairoPath()
{
  if (this->path_) {
    cairo_path_destroy(this->path_);
    this->path_ = nullptr;
  }
}

Napi::Object
CairoPath::NewInstance(cairo_path_t* path)
{
  Napi::Object obj = pathConstructor->New({});
  CairoPath* p = Napi::ObjectWrap<CairoPath>::Unwrap(obj);
  p->SetPath(path);
  return obj;
}

bool
CairoPath::HasInstance(const Napi::Value& value)
{
  if (!value.IsObject()) {
    return false;
  }
  return value.As<Napi::Object>().InstanceOf(pathConstructor->Value());
}

cairo_path_t*
CairoPath::GetPath()
{
  return this->path_;
}

void
CairoPath::SetPath(cairo_path_t* path)
{
  this->path_ = path;
}

Napi::Value
CairoPath::Destroy(const Napi::CallbackInfo& info)
{
  Napi::Env env = info.Env();
  if (this->path_) {
    cairo_path_destroy(this->path_);
    this->path_ = nullptr;
  }
  return env.Undefined();
}