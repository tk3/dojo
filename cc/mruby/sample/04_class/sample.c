#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <mruby.h>
#include <mruby/proc.h>

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


static mrb_value mrb_foo_init(mrb_state *mrb, mrb_value self)
{
    return self;
}

int define_foo_class(mrb_state *mrb)
{
    struct RClass *class_foo;

    class_foo  = mrb_define_class(mrb, "Foo", mrb->object_class);

    mrb_define_method(mrb, class_foo, "initialize", mrb_foo_init, MRB_ARGS_NONE());

    return 0;
}

