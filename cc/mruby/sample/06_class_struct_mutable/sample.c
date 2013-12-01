#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <mruby.h>
#include <mruby/proc.h>
#include <mruby/compile.h>
#include <mruby/array.h>
#include <mruby/data.h>
#include <mruby/class.h>

#define p(mrb,obj) mrb_p(mrb,obj)

int define_foo_class(mrb_state *mrb);

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

    define_foo_class(mrb);

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

int define_foo_class(mrb_state *mrb)
{
    struct RClass *class_foo;

    class_foo = mrb_define_class(mrb, "Foo", mrb->object_class);

    MRB_SET_INSTANCE_TT(class_foo, MRB_TT_DATA);

    mrb_define_method(mrb, class_foo, "initialize", mrb_foo_init, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_foo, "set", mrb_foo_set, MRB_ARGS_NONE());

    return 0;
}

