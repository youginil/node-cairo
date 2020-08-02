const {CairoSurface, CairoContext, CairoPattern, matrixInit, matrixTranslate} = require('../index.debug');

const s = CairoSurface.imageSurfaceCreate(0, 500, 500);
const ctx = CairoContext.create(s);

// s.writeToPng("./hello.png");

const matrix = matrixInit(100, 0, 0, 100, 10, 10);
console.log(matrix, matrixTranslate);
const result = matrixTranslate(matrix, 0.5, 0.5);
console.log(matrix, result);
