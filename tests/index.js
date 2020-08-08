const { CairoSurface, CairoContext, PangoLayout, PangoFontDescription} = require('../index');

const s = CairoSurface.imageSurfaceCreate(0, 500, 500);
const ctx = CairoContext.create(s);

const layout = PangoLayout.cairoCreateLayout(ctx);
layout.setText("Hello world!");
const desc = PangoFontDescription.fromString('Monaco 30');
layout.setFontDescription(desc);
desc.free();
layout.cairoShowLayout(ctx);

s.writeToPng("./hello.png");
