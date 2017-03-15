
puts FFI::Library::CURRENT_PROCESS.class

class Foo
  extend FFI::Library

  ffi_lib "aaa"

  attach_function "func"
end

dl = FFI::DynamicLibrary.new "/lib/x86_64-linux-gnu/libc.so.6", 1

puts "========"
f2 = dl.find :atoi, [:string], :int
p f2
f2.call
r = f2.call 1234
p r

puts "========"
func = FFI::Function.new :aaa, [:bbb], :ccc
p func

