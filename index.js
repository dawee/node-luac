const fs = require('fs');
const _luac  = require('./build/Release/luac');

const luac = module.exports = {};

Object.assign(luac, _luac);

luac.buildToFileSync = (inputFile, outputFile) => luac._build(inputFile, outputFile);
