#include "node-cairo-context.h"
#include "node-cairo-device.h"
#include "node-cairo-enum.h"
#include "node-cairo-font-face.h"
#include "node-cairo-font-options.h"
#include "node-cairo-path.h"
#include "node-cairo-pattern.h"
#include "node-cairo-region.h"
#include "node-cairo-scaled-font.h"
#include "node-cairo-surface.h"

Napi::Object
InitAll(Napi::Env env, Napi::Object exports)
{
  CairoContext::Init(env, exports);
  CairoDevice::Init(env, exports);
  InitEnums(env, exports);
  CairoFontFace::Init(env, exports);
  CairoFontOptions::Init(env, exports);
  CairoPath::Init(env, exports);
  CairoPattern::Init(env, exports);
  CairoRegion::Init(env, exports);
  CairoScaledFont::Init(env, exports);
  CairoSurface::Init(env, exports);
  return exports;
}

NODE_API_MODULE(cairo, InitAll);