// hello.cc
#include <node.h>

#include "lua.h"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;

void init(Local<Object> exports) {

}

NODE_MODULE(luac, init);
