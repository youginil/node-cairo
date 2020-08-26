export enum CairoStatus {
  SUCCESS = 0,

  NO_MEMORY,
  INVALID_RESTORE,
  INVALID_POP_GROUP,
  NO_CURRENT_POINT,
  INVALID_MATRIX,
  INVALID_STATUS,
  NULL_POINTER,
  INVALID_STRING,
  INVALID_PATH_DATA,
  READ_ERROR,
  WRITE_ERROR,
  SURFACE_FINISHED,
  SURFACE_TYPE_MISMATCH,
  PATTERN_TYPE_MISMATCH,
  INVALID_CONTENT,
  INVALID_FORMAT,
  INVALID_VISUAL,
  FILE_NOT_FOUND,
  INVALID_DASH,
  INVALID_DSC_COMMENT,
  INVALID_INDEX,
  CLIP_NOT_REPRESENTABLE,
  TEMP_FILE_ERROR,
  INVALID_STRIDE,
  FONT_TYPE_MISMATCH,
  USER_FONT_IMMUTABLE,
  USER_FONT_ERROR,
  NEGATIVE_COUNT,
  INVALID_CLUSTERS,
  INVALID_SLANT,
  INVALID_WEIGHT,
  INVALID_SIZE,
  USER_FONT_NOT_IMPLEMENTED,
  DEVICE_TYPE_MISMATCH,
  DEVICE_ERROR,
  INVALID_MESH_CONSTRUCTION,
  DEVICE_FINISHED,
  JBIG2_GLOBAL_MISSING,
  PNG_ERROR,
  FREETYPE_ERROR,
  WIN32_GDI_ERROR,
  TAG_ERROR,

  LAST_STATUS
}

export enum CairoContent {
  COLOR = 0x1000,
  ALPHA = 0x2000,
  COLOR_ALPHA = 0x3000
}

export enum CairoAntialias {
  DEFAULT,

  /* method */
  NONE,
  GRAY,
  SUBPIXEL,

  /* hints */
  FAST,
  GOOD,
  BEST
}

export enum CairoFillRule {
  WINDING,
  EVEN_ODD
}

export enum CairoLineCap {
  BUTT,
  ROUND,
  SQUARE
}

export enum CairoLineJoin {
  MITER,
  ROUND,
  BEVEL
}

export enum CairoOperator {
  CLEAR,

  SOURCE,
  OVER,
  IN,
  OUT,
  ATOP,

  DEST,
  DEST_OVER,
  DEST_IN,
  DEST_OUT,
  DEST_ATOP,

  XOR,
  ADD,
  SATURATE,

  MULTIPLY,
  SCREEN,
  OVERLAY,
  DARKEN,
  LIGHTEN,
  COLOR_DODGE,
  COLOR_BURN,
  HARD_LIGHT,
  SOFT_LIGHT,
  DIFFERENCE,
  EXCLUSION,
  HSL_HUE,
  HSL_SATURATION,
  HSL_COLOR,
  HSL_LUMINOSITY
}

export enum CairoFontSlant {
  NORMAL,
  ITALIC,
  OBLIQUE
}

export enum CairoFontWeight {
  NORMAL,
  BOLD
}

export enum CairoFormat {
  INVALID = -1,
  ARGB32 = 0,
  RGB24 = 1,
  A8 = 2,
  A1 = 3,
  RGB16_565 = 4,
  RGB30 = 5
}

export enum CairoSurfaceType {
  IMAGE,
  PDF,
  PS,
  XLIB,
  XCB,
  GLITZ,
  QUARTZ,
  WIN32,
  BEOS,
  DIRECTFB,
  SVG,
  OS2,
  WIN32_PRINTING,
  QUARTZ_IMAGE,
  SCRIPT,
  QT,
  RECORDING,
  VG,
  GL,
  DRM,
  TEE,
  XML,
  SKIA,
  SUBSURFACE,
  COGL
}

export enum CairoMimeType {
  JPEG = "image/jpeg",
  PNG = "image/png",
  JP2 = "image/jp2",
  URI = "text/x-uri",
  UNIQUE_ID = "application/x-cairo.uuid",
  JBIG2 = "application/x-cairo.jbig2",
  JBIG2_GLOBAL = "application/x-cairo.jbig2-global",
  JBIG2_GLOBAL_ID = "application/x-cairo.jbig2-global-id",
  CCITT_FAX = "image/g3fax",
  CCITT_FAX_PARAMS = "application/x-cairo.ccitt.params",
  EPS = "application/postscript",
  EPS_PARAMS = "application/x-cairo.eps.params"
}

