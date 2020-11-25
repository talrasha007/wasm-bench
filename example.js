const bind = require('./wasm/bind');

function fromIntVector(vec) {
  const size = vec.size();
  const buf = new ArrayBuffer(size * 4);
  const view = new Int32Array(buf);
  for (let i = 0; i < size; i++) {
    view[i] = vec.get(i);
  }
  return view;
}

setTimeout(() => {
  bind.testCall();
  console.log(bind.testRetString());
  console.log(bind.testModifyString('abc'));

  const vec = bind.testStruct({
    key: 'key',
    x: 1, y: -1,
    anyArray: Int32Array.from([1, 2, 3]).buffer
  });
  console.log(fromIntVector(vec));
}, 50);