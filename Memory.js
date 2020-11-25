const bind = require('./wasm/bind');

class Memory {
  constructor(len) {
    this.ptr = bind._malloc(len);
    this.len = len;
  }

  free() {
    bind._free(this.ptr);
    this.len = 0;
  }

  toByteArray() {
    return new Uint8Array(bind.HEAP8.buffer, this.ptr, this.len);
  }
}

module.exports = Memory;