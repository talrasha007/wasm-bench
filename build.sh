#!/bin/sh

emcc -O3 -o wasm/ptr.js -s EXPORTED_RUNTIME_METHODS=['ccall'] cpp/ptr.cc
emcc --bind -O3 -o wasm/bind.js cpp/bind.cc