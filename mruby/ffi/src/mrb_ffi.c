#include <mruby.h>
#include <mruby/variable.h>
#include <mruby/class.h>
#include <mruby/string.h>
#include <mruby/array.h>
#include <mruby/data.h>
#include <mruby/value.h>
#include <sys/types.h>
#include <dlfcn.h>
#include <ffi.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static mrb_value
func_ffi_lib(mrb_state *mrb, mrb_value self)
{
  mrb_value o;
  enum mrb_vtype type;

  mrb_get_args(mrb, "o", &o);

  type = mrb_type(o);
  if (type == MRB_TT_SYMBOL) {
    printf("ffi_lib) %s\n", "symbol");
  } else if (type == MRB_TT_STRING) {
    printf("ffi_lib) %s\n", "string");
  }

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
  mrb_value ary;
  mrb_value v;
  int len;

  mrb_get_args(mrb, "A", &ary);

  len = mrb_ary_len(mrb, ary);

  printf("len: %d\n", mrb_ary_len(mrb, ary));

  for (int i = 0; i < len; i++) {
    v = mrb_ary_ref(mrb, ary, i);
    printf("%d) %d\n", i, mrb_type(v));
  }

  return self;
}

void
mrb_mruby_ffi_gem_init(mrb_state* mrb) {
  mrb_define_global_const(mrb, "CURRENT_PROCESS", mrb_symbol_value(mrb_intern_cstr(mrb, "current_process")));

  mrb_define_method(mrb, mrb->kernel_module, "ffi_lib", func_ffi_lib, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, mrb->kernel_module, "attach_function", func_attach_function, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb->kernel_module, "foo", func1, MRB_ARGS_REQ(1));
}

void
mrb_mruby_ffi_gem_final(mrb_state* mrb) {
  /* finalizer */
}
