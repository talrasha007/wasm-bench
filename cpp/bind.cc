// document: https://emscripten.org/docs/porting/connecting_cpp_and_javascript/embind.html
// memory model doc: https://www.cntofu.com/book/150/zh/ch2-c-js/ch2-03-mem-model.md
#include <stddef.h>
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

EMSCRIPTEN_BINDINGS (c) {
  emscripten::function("testCall", &testCall);
  emscripten::function("testRetString", &testRetString);
  emscripten::function("testModifyString", &testModifyString);

  emscripten::function("testStruct", &testStruct);
  register_vector<int>("vector<int>");
  value_object<ST>("ST")
    .field("key", &ST::key)
    .field("x", &ST::x).field("y", &ST::y)
    .field("anyArray", &ST::anyArray);
}