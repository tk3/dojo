
puts FFI::Library::CURRENT_PROCESS.class

class Foo
  extend FFI::Library

  ffi_lib "aaa"

  attach_function "func"
end

dl = FFI::DynamicLibrary.new "/lib/x86_64-linux-gnu/libc.so.6", 1
puts ">> #{dl.name}"

f1 = dl.find :aaa, [:bbb], :ccc
p f1

f2 = dl.find :atoi, [:bbb], :ccc
p f2
f2.call

f3 = dl.find :puts, [:bbb], :ccc
p f3
f3.call

func = FFI::Function.new :aaa, [:bbb], :ccc
p func

