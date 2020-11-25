// document: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
// memory model doc: https://www.cntofu.com/book/150/zh/ch2-c-js/ch2-03-mem-model.md
#include <stddef.h>
#include <cstdint>
#include <vector>
#include <string>

#include <emscripten/bind.h>
#include <emscripten/val.h>

using namespace std;
using namespace emscripten;

void testCall() { }

val testRetString() {
 return val(string("1234567890"));
}

val testModifyString(string str) {
  str[0] = 'z';
  return val(str);
}

struct ST {
  string key;
  int x, y;
  string anyArray;
};

vector<int> testStruct(ST st) {
  vector<int> ret;
  ret.push_back(st.x);
  ret.push_back(st.y);

  const int* arr = (const int*)&st.anyArray[0];
  for (int i = 0; i < st.anyArray.length() / 4; i++) {
    ret.push_back(arr[i]);
  }

  return move(ret);
}

struct Memory {
  uint8_t *ptr;
  size_t len;
};

val getMemoryPtr(const Memory &mem) {
  return val((uintptr_t)mem.ptr);
}

void setMemoryPtr(Memory &mem, val ptr) {
  mem.ptr = (uint8_t*)ptr.as<uintptr_t>();
}

void FillMemory(Memory mem) {
  for (size_t i = 0; i < mem.len; i++) {
    mem.ptr[i] = i;
  }
}

EMSCRIPTEN_BINDINGS (c) {
  emscripten::function("testCall", &testCall);
  emscripten::function("testRetString", &testRetString);
  emscripten::function("testModifyString", &testModifyString);

  emscripten::function("FillMemory", &FillMemory);
  value_object<Memory>("Memory")
    .field("len", &Memory::len)
    .field("ptr", getMemoryPtr, setMemoryPtr);

  emscripten::function("testStruct", &testStruct);
  register_vector<int>("vector<int>");
  value_object<ST>("ST")
    .field("key", &ST::key)
    .field("x", &ST::x).field("y", &ST::y)
    .field("anyArray", &ST::anyArray);
}