MRuby::Build.new do |conf|
  toolchain :gcc

  enable_debug

  conf.gem '../mruby-digest-ffi'

  conf.gembox 'default'
end

MRuby::Build.new('test') do |conf|
  toolchain :gcc

  conf.gem '../mruby-digest-ffi'

  enable_debug
  conf.enable_bintest
  conf.enable_test

  conf.gembox 'default'
end

