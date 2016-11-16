
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

#assert "test-2" do
#  assert_raise(ArgumentError) do
#    libc = "/lib/x86_64-linux-gnu/libc.so.6"
#    dl = FFI::DynamicLibrary.new libc, 1
#    dl.find :aaa, [:bbb], :ccc
#  end
#end

