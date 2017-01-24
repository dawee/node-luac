// hello.cc
#include <node.h>

#include "lua.h"

using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Exception;

extern "C" int build_luac(int argc, char* argv[]);

const char* ToCString(const String::Utf8Value& value) {
  return *value;
}

void BuildLuac(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = args.GetIsolate();

  if (args.Length() < 2) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "luac._build needs 2 arguments")));
    return;
  }

  if (!args[0]->IsString() || !args[1]->IsString()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "luac._build needs 2 paths")));
    return;
  }

  v8::String::Utf8Value utf8_source_path(args[0]->ToString());
  v8::String::Utf8Value utf8_output_path(args[1]->ToString());

  const char * source_path = ToCString(utf8_source_path);
  const char * output_path = ToCString(utf8_output_path);
  char * argv[] = {
    "node-luac",
    "-o",
    (char *) output_path,
    (char *) source_path,
  };

  build_luac(4, argv);
}

void init(Local<Object> exports) {
  NODE_SET_METHOD(exports, "_build", BuildLuac);
}

NODE_MODULE(luac, init);
