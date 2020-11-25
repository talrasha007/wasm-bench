const bind = require('./wasm/bind');

setTimeout(() => {
  bind.testCall();
  console.log(bind.testRetString());
  console.log(bind.testModifyString('abc'));
}, 50);