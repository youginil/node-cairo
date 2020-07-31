const {CairoSurface, CairoContext, CairoPattern} = require('../index');

const s = CairoSurface.imageSurfaceCreate(0, 500, 500);
const ctx = CairoContext.create(s);

const s1 = CairoSurface.imageSurfaceCreateFromPng('./apple.png');
const pattern = CairoPattern.createForSurface(s1);
ctx.setSource(pattern);
ctx.paint();

s.writeToPng("./hello.png");
