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

typedef struct {
  void *handle;
} mrb_ffi_dl;

static void mrb_ffi_dl_free(mrb_state *mrb, void *p);
static mrb_value mrb_ffi_dl_new(mrb_state *mrb, mrb_value self);

static const mrb_data_type mrb_ffi_dl_type = {
  "mrb_ffi_dl", mrb_ffi_dl_free,
};

static void
mrb_ffi_dl_free(mrb_state *mrb, void *p) {
  mrb_ffi_dl *dl = (mrb_ffi_dl *)p;

  if (dl->handle != NULL) {
    dlclose(dl->handle);
  }

  free(dl);
}

static mrb_value
mrb_ffi_dl_new(mrb_state *mrb, mrb_value self)
{
  mrb_ffi_dl *dl;
  unsigned char *s;
  mrb_int len;
  mrb_int flags;

  dl = (mrb_ffi_dl *)malloc(sizeof(mrb_ffi_dl));
  if (dl == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "cannot allocate memory");
  }
  dl->handle = NULL;

  DATA_PTR(self) = dl;
  DATA_TYPE(self) = &mrb_ffi_dl_type;

  mrb_get_args(mrb, "si", &s, &len, &flags);

  printf("ffi_dl.new) %s\n", s);

  return self;
}

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
  struct RClass *ffi;
  struct RClass *library;
  struct RClass *ffi_dl;

  ffi = mrb_define_module(mrb, "FFI");
  library = mrb_define_module_under(mrb, ffi, "Library");

  ffi_dl = mrb_define_class_under(mrb, ffi, "DynamicLibrary", mrb->object_class);
  MRB_SET_INSTANCE_TT(ffi_dl, MRB_TT_DATA);

  mrb_define_method(mrb, ffi_dl, "initialize", mrb_ffi_dl_new, MRB_ARGS_REQ(2));

  mrb_define_const(mrb, library, "CURRENT_PROCESS", mrb_symbol_value(mrb_intern_cstr(mrb, "current_process")));

  mrb_define_method(mrb, library, "ffi_lib", func_ffi_lib, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, library, "attach_function", func_attach_function, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb->kernel_module, "foo", func1, MRB_ARGS_REQ(1));
}

void
mrb_mruby_ffi_gem_final(mrb_state* mrb) {
  /* finalizer */
}
