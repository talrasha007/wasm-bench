# wasm-bench
A simple benchmark for wasm.

## Run
```shell script
node bench.js
```

## Build wasm
Use build.sh to build cpp files to wasm.

## Using docker for building
Using docker is an easier way, just create an alias:
```shell script
alias emcc='docker run -v $(pwd):/src --rm emscripten/emsdk emcc'
``` 