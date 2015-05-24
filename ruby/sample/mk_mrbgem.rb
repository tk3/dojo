#!/bin/env ruby

require 'fileutils'

readme = <<README_TEMPLATE
mruby-foo
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
MRuby::Gem::Specification.new('mruby-foo') do |spec|
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
mrb_foo_method(mrb_state *mrb, mrb_value self)
{
  puts("Foo> Hello!");
  return self;
}

void
mrb_mruby_foo_gem_init(mrb_state* mrb)
{
  struct RClass *foo_class = mrb_define_module(mrb, "Foo");
  mrb_define_class_method(mrb, foo_class, "call", mrb_foo_method, MRB_ARGS_NONE());
}

void
mrb_mruby_foo_gem_final(mrb_state* mrb)
{
  /* finalizer */
}
C_SOURCE_TEMPLATE

test =<<MRB_TEST_TEMPLATE
assert('C Extension Example') do
  Foo.respond_to? :call
end
MRB_TEST_TEMPLATE


mgem_name = 'mruby-aaa'

FileUtils.mkdir_p mgem_name
FileUtils.mkdir_p "#{mgem_name}/src"
FileUtils.mkdir_p "#{mgem_name}/test"

File.write "#{mgem_name}/README.md", readme
File.write "#{mgem_name}/mrbgem.rake", mrbgem_rake
File.write "#{mgem_name}/src/example.c", c_source
File.write "#{mgem_name}/test/example.rb", test

