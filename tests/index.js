const cairo = require('../index.debug');

const s1 = cairo.CairoSurface.imageSurfaceCreate(0, 100, 100);
const ctx = cairo.CairoContext.create(s1);
ctx.rectangle(10, 10, 20, 20);
ctx.stroke();
s1.writeToPng("./hello.png");
