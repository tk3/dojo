
puts FFI::Library::CURRENT_PROCESS.class

class Foo
  extend FFI::Library

  ffi_lib "aaa"

  attach_function "func"
end


