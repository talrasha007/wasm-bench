const { benchmark } = require('@thi.ng/bench');

const bind = require('./wasm/bind.js');
const ptr = require('./wasm/ptr.js');

setTimeout(() => {
  benchmark(() => bind.testCall(), { title: 'bind.testCall', iter: 1000000 });
  benchmark(() => bind.testRetString(), { title: 'bind.testRetString', iter: 1000000 });
  benchmark(() => bind.testModifyString('abc'), { title: 'bind.testModifyString', iter: 1000000 });
  benchmark(() => bind.testStruct({
    key: 'key',
    x: 1, y: -1,
    anyArray: Int32Array.from([1, 2, 3]).buffer
  }), { title: 'bind.testStruct', iter: 1000 });

  benchmark(() => ptr._testCall(), { title: 'ptr._testCall', iter: 1000000 });
  benchmark(() => ptr.ccall('testCall'), { title: 'ptr.ccall(\'testCall\')', iter: 1000000 });
}, 200);
