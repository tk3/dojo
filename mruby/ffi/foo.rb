
puts FFI::Library::CURRENT_PROCESS.class

class Foo
  extend FFI::Library

  ffi_lib "aaa"

  attach_function "func"
end

dl = FFI::DynamicLibrary.new "/lib/x86_64-linux-gnu/libc.so.6", 1
puts ">> #{dl.name}"

func = FFI::Function.new 10, 20, 30


