#!/bin/env ruby

require 'fileutils'

if ARGV.length < 1
  exit 1
end

library_name = ARGV[0]
mgem_name = "mruby-#{library_name}"

puts library_name
puts mgem_name

readme = <<README_TEMPLATE
#{mgem_name}
=========

Dependences
=========

Example
=========

License
=========
MIT License

README_TEMPLATE

mrbgem_rake = <<MRBGEMS_RAKE_TEMPLATE
MRuby::Gem::Specification.new('#{mgem_name}') do |spec|
  spec.license = 'MIT'
  spec.author  = 'mruby developers'
  spec.summary = 'This is a template'
  # spec.add_dependency ''
end
MRBGEMS_RAKE_TEMPLATE

c_source = <<C_SOURCE_TEMPLATE
#include <mruby.h>
#include <stdio.h>

static mrb_value
mrb_#{library_name}_method(mrb_state *mrb, mrb_value self)
{
  puts("Foo> Hello!");
  return self;
}

void
mrb_mruby_#{library_name}_gem_init(mrb_state* mrb)
{
  struct RClass *#{library_name}_class = mrb_define_module(mrb, "#{library_name}");
  mrb_define_class_method(mrb, #{library_name}_class, "call", mrb_#{library_name}_method, MRB_ARGS_NONE());
}

void
mrb_mruby_#{library_name}_gem_final(mrb_state* mrb)
{
  /* finalizer */
}
C_SOURCE_TEMPLATE

test =<<MRB_TEST_TEMPLATE
assert('C Extension Example') do
  Foo.respond_to? :call
end
MRB_TEST_TEMPLATE

FileUtils.mkdir_p mgem_name
FileUtils.mkdir_p "#{mgem_name}/src"
FileUtils.mkdir_p "#{mgem_name}/test"

File.write "#{mgem_name}/README.md", readme
File.write "#{mgem_name}/mrbgem.rake", mrbgem_rake
File.write "#{mgem_name}/src/example.c", c_source
File.write "#{mgem_name}/test/example.rb", test

