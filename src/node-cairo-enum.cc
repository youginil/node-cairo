#include "node-cairo-enum.h"
#include "cairo-pdf.h"
#include "cairo-script.h"
#include "cairo-svg.h"

Napi::Object
InitEnums(Napi::Env env, Napi::Object exports)
{
  Napi::Object status = Napi::Object::New(env);
  status.Set("SUCCESS", Napi::Number::New(env, CAIRO_STATUS_SUCCESS));
  status.Set("NO_MEMORY", Napi::Number::New(env, CAIRO_STATUS_NO_MEMORY));
  status.Set("INVALID_RESTORE",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_RESTORE));
  status.Set("INVALID_POP_GROUP",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_POP_GROUP));
  status.Set("NO_CURRENT_POINT",
             Napi::Number::New(env, CAIRO_STATUS_NO_CURRENT_POINT));
  status.Set("INVALID_MATRIX",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_MATRIX));
  status.Set("INVALID_STATUS",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_STATUS));
  status.Set("NULL_POINTER", Napi::Number::New(env, CAIRO_STATUS_NULL_POINTER));
  status.Set("INVALID_STRING",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_STRING));
  status.Set("INVALID_PATH_DATA",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_PATH_DATA));
  status.Set("READ_ERROR", Napi::Number::New(env, CAIRO_STATUS_READ_ERROR));
  status.Set("WRITE_ERROR", Napi::Number::New(env, CAIRO_STATUS_WRITE_ERROR));
  status.Set("SURFACE_FINISHED",
             Napi::Number::New(env, CAIRO_STATUS_SURFACE_FINISHED));
  status.Set("SURFACE_TYPE_MISMATCH",
             Napi::Number::New(env, CAIRO_STATUS_SURFACE_TYPE_MISMATCH));
  status.Set("PATTERN_TYPE_MISMATCH",
             Napi::Number::New(env, CAIRO_STATUS_PATTERN_TYPE_MISMATCH));
  status.Set("INVALID_CONTENT",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_CONTENT));
  status.Set("INVALID_FORMAT",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_FORMAT));
  status.Set("INVALID_VISUAL",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_VISUAL));
  status.Set("FILE_NOT_FOUND",
             Napi::Number::New(env, CAIRO_STATUS_FILE_NOT_FOUND));
  status.Set("INVALID_DASH", Napi::Number::New(env, CAIRO_STATUS_INVALID_DASH));
  status.Set("INVALID_DSC_COMMENT",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_DSC_COMMENT));
  status.Set("INVALID_INDEX",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_INDEX));
  status.Set("CLIP_NOT_REPRESENTABLE",
             Napi::Number::New(env, CAIRO_STATUS_CLIP_NOT_REPRESENTABLE));
  status.Set("TEMP_FILE_ERROR",
             Napi::Number::New(env, CAIRO_STATUS_TEMP_FILE_ERROR));
  status.Set("INVALID_STRIDE",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_STRIDE));
  status.Set("FONT_TYPE_MISMATCH",
             Napi::Number::New(env, CAIRO_STATUS_FONT_TYPE_MISMATCH));
  status.Set("USER_FONT_IMMUTABLE",
             Napi::Number::New(env, CAIRO_STATUS_USER_FONT_IMMUTABLE));
  status.Set("USER_FONT_ERROR",
             Napi::Number::New(env, CAIRO_STATUS_USER_FONT_ERROR));
  status.Set("NEGATIVE_COUNT",
             Napi::Number::New(env, CAIRO_STATUS_NEGATIVE_COUNT));
  status.Set("INVALID_CLUSTERS",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_CLUSTERS));
  status.Set("INVALID_SLANT",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_SLANT));
  status.Set("INVALID_WEIGHT",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_WEIGHT));
  status.Set("INVALID_SIZE", Napi::Number::New(env, CAIRO_STATUS_INVALID_SIZE));
  status.Set("USER_FONT_NOT_IMPLEMENTED",
             Napi::Number::New(env, CAIRO_STATUS_USER_FONT_NOT_IMPLEMENTED));
  status.Set("DEVICE_TYPE_MISMATCH",
             Napi::Number::New(env, CAIRO_STATUS_DEVICE_TYPE_MISMATCH));
  status.Set("DEVICE_ERROR", Napi::Number::New(env, CAIRO_STATUS_DEVICE_ERROR));
  status.Set("INVALID_MESH_CONSTRUCTION",
             Napi::Number::New(env, CAIRO_STATUS_INVALID_MESH_CONSTRUCTION));
  status.Set("DEVICE_FINISHED",
             Napi::Number::New(env, CAIRO_STATUS_DEVICE_FINISHED));
  status.Set("JBIG2_GLOBAL_MISSING",
             Napi::Number::New(env, CAIRO_STATUS_JBIG2_GLOBAL_MISSING));
  status.Set("PNG_ERROR", Napi::Number::New(env, CAIRO_STATUS_PNG_ERROR));
  status.Set("FREETYPE_ERROR",
             Napi::Number::New(env, CAIRO_STATUS_FREETYPE_ERROR));
  status.Set("WIN32_GDI_ERROR",
             Napi::Number::New(env, CAIRO_STATUS_WIN32_GDI_ERROR));
  status.Set("TAG_ERROR", Napi::Number::New(env, CAIRO_STATUS_TAG_ERROR));
  status.Set("LAST_STATUS", Napi::Number::New(env, CAIRO_STATUS_LAST_STATUS));
  exports.Set("CairoStatus", status);

  Napi::Object content = Napi::Object::New(env);
  content.Set("COLOR", Napi::Number::New(env, CAIRO_CONTENT_COLOR));
  content.Set("ALPHA", Napi::Number::New(env, CAIRO_CONTENT_ALPHA));
  content.Set("COLOR_ALPHA", Napi::Number::New(env, CAIRO_CONTENT_COLOR_ALPHA));
  exports.Set("CairoContent", content);

  Napi::Object antialias = Napi::Object::New(env);
  antialias.Set("DEFAULT", Napi::Number::New(env, CAIRO_ANTIALIAS_DEFAULT));
  antialias.Set("NONE", Napi::Number::New(env, CAIRO_ANTIALIAS_NONE));
  antialias.Set("GRAY", Napi::Number::New(env, CAIRO_ANTIALIAS_GRAY));
  antialias.Set("SUBPIXEL", Napi::Number::New(env, CAIRO_ANTIALIAS_SUBPIXEL));
  antialias.Set("FAST", Napi::Number::New(env, CAIRO_ANTIALIAS_FAST));
  antialias.Set("GOOD", Napi::Number::New(env, CAIRO_ANTIALIAS_GOOD));
  antialias.Set("BEST", Napi::Number::New(env, CAIRO_ANTIALIAS_BEST));
  exports.Set("CairoAntialias", antialias);

  Napi::Object fillRule = Napi::Object::New(env);
  fillRule.Set("WINDING", Napi::Number::New(env, CAIRO_FILL_RULE_WINDING));
  fillRule.Set("EVEN_ODD", Napi::Number::New(env, CAIRO_FILL_RULE_EVEN_ODD));
  exports.Set("CairoFillRule", fillRule);

  Napi::Object lineCap = Napi::Object::New(env);
  lineCap.Set("BUTT", Napi::Number::New(env, CAIRO_LINE_CAP_BUTT));
  lineCap.Set("ROUND", Napi::Number::New(env, CAIRO_LINE_CAP_ROUND));
  lineCap.Set("SQUARE", Napi::Number::New(env, CAIRO_LINE_CAP_SQUARE));
  exports.Set("CairoLineCap", lineCap);

  Napi::Object lineJoin = Napi::Object::New(env);
  lineJoin.Set("MITER", Napi::Number::New(env, CAIRO_LINE_JOIN_MITER));
  lineJoin.Set("ROUND", Napi::Number::New(env, CAIRO_LINE_JOIN_ROUND));
  lineJoin.Set("BEVEL", Napi::Number::New(env, CAIRO_LINE_JOIN_BEVEL));
  exports.Set("CairoLineJoin", lineJoin);

  Napi::Object op = Napi::Object::New(env);
  op.Set("CLEAR", Napi::Number::New(env, CAIRO_OPERATOR_CLEAR));
  op.Set("SOURCE", Napi::Number::New(env, CAIRO_OPERATOR_SOURCE));
  op.Set("OVER", Napi::Number::New(env, CAIRO_OPERATOR_OVER));
  op.Set("IN", Napi::Number::New(env, CAIRO_OPERATOR_IN));
  op.Set("OUT", Napi::Number::New(env, CAIRO_OPERATOR_OUT));
  op.Set("ATOP", Napi::Number::New(env, CAIRO_OPERATOR_ATOP));
  op.Set("DEST", Napi::Number::New(env, CAIRO_OPERATOR_DEST));
  op.Set("DEST_OVER", Napi::Number::New(env, CAIRO_OPERATOR_DEST_OVER));
  op.Set("DEST_IN", Napi::Number::New(env, CAIRO_OPERATOR_DEST_IN));
  op.Set("DEST_OUT", Napi::Number::New(env, CAIRO_OPERATOR_DEST_OUT));
  op.Set("DEST_ATOP", Napi::Number::New(env, CAIRO_OPERATOR_DEST_ATOP));
  op.Set("XOR", Napi::Number::New(env, CAIRO_OPERATOR_XOR));
  op.Set("ADD", Napi::Number::New(env, CAIRO_OPERATOR_ADD));
  op.Set("SATURATE", Napi::Number::New(env, CAIRO_OPERATOR_SATURATE));
  op.Set("MULTIPLY", Napi::Number::New(env, CAIRO_OPERATOR_MULTIPLY));
  op.Set("SCREEN", Napi::Number::New(env, CAIRO_OPERATOR_SCREEN));
  op.Set("OVERLAY", Napi::Number::New(env, CAIRO_OPERATOR_OVERLAY));
  op.Set("DARKEN", Napi::Number::New(env, CAIRO_OPERATOR_DARKEN));
  op.Set("LIGHTEN", Napi::Number::New(env, CAIRO_OPERATOR_LIGHTEN));
  op.Set("COLOR_DODGE", Napi::Number::New(env, CAIRO_OPERATOR_COLOR_DODGE));
  op.Set("COLOR_BURN", Napi::Number::New(env, CAIRO_OPERATOR_COLOR_BURN));
  op.Set("HARD_LIGHT", Napi::Number::New(env, CAIRO_OPERATOR_HARD_LIGHT));
  op.Set("SOFT_LIGHT", Napi::Number::New(env, CAIRO_OPERATOR_SOFT_LIGHT));
  op.Set("DIFFERENCE", Napi::Number::New(env, CAIRO_OPERATOR_DIFFERENCE));
  op.Set("EXCLUSION", Napi::Number::New(env, CAIRO_OPERATOR_EXCLUSION));
  op.Set("HSL_HUE", Napi::Number::New(env, CAIRO_OPERATOR_HSL_HUE));
  op.Set("HSL_SATURATION",
         Napi::Number::New(env, CAIRO_OPERATOR_HSL_SATURATION));
  op.Set("HSL_COLOR", Napi::Number::New(env, CAIRO_OPERATOR_HSL_COLOR));
  op.Set("HSL_LUMINOSITY",
         Napi::Number::New(env, CAIRO_OPERATOR_HSL_LUMINOSITY));
  exports.Set("CairoOperator", op);

  Napi::Object slant = Napi::Object::New(env);
  slant.Set("NORMAL", Napi::Number::New(env, CAIRO_FONT_SLANT_NORMAL));
  slant.Set("ITALIC", Napi::Number::New(env, CAIRO_FONT_SLANT_ITALIC));
  slant.Set("OBLIQUE", Napi::Number::New(env, CAIRO_FONT_SLANT_OBLIQUE));
  exports.Set("CairoFontSlant", slant);

  Napi::Object fontWeight = Napi::Object::New(env);
  fontWeight.Set("NORMAL", Napi::Number::New(env, CAIRO_FONT_WEIGHT_NORMAL));
  fontWeight.Set("BOLD", Napi::Number::New(env, CAIRO_FONT_WEIGHT_BOLD));
  exports.Set("CairoFontWeight", fontWeight);

  Napi::Object format = Napi::Object::New(env);
  format.Set("INVALID", Napi::Number::New(env, CAIRO_FORMAT_INVALID));
  format.Set("ARGB32", Napi::Number::New(env, CAIRO_FORMAT_ARGB32));
  format.Set("RGB24", Napi::Number::New(env, CAIRO_FORMAT_RGB24));
  format.Set("A8", Napi::Number::New(env, CAIRO_FORMAT_A8));
  format.Set("A1", Napi::Number::New(env, CAIRO_FORMAT_A1));
  format.Set("RGB16_565", Napi::Number::New(env, CAIRO_FORMAT_RGB16_565));
  format.Set("RGB30", Napi::Number::New(env, CAIRO_FORMAT_RGB30));
  exports.Set("CairoFormat", format);

  Napi::Object surfaceType = Napi::Object::New(env);
  surfaceType.Set("IMAGE", Napi::Number::New(env, CAIRO_SURFACE_TYPE_IMAGE));
  surfaceType.Set("PDF", Napi::Number::New(env, CAIRO_SURFACE_TYPE_PDF));
  surfaceType.Set("PS", Napi::Number::New(env, CAIRO_SURFACE_TYPE_PS));
  surfaceType.Set("XLIB", Napi::Number::New(env, CAIRO_SURFACE_TYPE_XLIB));
  surfaceType.Set("XCB", Napi::Number::New(env, CAIRO_SURFACE_TYPE_XCB));
  surfaceType.Set("GLITZ", Napi::Number::New(env, CAIRO_SURFACE_TYPE_GLITZ));
  surfaceType.Set("QUARTZ", Napi::Number::New(env, CAIRO_SURFACE_TYPE_QUARTZ));
  surfaceType.Set("WIN32", Napi::Number::New(env, CAIRO_SURFACE_TYPE_WIN32));
  surfaceType.Set("BEOS", Napi::Number::New(env, CAIRO_SURFACE_TYPE_BEOS));
  surfaceType.Set("DIRECTFB",
                  Napi::Number::New(env, CAIRO_SURFACE_TYPE_DIRECTFB));
  surfaceType.Set("SVG", Napi::Number::New(env, CAIRO_SURFACE_TYPE_SVG));
  surfaceType.Set("OS2", Napi::Number::New(env, CAIRO_SURFACE_TYPE_OS2));
  surfaceType.Set("WIN32_PRINTING",
                  Napi::Number::New(env, CAIRO_SURFACE_TYPE_WIN32_PRINTING));
  surfaceType.Set("QUARTZ_IMAGE",
                  Napi::Number::New(env, CAIRO_SURFACE_TYPE_QUARTZ_IMAGE));
  surfaceType.Set("SCRIPT", Napi::Number::New(env, CAIRO_SURFACE_TYPE_SCRIPT));
  surfaceType.Set("QT", Napi::Number::New(env, CAIRO_SURFACE_TYPE_QT));
  surfaceType.Set("RECORDING",
                  Napi::Number::New(env, CAIRO_SURFACE_TYPE_RECORDING));
  surfaceType.Set("VG", Napi::Number::New(env, CAIRO_SURFACE_TYPE_VG));
  surfaceType.Set("GL", Napi::Number::New(env, CAIRO_SURFACE_TYPE_GL));
  surfaceType.Set("DRM", Napi::Number::New(env, CAIRO_SURFACE_TYPE_DRM));
  surfaceType.Set("TEE", Napi::Number::New(env, CAIRO_SURFACE_TYPE_TEE));
  surfaceType.Set("XML", Napi::Number::New(env, CAIRO_SURFACE_TYPE_XML));
  surfaceType.Set("SKIA", Napi::Number::New(env, CAIRO_SURFACE_TYPE_SKIA));
  surfaceType.Set("SUBSURFACE",
                  Napi::Number::New(env, CAIRO_SURFACE_TYPE_SUBSURFACE));
  surfaceType.Set("COGL", Napi::Number::New(env, CAIRO_SURFACE_TYPE_COGL));
  exports.Set("CairoSurfaceType", surfaceType);

  Napi::Object mimeType = Napi::Object::New(env);
  mimeType.Set("JPEGP", "image/jpeg");
  mimeType.Set("PNG", "image/png");
  mimeType.Set("JP2", "image/jp2");
  mimeType.Set("URI", "text/x-uri");
  mimeType.Set("UNIQUE_ID", "application/x-cairo.uuid");
  mimeType.Set("JBIG2", "application/x-cairo.jbig2");
  mimeType.Set("JBIG2_GLOBAL", "application/x-cairo.jbig2-global");
  mimeType.Set("JBIG2_GLOBAL_ID", "application/x-cairo.jbig2-global-id");
  mimeType.Set("CCITT_FAX", "image/g3fax");
  mimeType.Set("CCITT_FAX_PARAMS", "application/x-cairo.ccitt.params");
  mimeType.Set("EPS", "application/postscript");
  mimeType.Set("EPS_PARAMS", "application/x-cairo.eps.params");
  exports.Set("CairoMimeType", mimeType);

  Napi::Object pdfVersion = Napi::Object::New(env);
  pdfVersion.Set("VERSION_1_4", Napi::Number::New(env, CAIRO_PDF_VERSION_1_4));
  pdfVersion.Set("VERSION_1_5", Napi::Number::New(env, CAIRO_PDF_VERSION_1_5));
  exports.Set("CairoPdfVersion", pdfVersion);

  Napi::Object outlineFlags = Napi::Object::New(env);
  outlineFlags.Set("OPEN", Napi::Number::New(env, CAIRO_PDF_OUTLINE_FLAG_OPEN));
  outlineFlags.Set("BOLD", Napi::Number::New(env, CAIRO_PDF_OUTLINE_FLAG_BOLD));
  outlineFlags.Set("ITALIC",
                   Napi::Number::New(env, CAIRO_PDF_OUTLINE_FLAG_ITALIC));
  exports.Set("CairoPdfOutlineFlags", outlineFlags);

  Napi::Object pdfMetadata = Napi::Object::New(env);
  pdfMetadata.Set("TITLE", Napi::Number::New(env, CAIRO_PDF_METADATA_TITLE));
  pdfMetadata.Set("AUTHOR", Napi::Number::New(env, CAIRO_PDF_METADATA_AUTHOR));
  pdfMetadata.Set("SUBJECT",
                  Napi::Number::New(env, CAIRO_PDF_METADATA_SUBJECT));
  pdfMetadata.Set("KEYWORDS",
                  Napi::Number::New(env, CAIRO_PDF_METADATA_KEYWORDS));
  pdfMetadata.Set("CREATOR",
                  Napi::Number::New(env, CAIRO_PDF_METADATA_CREATOR));
  pdfMetadata.Set("CREATE_DATE",
                  Napi::Number::New(env, CAIRO_PDF_METADATA_CREATE_DATE));
  pdfMetadata.Set("MOD_DATE",
                  Napi::Number::New(env, CAIRO_PDF_METADATA_MOD_DATE));
  exports.Set("CairoPdfMetadata", pdfMetadata);

  Napi::Object svgUnit = Napi::Object::New(env);
  svgUnit.Set("USER", Napi::Number::New(env, CAIRO_SVG_UNIT_USER));
  svgUnit.Set("EM", Napi::Number::New(env, CAIRO_SVG_UNIT_EM));
  svgUnit.Set("EX", Napi::Number::New(env, CAIRO_SVG_UNIT_EX));
  svgUnit.Set("PX", Napi::Number::New(env, CAIRO_SVG_UNIT_PX));
  svgUnit.Set("IN", Napi::Number::New(env, CAIRO_SVG_UNIT_IN));
  svgUnit.Set("CM", Napi::Number::New(env, CAIRO_SVG_UNIT_CM));
  svgUnit.Set("MM", Napi::Number::New(env, CAIRO_SVG_UNIT_MM));
  svgUnit.Set("PT", Napi::Number::New(env, CAIRO_SVG_UNIT_PT));
  svgUnit.Set("PC", Napi::Number::New(env, CAIRO_SVG_UNIT_PC));
  svgUnit.Set("PERCENT", Napi::Number::New(env, CAIRO_SVG_UNIT_PERCENT));
  exports.Set("CairoSvgUnit", svgUnit);

  Napi::Object svgVersion = Napi::Object::New(env);
  svgVersion.Set("VERSION_1_1", Napi::Number::New(env, CAIRO_SVG_VERSION_1_1));
  svgVersion.Set("VERSION_1_2", Napi::Number::New(env, CAIRO_SVG_VERSION_1_2));
  exports.Set("CairoSvgVersion", svgVersion);

  Napi::Object deviceType = Napi::Object::New(env);
  deviceType.Set("DRM", Napi::Number::New(env, CAIRO_DEVICE_TYPE_DRM));
  deviceType.Set("GL", Napi::Number::New(env, CAIRO_DEVICE_TYPE_GL));
  deviceType.Set("SCRIPT", Napi::Number::New(env, CAIRO_DEVICE_TYPE_SCRIPT));
  deviceType.Set("XCB", Napi::Number::New(env, CAIRO_DEVICE_TYPE_XCB));
  deviceType.Set("XLIB", Napi::Number::New(env, CAIRO_DEVICE_TYPE_XLIB));
  deviceType.Set("XML", Napi::Number::New(env, CAIRO_DEVICE_TYPE_XML));
  deviceType.Set("COGL", Napi::Number::New(env, CAIRO_DEVICE_TYPE_COGL));
  deviceType.Set("WIN32", Napi::Number::New(env, CAIRO_DEVICE_TYPE_WIN32));
  deviceType.Set("INVALID", Napi::Number::New(env, CAIRO_DEVICE_TYPE_INVALID));
  exports.Set("CairoDeviceType", deviceType);

  Napi::Object scriptMode = Napi::Object::New(env);
  scriptMode.Set("ASCII", Napi::Number::New(env, CAIRO_SCRIPT_MODE_ASCII));
  scriptMode.Set("BINARY", Napi::Number::New(env, CAIRO_SCRIPT_MODE_BINARY));
  exports.Set("CairoScriptMode", scriptMode);

  Napi::Object extend = Napi::Object::New(env);
  extend.Set("NONE", Napi::Number::New(env, CAIRO_EXTEND_NONE));
  extend.Set("REPEAT", Napi::Number::New(env, CAIRO_EXTEND_REPEAT));
  extend.Set("REFLECT", Napi::Number::New(env, CAIRO_EXTEND_REFLECT));
  extend.Set("PAD", Napi::Number::New(env, CAIRO_EXTEND_PAD));
  exports.Set("CairoExtend", extend);

  Napi::Object filter = Napi::Object::New(env);
  filter.Set("FAST", Napi::Number::New(env, CAIRO_FILTER_FAST));
  filter.Set("GOOD", Napi::Number::New(env, CAIRO_FILTER_GOOD));
  filter.Set("BEST", Napi::Number::New(env, CAIRO_FILTER_BEST));
  filter.Set("NEAREST", Napi::Number::New(env, CAIRO_FILTER_NEAREST));
  filter.Set("BILINEAR", Napi::Number::New(env, CAIRO_FILTER_BILINEAR));
  filter.Set("GAUSSIAN", Napi::Number::New(env, CAIRO_FILTER_GAUSSIAN));
  exports.Set("CairoFilter", filter);

  Napi::Object patternType = Napi::Object::New(env);
  patternType.Set("SOLID", Napi::Number::New(env, CAIRO_PATTERN_TYPE_SOLID));
  patternType.Set("SURFACE",
                  Napi::Number::New(env, CAIRO_PATTERN_TYPE_SURFACE));
  patternType.Set("LINEAR", Napi::Number::New(env, CAIRO_PATTERN_TYPE_LINEAR));
  patternType.Set("RADIAL", Napi::Number::New(env, CAIRO_PATTERN_TYPE_RADIAL));
  patternType.Set("MESH", Napi::Number::New(env, CAIRO_PATTERN_TYPE_MESH));
  patternType.Set("RASTER_SOURCE",
                  Napi::Number::New(env, CAIRO_PATTERN_TYPE_RASTER_SOURCE));
  exports.Set("CairoPatternType", patternType);

  Napi::Object fontType = Napi::Object::New(env);
  fontType.Set("TOY", Napi::Number::New(env, CAIRO_FONT_TYPE_TOY));
  fontType.Set("FT", Napi::Number::New(env, CAIRO_FONT_TYPE_FT));
  fontType.Set("WIN32", Napi::Number::New(env, CAIRO_FONT_TYPE_WIN32));
  fontType.Set("QUARTZ", Napi::Number::New(env, CAIRO_FONT_TYPE_QUARTZ));
  fontType.Set("USER", Napi::Number::New(env, CAIRO_FONT_TYPE_USER));
  exports.Set("CairoFontType", fontType);

  return exports;
}