#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <ClearSilver.h>

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

// HDF
static void mrb_hdf_free(mrb_state *mrb, void *p)
{
    HDF *hdf = (HDF *)p;

    if (hdf != NULL) {
        hdf_destroy(&hdf);
    }
}

static const mrb_data_type mrb_hdf_type = {
  "mrb_clearsilver_hdf", mrb_hdf_free,
};

static mrb_value mrb_hdf_init(mrb_state *mrb, mrb_value self)
{
    HDF *hdf;

    hdf_init(&hdf);

    DATA_PTR(self) = hdf;
    DATA_TYPE(self) = &mrb_hdf_type;

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

    HDF *hdf = mrb_get_datatype(mrb, self, &mrb_hdf_type);

    struct RString *name = mrb_str_ptr(argv1);
    struct RString *val = mrb_str_ptr(argv2);

    hdf_set_value(hdf, name->ptr, val->ptr);

    return mrb_fixnum_value(0);
}

static mrb_value mrb_hdf_get_value(mrb_state *mrb, mrb_value self)
{
    mrb_value argv1;
    mrb_value argv2;
    int arg;

    arg = mrb_get_args(mrb, "SS", &argv1, &argv2);
    if (arg != 2) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "argument");
    }

    HDF *hdf = mrb_get_datatype(mrb, self, &mrb_hdf_type);

    struct RString *name = mrb_str_ptr(argv1);
    struct RString *def_val = mrb_str_ptr(argv2);

    char *value = hdf_get_value(hdf, name->ptr, def_val->ptr);

    return mrb_str_new(mrb, value, strlen(value));
}

static mrb_value mrb_hdf_remove_tree(mrb_state *mrb, mrb_value self)
{
    mrb_value argv1;
    int arg;

    arg = mrb_get_args(mrb, "S", &argv1);
    if (arg != 1) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "argument");
    }

    HDF *hdf = mrb_get_datatype(mrb, self, &mrb_hdf_type);

    struct RString *name = mrb_str_ptr(argv1);

    hdf_remove_tree(hdf, name->ptr);

    return mrb_fixnum_value(0);
}

static mrb_value mrb_hdf_dump(mrb_state *mrb, mrb_value self)
{
    mrb_value argv1;
    int arg;
    char *prefix = NULL;

    arg = mrb_get_args(mrb, "|S", &argv1);
    if (arg == 1) {
        prefix = RSTRING_PTR(argv1);
    }

    HDF *hdf = mrb_get_datatype(mrb, self, &mrb_hdf_type);

    hdf_dump(hdf, prefix);

    return mrb_fixnum_value(0);
}

// CS
static void mrb_cs_free(mrb_state *mrb, void *p)
{
    CSPARSE *cs = (CSPARSE *)p;

    if (cs != NULL) {
        cs_destroy(&cs);
    }
}

static const mrb_data_type mrb_cs_type = {
  "mrb_clearsilver_cs", mrb_cs_free,
};

static mrb_value mrb_cs_init(mrb_state *mrb, mrb_value self)
{
    // NEOERR *cs_init (CSPARSE **parse, HDF *hdf);

    CSPARSE *cs;
    mrb_value argv1;
    int arg;

    arg = mrb_get_args(mrb, "o", &argv1);
    if (arg != 1) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "argument");
    }

    HDF *hdf = mrb_get_datatype(mrb, argv1, &mrb_hdf_type);
    if (hdf == NULL) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "argument");
    }

    cs_init(&cs, hdf);

    DATA_PTR(self) = cs;
    DATA_TYPE(self) = &mrb_cs_type;

    return self;
}

static mrb_value mrb_cs_parse_file(mrb_state *mrb, mrb_value self)
{
    // NEOERR *cs_parse_file (CSPARSE *parse, const char *path);

    mrb_value argv1;
    int arg;

    arg = mrb_get_args(mrb, "S", &argv1);
    if (arg != 1) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "argument");
    }

    CSPARSE *cs = mrb_get_datatype(mrb, self, &mrb_cs_type);

    cs_parse_file(cs, RSTRING_PTR(argv1));

    return mrb_fixnum_value(0);
}

static mrb_value mrb_cs_parse_string(mrb_state *mrb, mrb_value self)
{
    // NEOERR *cs_parse_string (CSPARSE *parse, char *buf, size_t blen);

    mrb_value argv1;
    int arg;

    arg = mrb_get_args(mrb, "S", &argv1);
    if (arg != 1) {
        mrb_raise(mrb, E_ARGUMENT_ERROR, "argument");
    }

    CSPARSE *cs = mrb_get_datatype(mrb, self, &mrb_cs_type);

    cs_parse_string(cs, RSTRING_PTR(argv1), RSTRING_LEN(argv1));

    return mrb_fixnum_value(0);
}

NEOERR *render_string(void *ctx, char *s)
{
    STRING *out = (STRING *)ctx;

    string_append(out, s);

    return STATUS_OK;
}

static mrb_value mrb_cs_render(mrb_state *mrb, mrb_value self)
{
    // NEOERR *cs_render (CSPARSE *parse, void *ctx, CSOUTFUNC cb);

    CSPARSE *cs = mrb_get_datatype(mrb, self, &mrb_cs_type);

    STRING render_result;

    string_init(&render_result);

    cs_render(cs, &render_result, render_string);

    mrb_value ret = mrb_str_new(mrb, render_result.buf, render_result.len);

    string_clear(&render_result);

    return ret;
}

int define_clearsilver_class(mrb_state *mrb)
{
    struct RClass *module_clearsilver;
    struct RClass *class_hdf;
    struct RClass *class_cs;

    module_clearsilver = mrb_define_module(mrb, "ClearSilver");

    class_hdf = mrb_define_class(mrb, "HDF", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_hdf, MRB_TT_DATA);
    mrb_define_method(mrb, class_hdf, "initialize", mrb_hdf_init, MRB_ARGS_NONE());
    mrb_define_method(mrb, class_hdf, "set_value", mrb_hdf_set_value, MRB_ARGS_OPT(2));
    mrb_define_method(mrb, class_hdf, "get_value", mrb_hdf_get_value, MRB_ARGS_OPT(2));
    mrb_define_method(mrb, class_hdf, "remove_tree", mrb_hdf_remove_tree, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_hdf, "dump", mrb_hdf_dump, MRB_ARGS_ANY());

    class_cs = mrb_define_class(mrb, "CS", mrb->object_class);
    MRB_SET_INSTANCE_TT(class_cs, MRB_TT_DATA);
    mrb_define_method(mrb, class_cs, "initialize", mrb_cs_init, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_cs, "parse_file", mrb_cs_parse_file, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_cs, "parse_string", mrb_cs_parse_string, MRB_ARGS_OPT(1));
    mrb_define_method(mrb, class_cs, "render", mrb_cs_render, MRB_ARGS_NONE());

    return 0;
}

