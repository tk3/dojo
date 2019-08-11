#include <mruby.h>
#include <stdio.h>

#include <mruby/variable.h>  // mrb_iv_set()

static mrb_value
mrb_foo_initialize(mrb_state *mrb, mrb_value self)
{
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "name"), mrb_str_new_cstr(mrb, "aaa"));
  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "description"), mrb_str_new_cstr(mrb, "bbb"));

  return self;
}

static mrb_value
mrb_odbc_foo_name(mrb_state *mrb, mrb_value self)
{
  mrb_value name;

  name = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "name"));

  return name;
}

static mrb_value
mrb_odbc_foo_description(mrb_state *mrb, mrb_value self)
{
  mrb_value description;

  description = mrb_iv_get(mrb, self, mrb_intern_cstr(mrb, "description"));

  return description;
}

void
mrb_mruby_recipe_gem_init(mrb_state* mrb)
{
  struct RClass *module_recipe;
  struct RClass *class_foo;

  // module Recipe
  module_recipe = mrb_define_module(mrb, "Recipe");
  //mrb_define_class_method(mrb, module_recipe, "c_method", mrb_c_method, MRB_ARGS_NONE());


  // class Recipe::Foo
  class_foo = mrb_define_class(mrb, "Foo", mrb->object_class);

  mrb_define_method(mrb, class_foo, "initialize", mrb_foo_initialize, MRB_ARGS_NONE());
  mrb_define_method(mrb, class_foo, "name", mrb_odbc_foo_name, MRB_ARGS_NONE());
  mrb_define_method(mrb, class_foo, "description", mrb_odbc_foo_description, MRB_ARGS_NONE());

}

void
mrb_mruby_recipe_gem_final(mrb_state* mrb)
{
  /* finalizer */
}
