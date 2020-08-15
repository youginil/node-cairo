const { CairoSurface, CairoContext, PangoLayout, PangoFontDescription, CairoAntialias, markupEscapeText } = require('../index');

const s = CairoSurface.imageSurfaceCreate(0, 500, 500);
const ctx = CairoContext.create(s);

ctx.moveTo(50, 50);
const layout = PangoLayout.cairoCreateLayout(ctx);
layout.setFontDescription(PangoFontDescription.fromString('serif bold 30'));
const text = markupEscapeText('<i>hello world</i>')
console.log(text);
layout.setMarkup(text);
layout.cairoShowLayout(ctx);

s.writeToPng("./hello.png");