export enum CairoPdfVersion {
  VERSION_1_4,
  VERSION_1_5
}

export enum CairoPdfOutlineFlags {
  OPEN = 0x1,
  BOLD = 0x2,
  ITALIC = 0x4,
}

export enum CairoPdfMetadata {
  TITLE,
  AUTHOR,
  SUBJECT,
  KEYWORDS,
  CREATOR,
  CREATE_DATE,
  MOD_DATE,
}

export enum CairoSvgUnit {
  USER = 0,
  EM,
  EX,
  PX,
  IN,
  CM,
  MM,
  PT,
  PC,
  PERCENT
}

export enum CairoSvgVersion {
  VERSION_1_1,
  VERSION_1_2
}

export enum CairoDeviceType {
  DRM,
  GL,
  SCRIPT,
  XCB,
  XLIB,
  XML,
  COGL,
  WIN32,

  INVALID = -1
}

export enum CairoScriptMode {
  ASCII,
  BINARY
}

export enum CairoExtend {
  NONE,
  REPEAT,
  REFLECT,
  PAD
}

export enum CairoFilter {
  FAST,
  GOOD,
  BEST,
  NEAREST,
  BILINEAR,
  GAUSSIAN
}

export enum CairoPatternType {
  SOLID,
  SURFACE,
  LINEAR,
  RADIAL,
  MESH,
  RASTER_SOURCE
}

export enum CairoFontType {
  TOY,
  FT,
  WIN32,
  QUARTZ,
  USER
}

export type CairoGlyph = {
  index: number;
  x: number;
  y: number;
}

export type CairoMatrix = {
  xx: number;
  yx: number;
  xy: number;
  yy: number;
  x0: number;
  y0: number;
}

export type CairoFontExtents = {
  ascent: number;
  descent: number;
  height: number;
  xAdvance: number;
  yAdvance: number;
}

export type CairoTextExtents = {
  xBearing: number;
  yBearing: number;
  width: number;
  height: number;
  xAdvance: number;
  yAdvance: number;
}

export type CairoRectangle = {
  x: number;
  y: number;
  width: number;
  height: number;
}

export type CairoRectangleInt = {
  x: number;
  y: number;
  width: number;
  height: number;
}

export class CairoContext {
  static create(surface: CairoSurface): CairoContext;
  reference(): this;
  destroy(): this;
  status(): CairoStatus;
  save(): this;
  restore(): this;
  getTarget(): CairoSurface;
  pushGroup(): this;
  pushGroupWithContent(content: CairoContent): this;
  popGroup(): CairoPattern;
  popGroupToSource(): this;
  getGroupTarget(): CairoSurface;
  setSourceRgb(red: number, green: number, blue: number): this;
  setSourceRgba(red: number, green: number, blue: number, alpha: number): this;
  setSource(pattern: CairoPattern): this;
  setSourceSurface(surface: CairoSurface, x: number, y: number): this;
  getSource(): CairoPattern;
  setAntialias(antialias: CairoAntialias): this;
  getAntialias(): CairoAntialias;
  setDash(dashes: number[], offset: number): this;
  getDashCount(): number;
  getDash(): { dashes: number[], offset: number } | null;
  setFillRule(rule: CairoFillRule): this;
  getFillRule(): CairoFillRule;
  setLineCap(cap: CairoLineCap): this;
  getLineCap(): CairoLineCap;
  setLineJoin(join: CairoLineJoin): this;
  getLineJoin(): CairoLineJoin;
  setLineWidth(width: number): this;
  getLineWidth(): number;
  setMiterLimit(limit: number): this;
  getMiterLimit(): number;
  setOperator(operator: CairoOperator): this;
  getOperator(): CairoOperator;
  setTolerance(tolerance: number): this;
  getTolerance(): number;
  clip(): this;
  clipPreserve(): this;
  clipExtents(): { x1: number, y1: number, x2: number, y2: number };
  inClip(x: number, y: number): boolean;
  resetClip(): this;
  // rectangleListDestroy(): this;
  // copyClipRectangleList(): this;
  fill(): this;
  fillPreserve(): this;
  fillExtents(): { x1: number, y1: number, x2: number, y2: number };
  inFill(x: number, y: number): boolean;
  mask(pattern: CairoPattern): this;
  maskSurface(surface: CairoSurface, x: number, y: number): this;
  paint(): this;
  paintWithAlpha(alpha: number): this;
  stroke(): this;
  strokePreserve(): this;
  strokeExtents(): { x1: number, y1: number, x2: number, y2: number };
  inStroke(x: number, y: number): boolean;
  copyPage(): this;
  showPage(): this;
  getReferenceCount(): number;
  // setUserData(key: string, value: unknown): this;
  // getUserData(key: string): unknown;

