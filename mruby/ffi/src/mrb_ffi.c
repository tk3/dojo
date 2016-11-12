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

typedef struct {
  void *handle;
} mrb_ffi_func;

static void mrb_ffi_dl_free(mrb_state *mrb, void *p);
static mrb_value mrb_ffi_dl_new(mrb_state *mrb, mrb_value self);
static mrb_value mrb_ffi_dl_get_name(mrb_state *mrb, mrb_value self);
static mrb_value mrb_ffi_dl_find(mrb_state *mrb, mrb_value self);

static void mrb_ffi_func_free(mrb_state *mrb, void *p);
static mrb_value mrb_ffi_func_new(mrb_state *mrb, mrb_value self);

static const mrb_data_type mrb_ffi_dl_type = {
  "mrb_ffi_dl", mrb_ffi_dl_free,
};

static const mrb_data_type mrb_ffi_func_type = {
  "mrb_ffi_func", mrb_ffi_func_free,
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
  printf("ffi_dl.new) %d\n", flags);

  dl->handle = dlopen((const char*)s, RTLD_LAZY | RTLD_LOCAL);
  if (dl->handle == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "cannot find library");
  }
  dlerror();

  mrb_iv_set(mrb, self, mrb_intern_cstr(mrb, "@name"), mrb_str_new_cstr(mrb, (const char*)s));

  return self;
}

static mrb_value
mrb_ffi_dl_get_name(mrb_state *mrb, mrb_value self)
{
  mrb_value val = mrb_iv_get(mrb, self, mrb_intern_lit(mrb, "@name"));

  return val;
}

static mrb_value
mrb_ffi_dl_find(mrb_state *mrb, mrb_value self)
{
  mrb_ffi_dl *dl;
  mrb_value ffi_function;

  dl = mrb_get_datatype(mrb, self, &mrb_ffi_dl_type);
  if (dl == NULL) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "invalid argument");
  }

#if 0
  void *func;
  char *err_msg;
  func = dlsym(dl->handle, c->init_func_name);
  if ((err_msg = dlerror()) != NULL)  {
    mrb_raise(mrb, E_RUNTIME_ERROR, "cannot find function");
  }
  dlerror();
#endif

  {
    struct RClass *ffi;
    struct RClass *func;
    mrb_value argv[3];
    mrb_ffi_func *ffi_func;
    char *func_name;

    mrb_sym name;
    mrb_value ary;
    mrb_sym ret_type;

    ffi = mrb_module_get(mrb, "FFI");
    func = mrb_class_get_under(mrb, ffi, "Function");

    mrb_get_args(mrb, "nAn", &name, &ary, &ret_type);

    func_name = mrb_sym2name(mrb, name);
    printf("func_name = %s\n", func_name);

    argv[0] = mrb_symbol_value(name);
    argv[1] = ary;
    argv[2] = mrb_symbol_value(ret_type);

    ffi_function = mrb_obj_new(mrb, func, 3, argv);

    ffi_func = mrb_get_datatype(mrb, ffi_function, &mrb_ffi_func_type);
  }

  return ffi_function;
}

////////

static void
mrb_ffi_func_free(mrb_state *mrb, void *p)
{
  free(p);
}

static mrb_value
mrb_ffi_func_new(mrb_state *mrb, mrb_value self)
{
  mrb_ffi_func *func;

  func = (mrb_ffi_func *)malloc(sizeof(mrb_ffi_func));
  if (func == NULL) {
    mrb_raise(mrb, E_RUNTIME_ERROR, "cannot allocate memory");
  }
  func->handle = NULL;

  DATA_PTR(self) = func;
  DATA_TYPE(self) = &mrb_ffi_func_type;

  {
    mrb_sym name;
    mrb_value ary;
    mrb_sym ret_type;

    mrb_get_args(mrb, "nAn", &name, &ary, &ret_type);

    printf("func.new) %s\n", mrb_sym2name(mrb, name));
  }

  return self;
}

////////

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
  struct RClass *ffi_func;

  ffi = mrb_define_module(mrb, "FFI");
  library = mrb_define_module_under(mrb, ffi, "Library");

  ffi_dl = mrb_define_class_under(mrb, ffi, "DynamicLibrary", mrb->object_class);
  MRB_SET_INSTANCE_TT(ffi_dl, MRB_TT_DATA);

  mrb_define_method(mrb, ffi_dl, "initialize", mrb_ffi_dl_new, MRB_ARGS_REQ(2));
  mrb_define_method(mrb, ffi_dl, "name", mrb_ffi_dl_get_name, MRB_ARGS_NONE());
  mrb_define_method(mrb, ffi_dl, "find", mrb_ffi_dl_find, MRB_ARGS_NONE());

  ffi_func = mrb_define_class_under(mrb, ffi, "Function", mrb->object_class);
  MRB_SET_INSTANCE_TT(ffi_func, MRB_TT_DATA);

  mrb_define_method(mrb, ffi_func, "initialize", mrb_ffi_func_new, MRB_ARGS_REQ(3));


  mrb_define_const(mrb, library, "CURRENT_PROCESS", mrb_symbol_value(mrb_intern_cstr(mrb, "current_process")));

  mrb_define_method(mrb, library, "ffi_lib", func_ffi_lib, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, library, "attach_function", func_attach_function, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, mrb->kernel_module, "foo", func1, MRB_ARGS_REQ(1));
}

void
mrb_mruby_ffi_gem_final(mrb_state* mrb) {
  /* finalizer */
}
