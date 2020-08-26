const { CairoSurface, CairoContext, CairoPattern, matrixInitScale, matrixInitTranslate, matrixScale, matrixTransformPoint, matrixInit, matrixTranslate, matrixTransformDistance, matrixInvert, RsvgHandle  } = require('../index.debug');

const s = CairoSurface.imageSurfaceCreate(0, 500, 500);
const ctx = CairoContext.create(s);


const svgh = RsvgHandle.newFromFile('/Users/yinliguo/Downloads/pic.svg');
console.log(svgh.getIntrinsicDimensions());
svgh.setStylesheet('svg {opacity: 0.1;}');
svgh.renderDocument(ctx, {x: 0, y: 0, width: 300, height: 300});

s.writeToPng("./hello.png");