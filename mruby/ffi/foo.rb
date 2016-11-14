
puts FFI::Library::CURRENT_PROCESS.class

class Foo
  extend FFI::Library

  ffi_lib "aaa"

  attach_function "func"
end

dl = FFI::DynamicLibrary.new "/lib/x86_64-linux-gnu/libc.so.6", 1
puts ">> #{dl.name}"

puts "========"
f1 = dl.find :aaa, [:bbb], :ccc
p f1

puts "========"
f2 = dl.find :atoi, [:string], :ccc
p f2
f2.call

puts "========"
f3 = dl.find :puts, [:string], :ccc
p f3
f3.call
f3.call 10, 20
f3.call "Hello world"

puts "========"
func = FFI::Function.new :aaa, [:bbb], :ccc
p func