  /* Paths */
  copyPath(): CairoPath;
  copyPathFlat(): CairoPath;
  appendPath(path: CairoPath): this;
  hasCurrentPoint(): boolean;
  newPath(): this;
  newSubPath(): this;
  closePath(): this;
  arc(x: number, y: number, radius: number, startAngle: number, endAngle: number): this;
  arcNegative(x: number, y: number, radius: number, startAngle: number, endAngle: number): this;
  curveTo(x1: number, y1: number, x2: number, y2: number, x3: number, y3: number): this;
  lineTo(x: number, y: number): this;
  moveTo(x: number, y: number): this;
  rectangle(x: number, y: number, width: number, height: number): this;
  glyphPath(glyphs: CairoGlyph[]): this;
  textPath(text: string): this;
  relCurveTo(x1: number, y1: number, x2: number, y2: number, x3: number, y3: number): this;
  relLineTo(x: number, y: number): this;
  relMoveTo(x: number, y: number): this;
  pathExtents(): { x1: number, y1: number, x2: number, y2: number };

  /* Transformations */
  translate(tx: number, ty: number): this;
  scale(sx: number, sy: number): this;
  rotate(angle: number): this;
  transform(matrix: CairoMatrix): this;
  setMatrix(matrix: CairoMatrix): this;
  getMatrix(): CairoMatrix;
  identityMatrix(): this;
  userToDevice(x: number, y: number): { x: number, y: number };
  userToDeviceDistance(dx: number, dy: number): { dx: number, dy: number };
  deviceToUser(x: number, y: number): { x: number, y: number };
  deviceToUserDistance(dx: number, dy: number): { dx: number, dy: number };

  /* Text */
  selectFontFace(family: string, slant: CairoFontSlant, weight: CairoFontWeight): this;
  setFontSize(size: number): this;
  setFontMatrix(matrix: CairoMatrix): this;
  getFontMatrix(): CairoMatrix;
  setFontOptions(options: CairoFontOptions): this;
  getFontOptions(): CairoFontOptions;
  setFontFace(face: CairoFontFace): this;
  getFontFace(): CairoFontFace;
  setScaledFont(font: CairoScaledFont): this;
  getScaledFont(): CairoScaledFont;
  showText(text: string): this;
  showGlyphs(glyphs: CairoGlyph[]): this;
  // showTextGlyphs(): this;
  fontExtents(): CairoFontExtents;
  textExtents(text: string): CairoTextExtents;
  glyphExtents(glyphs: CairoGlyph[]): CairoTextExtents;
}

export class CairoSurface {
  createSimilar(content: CairoContext, width: number, height: number): CairoSurface;
  createSimilarImage(format: CairoFormat, width: number, height: number): CairoSurface;
  createForRectangle(x: number, y: number, width: number, height: number): CairoSurface;
  reference(): this;
  destroy(): this;
  status(): CairoStatus;
  finish(): this;
  flush(): this;
  getDevice(): CairoDevice;
  getFontOptions(): CairoFontOptions;
  getContent(): CairoContent;
  markDirty(): this;
  markDirtyRectangle(x: number, y: number, width: number, height: number): this;
  setDeviceOffset(x: number, y: number): this;
  getDeviceOffset(): { x: number, y: number };
  getDeviceScale(): { x: number, y: number };
  setDeviceScale(x: number, y: number): this;
  setFallbackResolution(x: number, y: number): this;
  getFallbackResolution(): { x: number, y: number };
  getType(): CairoSurfaceType;
  getReferenceCount(): number;
  // setUserData(key: string, value: unknown): this;
  // getUserData(key: string): unknown;
  copyPage(): this;
  showPage(): this;
  hasShowTextGlyphs(): boolean;
  setMimeData(mime: CairoMimeType, data: ArrayBuffer): this;
  getMimeData(mime: CairoMimeType): ArrayBuffer | null;
  supportsMimeType(mime: CairoMimeType): boolean;
  mapToImage(rect: CairoRectangleInt | null): CairoSurface;
  unmapImage(surface: CairoSurface): this;

