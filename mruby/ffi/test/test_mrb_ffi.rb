
assert "test-1" do
  libc = "/lib/x86_64-linux-gnu/libc.so.6"
  dl = FFI::DynamicLibrary.new libc, 1
  assert_equal dl.name,libc
end

assert "test-2" do
  libc = "/lib/x86_64-linux-gnu/libc.so.6"
  dl = FFI::DynamicLibrary.new libc, 1
  assert_nil dl.find(:aaa, [:bbb], :ccc)
end

assert "test-3" do
  assert_raise(ArgumentError) do
    libc = "/lib/x86_64-linux-gnu/libc.so.6"
    dl = FFI::DynamicLibrary.new libc, 1
    f = dl.find :atoi, [:string], :int
    f.call
  end
end

assert "test-4" do
  assert_raise(ArgumentError) do
    libc = "/lib/x86_64-linux-gnu/libc.so.6"
    dl = FFI::DynamicLibrary.new libc, 1
    f = dl.find :atoi, [:string], :int
    f.call 10, 20
  end
end

assert "test-5" do
  libc = "/lib/x86_64-linux-gnu/libc.so.6"
  dl = FFI::DynamicLibrary.new libc, 1
  f = dl.find :atoi, [:string], :int
  assert_equal f.call(1234), 1234
end

