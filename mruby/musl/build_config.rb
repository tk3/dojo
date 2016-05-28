MRuby::Build.new do |conf|
  toolchain :gcc

  enable_debug

  conf.gembox 'default'

  conf.cc do |cc|
    cc.command = "musl-gcc" # -static"
    cc.flags = "-static"
  end

  conf.linker do |linker|
    linker.command = "musl-gcc" # -static"
    linker.flags = "-static"
  end
end