  /* Image Surfaces */
  static formatStrideForWidth(format: CairoFormat, width: number): number;
  static imageSurfaceCreate(format: CairoFormat, width: number, height: number): CairoSurface;
  static imageSurfaceCreateForData(data: ArrayBuffer, format: CairoFormat, width: number, height: number, stride: number): CairoSurface;
  // imageSurfaceGetData(): this;
  imageSurfaceGetFormat(): CairoFormat;
  imageSurfaceGetWidth(): number;
  imageSurfaceGetHeight(): number;
  imageSurfaceGetStride(): number;

  /* PDF Surfaces */
  static pdfSurfaceCreate(filename: string, width: number, height: number): CairoSurface;
  // static pdfSurfaceCreateForStream(): this;
  pdfSurfaceRestrictToVersion(version: CairoPdfVersion): this;
  static pdfGetVersions(): number[];
  static pdfVersionToString(version: CairoPdfVersion): string | null;
  pdfSurfaceSetSize(width: number, height: number): this;
  pdfSurfaceAddOutline(parent: number, name: string, attributes: string, flag: CairoPdfOutlineFlags): number;
  pdfSurfaceSetMetadata(metadata: CairoPdfMetadata, value: string): this;
  pdfSurfaceSetPageLabel(label: string): this;
  pdfSurfaceSetThumbnailSize(width: number, height: number): this;

  /* PNG Support */
  static imageSurfaceCreateFromPng(filename: string): CairoSurface;
  // static imageSurfaceCreateFromPngStream(): CairoSurface;
  writeToPng(filename: string): this;
  // writeToPngStream(): this;

  /* Recording Surfaces */
  static recordingSurfaceCreate(content: CairoContent, extents: CairoRectangle): CairoSurface;
  recordingSurfaceInkExtents(): CairoRectangle;
  recordingSurfaceGetExtents(): CairoRectangle;

  /* SVG Surfaces */
  static svgSurfaceCreate(filename: string, width: number, height: number): CairoSurface;
  // static svgSurfaceCreateForStream(): CairoSurface;
  svgSurfaceSetDocumentUnit(unit: CairoSvgUnit): this;
  svgSurfaceRestrictToVersion(version: CairoSvgVersion): this;
  static svgGetVersions(): number[];
  static svgVersionToString(version: CairoSvgVersion): string;

  /* Script Surfaces */
  scriptFromRecordingSurface(device: CairoDevice): this;
  static scriptSurfaceCreate(device: CairoDevice, content: CairoContent, width: number, height: number): CairoSurface;
  static scriptSurfaceCreateForTarget(device: CairoDevice, surface: CairoSurface): CairoSurface;
}

export class CairoPattern {
  addColorStopRgb(offset: number, red: number, green: number, blue: number): this;
  addColorStopRgba(offset: number, red: number, green: number, blue: number, alpha: number): this;
  getColorStopCount(): number;
  getColorStopRgba(): { offset: number, r: number, g: number, b: number, a: number };
  static createRgb(red: number, green: number, blue: number): CairoPattern;
  static createRgba(red: number, green: number, blue: number, alpha: number): CairoPattern;
  getRgba(): { r: number, g: number, b: number, a: number };
  static createForSurface(surface: CairoSurface): CairoPattern;
  getSurface(): CairoSurface | null;
  static createLinear(x0: number, y0: number, x1: number, y1: number): CairoPattern;
  getLinearPoints(): { x0: number, y0: number, x1: number, y1: number };
  static createRadial(x0: number, y0: number, r0: number, x1: number, y1: number, r1: number): CairoPattern;
  getRadialCircles(): { x0: number, y0: number, r0: number, x1: number, y1: number, r1: number };
  static createMesh(): CairoPattern;
  meshPatternBeginPath(): this;
  meshPatternEndPath(): this;
  meshPatternMoveTo(x: number, y: number): this;
  meshPatternLineTo(x: number, y: number): this;
  meshPatternCurveTo(x1: number, y1: number, x2: number, y2: number, x3: number, y3: number): this;
  meshPatternSetControlPoint(point: number, x: number, y: number): this;
  meshPatternSetCornerColorRgb(point: number, red: number, green: number, blue: number): this;
  meshPatternSetCornerColorRgba(point: number, red: number, green: number, blue: number, alpha: number): this;
  meshPatterGetPatchCount(): number;
  meshPatternGetPath(point: number): CairoPath;
  meshPatternGetControlPoint(patch: number, point: number): { x: number, y: number };
  meshPatternGetCornerColorRgba(patch: number, corner: number): { r: number, g: number, b: number, a: number };
  reference(): this;
  destroy(): this;
  status(): CairoStatus;
  setExtend(extend: CairoExtend): this;
  getExtend(): CairoExtend;
  setFilter(filter: CairoFilter): this;
  getFilter(): CairoFilter;
  setMatrix(matrix: CairoMatrix): this;
  getMatrix(): CairoMatrix;
  getType(): CairoPatternType;
  getReferenceCount(): number;
  // setUserData(key: string, data: unknown): this;
  // getUserData(key: string): unknown;
}

