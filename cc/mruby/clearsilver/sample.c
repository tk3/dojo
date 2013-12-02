#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <mruby.h>
#include <mruby/proc.h>
#include <mruby/compile.h>
#include <mruby/data.h>
#include <mruby/class.h>
#include <mruby/string.h>

#define p(mrb,obj) mrb_p(mrb,obj)

int define_clearsilver_class(mrb_state *mrb);

int main(int argc, char **argv)
{
    mrb_state     *mrb;
    mrbc_context  *ctx;
    FILE          *fp;
    int           r;
    mrb_value     v;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return -1;
    }

    mrb = mrb_open();
    if (mrb == NULL) {
        fprintf(stderr, "Error: mrb_open() failed.\n");
        return -1;
    }

    define_clearsilver_class(mrb);

    ctx = mrbc_context_new(mrb);
    if (ctx == NULL) {
        fprintf(stderr, "Error: mrbc_context_new() failed.\n");
        mrb_close(mrb);
        return -1;
    }

    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file. filename=[%s]\n", argv[1]);
        mrb_close(mrb);
        return -1;
    }

    mrbc_filename(mrb, ctx, argv[1]);
    mrb_load_file_cxt(mrb, fp, ctx);

    mrbc_context_free(mrb, ctx);

    r = 0;
    if (mrb->exc) {
        if (!mrb_undef_p(v)) {
            p(mrb, mrb_obj_value(mrb->exc));
        }
        r = 1;
    }

    fclose(fp);
    mrb_close(mrb);

    return r;
}

/*--
typedef struct {
    int val;
} foo_t;

static foo_t *mrb_foo_alloc(void)
{
    foo_t *f;

    f = (foo_t *)malloc(sizeof(foo_t));
    if (f == NULL) {
        return NULL;
    }
    memset(f, 0, sizeof(foo_t));

    return f;
}

static void mrb_foo_free(mrb_state *mrb, void *p)
{
    foo_t *f = (foo_t *)p;

    if (f != NULL) {
        free(f);
    }
    fprintf(stderr, "pass: mrb_foo_free()\n");
}

static const mrb_data_type mrb_foo_type = {
  "mrb_foo", mrb_foo_free,
};

static mrb_value mrb_foo_init(mrb_state *mrb, mrb_value self)
{
    foo_t *f;
    static int v = 100;

    f = mrb_foo_alloc();
    f->val = v++;
    fprintf(stderr, "init >> foo = [%p]\n", f); 

    DATA_PTR(self) = f;
    DATA_TYPE(self) = &mrb_foo_type;

    return self;
}

static mrb_value mrb_foo_set(mrb_state *mrb, mrb_value self)
{
    foo_t *f = mrb_get_datatype(mrb, self, &mrb_foo_type);

    fprintf(stderr, "set >> [%p]\n", f);
    fprintf(stderr, "set >> [%d]\n", f->val);

    return mrb_fixnum_value(0);
}
--*/

// HDF
static mrb_value mrb_hdf_init(mrb_state *mrb, mrb_value self)
{
    return self;
}

static mrb_value mrb_hdf_set_value(mrb_state *mrb, mrb_value self)
{
    mrb_value argv1;
    mrb_value argv2;
    int arg;

    arg = mrb_get_args(mrb, "SS", &argv1, &argv2);
    if (arg != 2) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "argument");
    }

    struct RString *name = mrb_str_ptr(argv1);
    struct RString *val = mrb_str_ptr(argv2);

    printf("set_value: %s=%s\n", name->ptr, val->ptr);

    return mrb_fixnum_value(0);
}

static mrb_value mrb_hdf_remove_tree(mrb_state *mrb, mrb_value self)
{
    mrb_value argv1;
    int arg;

    arg = mrb_get_args(mrb, "S", &argv1);
    if (arg != 1) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "argument");
    }

    struct RString *name = mrb_str_ptr(argv1);

    printf("remove_tree: %s\n", name->ptr);

    return mrb_fixnum_value(0);
}

int define_clearsilver_class(mrb_state *mrb)
{
    struct RClass *module_clearsilver;
    struct RClass *class_hdf;
    struct RClass *class_cs;

    module_clearsilver = mrb_define_module(mrb, "ClearSilver");

    class_hdf = mrb_define_class(mrb, "HDF", mrb->object_class);
    mrb_define_method(mrb, class_hdf, "initialize", mrb_hdf_init, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_hdf, "set_value", mrb_hdf_set_value, MRB_ARGS_OPT(2));
    mrb_define_method(mrb, class_hdf, "remove_tree", mrb_hdf_remove_tree, MRB_ARGS_OPT(1));

    class_cs = mrb_define_class(mrb, "CS", mrb->object_class);

    return 0;
}

