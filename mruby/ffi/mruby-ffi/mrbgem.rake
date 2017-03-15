MRuby::Gem::Specification.new('mruby-ffi') do |spec|
  spec.license = 'MIT'
  spec.author  = 'qtakamitsu <qtakamitsu@gmail.com>'
  spec.summary = 'Message Digest class'

  spec.cc.flags << `pkg-config --cflags libffi`.chomp.split(" ")
  ffi_libs = `pkg-config --libs libffi`.chomp.split(" ")
  spec.linker.library_paths << ffi_libs.map{|i| i.match(/^-L(.+)/){|md| md[1]}}.compact
  spec.linker.libraries << ffi_libs.map{|i| i.match(/^-l(.+)/){|md| md[1]}}.compact
  spec.linker.libraries << "dl"

  spec.add_test_dependency 'mruby-sprintf'
end