export class CairoPath {
  destroy(): this;
}

export class CairoFontOptions {
  setAntialias(antialias: CairoAntialias): this;
}

export class CairoFontFace {
  reference(): this;
  destroy(): this;
  status(): CairoStatus;
  getType(): CairoFontType;
  getReferenceCount(): number;
  // setUserData(key: string, value: unknown): this;
  // getUserData(key: string): unknown;
  static toyFontFaceCreate(family: string, slant: CairoFontSlant, weight: CairoFontWeight): CairoFontFace;
  toyFontFaceGetFamily(): string;
  toyFontFaceGetSlant(): CairoFontSlant;
  toyFontFaceGetWeight(): CairoFontWeight;
}

export class CairoScaledFont {
  static create(fontFace: CairoFontFace, fontMatrix: CairoMatrix, ctm: CairoMatrix, fontOptions: CairoFontOptions): CairoScaledFont;
  reference(): this;
  destroy(): this;
  status(): CairoStatus;
  extents(): CairoFontExtents;
  textExtents(text: string): CairoTextExtents;
  glyphExtents(glyphs: CairoGlyph[]): CairoTextExtents;
  textToGlyphs(x: number, y: number, text: string): { glyphs: CairoGlyph[], clusters: { bytes: number, glyphs: number }[] | null, clusterFlags: number | null };
  getFontFace(): CairoFontFace;
  getFontOptions(): CairoFontOptions;
  getFontMatrix(): CairoMatrix;
  getCtm(): CairoMatrix;
  getScaleMatrix(): CairoMatrix;
  getType(): CairoFontType;
  getReferenceCount(): number;
  // setUserData(key: string, value: unknown): this;
  // getUserData(key: string): unknown;
}

export class CairoDevice {
  reference(): this;
  destroy(): this;
  status(): CairoStatus;
  finish(): this;
  flush(): this;
  getType(): CairoDeviceType;
  getReferenceCount(): number;
  // setUserData(key: string, value: unknown): this;
  // getUserData(key: string): unknown;
  acquire(): this;
  release(): this;
  observerElapsed(): number;
  observerFillElapsed(): number;
  observerGlyphElapsed(): number;
  observerPaintElapsed(): number;
  // observerPrint(): this;
  observerStrokeElapsed(): number;

  /* Script Devices */
  static scriptCreate(filename: string): CairoDevice;
  // static scriptCreateForStream(): CairoDevice;
  scriptGetMode(): CairoScriptMode;
  scriptSetMode(mode: CairoScriptMode): this;
  scriptWriteComment(comment: string): this;
}

export function matrixInit(xx: number, yx: number, xy: number, yy: number, x0: number, y0: number): CairoMatrix;
export function matrixInitIdentity(matrix: CairoMatrix): void;
export function matrixInitTranslate(tx: number, ty: number): CairoMatrix;
export function matrixInitScale(sx: number, sy: number): CairoMatrix;
export function matrixInitRotate(angle: number): CairoMatrix;
export function matrixTranslate(matrix: CairoMatrix, tx: number, ty: number): void;
export function matrixScale(matrix: CairoMatrix, sx: number, sy: number): void;
export function matrixRotate(matrix: CairoMatrix, angle: number): void;
export function matrixInvert(matrix: CairoMatrix): void;
export function matrixMultiply(a: CairoMatrix, b: CairoMatrix): CairoMatrix;
export function matrixTransformDistance(matrix: CairoMatrix, dx: number, dy: number): [number, number];
export function matrixTransformPoint(matrix: CairoMatrix, x: number, y: number): [number, number];

export enum PangoWrapMode {
  WORD,
  CHAR,
  WORD_CHAR
}

export enum PangoEllipsizeMode {
  NONE,
  START,
  MIDDLE,
  END
}

export enum PangoAlignment {
  LEFT,
  CENTER,
  RIGHT
}

export type PangoRectangle = {
  x: number;
  y: number;
  width: number;
  height: number;
}

export class PangoFontDescription {
  static fromString(font: string): PangoFontDescription;
  free(): this;
}

