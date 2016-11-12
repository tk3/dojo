
puts FFI::Library::CURRENT_PROCESS.class

class Foo
  extend FFI::Library

  ffi_lib "aaa"

  attach_function "func"
end

dl = FFI::DynamicLibrary.new "/lib/x86_64-linux-gnu/libc.so.6", 1
puts ">> #{dl.name}"

f = dl.find :aaa, [:bbb], :ccc
p f

func = FFI::Function.new :aaa, [:bbb], :ccc
p func

