#include <mruby.h>
#include <mruby/variable.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/data.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <ffi.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static mrb_value
func_ffi_lib(mrb_state *mrb, mrb_value self)
{
  unsigned char *s;
  mrb_int len;

  mrb_get_args(mrb, "s", &s, &len);

  printf("ffi_lib) %s\n", s);

  return self;
}

static mrb_value
func_attach_function(mrb_state *mrb, mrb_value self)
{
  unsigned char *s;
  mrb_int len;

  mrb_get_args(mrb, "s", &s, &len);

  printf("ffi_lib) %s\n", s);

  return self;
}

static mrb_value
func1(mrb_state *mrb, mrb_value self)
{
  mrb_sym sym;

  mrb_get_args(mrb, "n", &sym);

  printf("argv: %s\n", mrb_sym2name(mrb, sym));

  return self;
}

void
mrb_mruby_ffi_gem_init(mrb_state* mrb) {
  mrb_define_method(mrb, mrb->kernel_module, "ffi_lib", func_ffi_lib, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb->kernel_module, "attach_function", func_attach_function, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb->kernel_module, "foo", func1, MRB_ARGS_REQ(1));
}

void
mrb_mruby_ffi_gem_final(mrb_state* mrb) {
  /* finalizer */
}