export class PangoLayout {
  static cairoCreateLayout(ctx: CairoContext): PangoLayout;
  cairoUpdateLayout(ctx: CairoContext): this;
  cairoShowLayout(ctx: CairoContext): this;
  setText(text: string): this;
  getText(): string;
  getCharacterCount(): number;
  setMarkup(markup: string): this;
  setMarkupAccel(markup: string, marker: number): number;
  setFontDescription(description: PangoFontDescription): this;
  getFontDescription(): PangoFontDescription;
  setWidth(width: number): this;
  getWidth(): number;
  setHeight(height: number): this;
  getHeight(): number;
  setWrap(wrap: PangoWrapMode): this;
  getWrap(): PangoWrapMode;
  isWrapped(): boolean;
  setEllipsize(ellipsize: PangoEllipsizeMode): this;
  getEllipsize(): PangoEllipsizeMode;
  isEllipsized(): boolean;
  setIndent(indent: number): this;
  getIndent(): number;
  getSpacing(): number;
  setSpacing(spacing: number): this;
  setLineSpacing(spacing: number): this;
  getLineSpacing(): number;
  setJustify(justify: boolean): this;
  getJustify(): boolean;
  setAutoDir(autoDir: boolean): this;
  getAutoDir(): boolean;
  setAlignment(align: PangoAlignment): this;
  getAlignment(): PangoAlignment;
  setSingleParagraphMode(single: boolean): this;
  getSingleParagraphMode(): boolean;
  getUnknownGlyphCount(): number;
  getLogAttrs(): number[];
  getLogAttrsReadonly(): number[];
  indexToPos(index: number): PangoRectangle;
  indexToLineX(index: number, trailing: boolean): { line: number; x: number };
  xyToIndex(x: number, y: number): { index: number; trailing: number; inside: boolean };
  getCursorPos(index: number): { strong: PangoRectangle; weak: PangoRectangle };
  moveCursorVisually(strong: boolean, index: number, trailing: number, direction: number): { index: number; trailing: number };
  getExtents(): { ink: PangoRectangle | null; logical: PangoRectangle | null };
  getPixelExtents(): { ink: PangoRectangle | null; logical: PangoRectangle | null };
  getSize(): [number, number];
  getPixelSize(): [number, number];
  getBaseline(): number;
  getLineCount(): number;
  getLine(index: number): PangoLayoutLine | null;
  getLineReadonly(index: number): PangoLayoutLine | null;
  getIter(): PangoLayoutIter;
}

export class PangoLayoutLine {
  ref(): this;
  unref(): this;
  getExtents(): { ink: PangoRectangle | null; logical: PangoRectangle | null };
  getPixelExtents(): { ink: PangoRectangle | null; logical: PangoRectangle | null };
  indexToX(index: number, trailing: boolean): number;
  xToIndex(x: number): { index: number; trailing: number };
  getXRanges(start: number, end: number): [number, number][];
  getHeight(): number;
}

export class PangoLayoutIter {
  copy(): PangoLayoutIter;
  free(): this;
  nextRun(): boolean;
  nextChar(): boolean;
  nextCluster(): boolean;
  nextLine(): boolean;
  atLastLine(): boolean;
  getIndex(): number;
  getBaseline(): number;
  getLine(): PangoLayoutLine | null;
  getLineReadonly(): PangoLayoutLine | null;
  getLayout(): PangoLayout | null;
  getCharExtents(): PangoRectangle;
  getClusterExtents(): { ink: PangoRectangle | null; logical: PangoRectangle | null };
  getRunExtents(): { ink: PangoRectangle | null; logical: PangoRectangle | null };
  getLineYRange(): [number, number];
  getLineExtents(): { ink: PangoRectangle | null; logical: PangoRectangle | null };
  getLayoutExtents(): { ink: PangoRectangle | null; logical: PangoRectangle | null };
}

export function markupEscapeText(text: string): string;

export enum RsvgUnit {
  PERCENT,
  PX,
  EM,
  EX,
  IN,
  CM,
  MM,
  PT,
  PC
}

export type RsvgLength = { length: number; unit: RsvgUnit };

export type RsvgRectangle = { x: number; y: number; width: number; height: number }

export class RsvgHandle {
  static newFromFile(filename: string): RsvgHandle;
  getIntrinsicDimensions(): { width: RsvgLength | null; height: RsvgLength | null; viewbox: RsvgRectangle | null };
  renderDocument(ctx: CairoContext, viewport: RsvgRectangle): this;
  setStylesheet(css: string): this;
}
