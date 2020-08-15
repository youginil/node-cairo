#include "node-cairo-context.h"
#include "node-cairo-device.h"
#include "node-cairo-enum.h"
#include "node-cairo-font-face.h"
#include "node-cairo-font-options.h"
#include "node-cairo-matrix.h"
#include "node-cairo-path.h"
#include "node-cairo-pattern.h"
#include "node-cairo-region.h"
#include "node-cairo-scaled-font.h"
#include "node-cairo-surface.h"

#include "node-pango-enum.h"
#include "node-pango-font-description.h"
#include "node-pango-layout-iter.h"
#include "node-pango-layout-line.h"
#include "node-pango-layout.h"
#include "node-pango-utils.h"

Napi::Object
InitAll(Napi::Env env, Napi::Object exports)
{
  CairoContext::Init(env, exports);
  CairoDevice::Init(env, exports);
  InitEnums(env, exports);
  CairoFontFace::Init(env, exports);
  CairoFontOptions::Init(env, exports);
  InitMatrix(env, exports);
  CairoPath::Init(env, exports);
  CairoPattern::Init(env, exports);
  CairoRegion::Init(env, exports);
  CairoScaledFont::Init(env, exports);
  CairoSurface::Init(env, exports);

  InitPangoEnums(env, exports);
  NodePangoFontDescription::Init(env, exports);
  NodePangoLayout::Init(env, exports);
  NodePangoLayoutIter::Init(env, exports);
  NodePangoLayoutLine::Init(env, exports);
  InitPangoUtils(env, exports);

  return exports;
}

NODE_API_MODULE(cairo, InitAll);