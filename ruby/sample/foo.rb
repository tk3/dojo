#!/usr/bin/env ruby

require 'yaml'
require 'erb'
require 'pp'

def foo(s)
  
end

def to_binding(config)
  config = {}  unless config.is_a?(Hash)
  config['name'] = {}  unless config.is_a?(Hash)
  binding
end

content = <<TEXT
MRuby::Build.new('<%= config['name'] %>') do |conf|
<%- if config.key?('toolchain') -%>
  toolchain :<%= config['toolchain'] %>
<%- end -%>

<%- if config.key?('debug') -%>
  enable_debug
<%- end -%>

<%- config['gem'].each do |gem| -%>
<%-   if gem.is_a?(String) -%>
  conf.gem '<%= gem %>'
<%-   elsif gem.is_a?(Hash) && gem.key?('github') -%>
  conf.gem :github => '<%= gem['github'] -%>'
<%-   end -%>
<%- end -%>

<%- if config.key?('gembox') -%>
  conf.gembox '<%= config['gembox'] %>'
<%- end -%>
end
TEXT

cross_content = <<TEXT
MRuby::CrossBuild.new('<%= config['name'] %>') do |conf|
<%- if config.key?('toolchain') -%>
  toolchain :<%= config['toolchain'] %>
<%- end -%>

<%- if config.key?('debug') -%>
  enable_debug
<%- end -%>

<%- config['gem'].each do |gem| -%>
<%-   if gem.is_a?(String) -%>
  conf.gem '<%= gem %>'
<%-   elsif gem.is_a?(Hash) && gem.key?('github') -%>
  conf.gem :github => '<%= gem['github'] -%>'
<%-   end -%>
<%- end -%>

<%- if config.key?('gembox') -%>
  conf.gembox '<%= config['gembox'] %>'
<%- end -%>
end
TEXT

yaml = YAML.load(DATA.read)

if yaml.key?('build')
  yaml['build'].keys.each do |name|
    config = yaml['build'][name]
    config['name'] = name
    b = to_binding(config)
    puts ERB.new(content, nil, '-').result(b)
  end
end

if yaml.key?('cross_build')
  yaml['cross_build'].keys.each do |name|
    config = yaml['cross_build'][name]
    config['name'] = name
    b = to_binding(config)
    puts ERB.new(cross_content, nil, '-').result(b)
  end
end

__END__
build:
  host:
    toolchain: gcc
    debug: enable
    gembox: default
    gem:
      - 'examples/mrbgems/c_and_ruby_extension_example'
      - 
        'examples/mrbgems/c_extension_example':
           cc:
             flags: << '-g'
      -
        github: 'masuidrive/mrbgems-example'
        checksum_hash: '76518e8aecd131d047378448ac8055fa29d974a9'
      -
        git: 'git@github.com:masuidrive/mrbgems-example.git'
        branch: 'master'
        options: '-v'

  host-debug:
    toolchain: gcc
    debug: enable
    bintest: enable
    gembox: default
    cc:
      defines: '%w(ENABLE_DEBUG)'
    gem:
        core: mruby-bin-debugger

cross_build:
  '32bit':
    toolchain: gcc
    cc:
      flags: << '-m32'
    linker:
      flags: << '-m32'
    build_mrbtest_lib_only:
    gem:
      - 'examples/mrbgems/c_and_ruby_extension_example'
    test_runner:
      command: 'env'

