const { CairoSurface, CairoContext, CairoPattern, matrixInitScale, matrixInitTranslate, matrixScale, matrixTransformPoint, matrixInit, matrixTranslate, matrixTransformDistance, matrixInvert  } = require('../index');

const s = CairoSurface.imageSurfaceCreate(0, 500, 500);
const ctx = CairoContext.create(s);

for(let i = 0; i < 4; i++) {
  ctx.moveTo(0, 100 * (i + 1)).lineTo(500, 100 * (i + 1));
  ctx.moveTo(100 * (i + 1), 0).lineTo(100 * (i + 1), 500).stroke();
}

// ctx.translate(250, 250).scale(0.5, 0.5).translate(-250, -250);
// ctx.rectangle(150, 150, 200, 200);
const ow = 1052;
const oh = 1052;
const x = 200;
const y = 200;
const w = 100;
const h = 100;
const cx = 250;
const cy = 250;
const sx = 2;
const sy = 2;
const rx = 250;
const ry = 250;
const angle = Math.PI / 2;

const m = matrixInitTranslate(cx, cy);
matrixScale(m, sx, sy);
matrixTranslate(m, -cx, -cy);
const [x1, y1] = matrixTransformPoint(m, x, y);

ctx.translate(x1, y1).scale(w / ow * sx, h / oh * sy);

const m1 = matrixInitTranslate(x, y);
matrixScale(m1, w / ow, h / oh);
const rx1 = (rx - x) / (w / ow);
const ry1 = (ry - y) / (h / oh)
ctx.translate(rx1, ry1).rotate(angle).translate(-rx1, -ry1);

const s1 = CairoSurface.imageSurfaceCreateFromPng('/Users/yinliguo/js.png');
const pattern = CairoPattern.createForSurface(s1);
ctx.setSource(pattern).paint();

// ctx.rectangle(200, 200, 100, 100).fill();

ctx.fill()


s.writeToPng("./hello.png");
