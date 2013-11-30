#include <stdio.h>
#include <string.h>
#include <mruby.h>
#include <mruby/proc.h>
#include <mruby/array.h>
#include <mruby/string.h>
#include <mruby/hash.h>

#define p(mrb,obj) mrb_p(mrb,obj)

int mrb2c(mrb_state *mrb, mrb_value v);

int main(int argc, char **argv)
{
    mrb_state *mrb;
    mrb_value ret;
    char script[128] = "";

    mrb = mrb_open();
    if (mrb == NULL) {
        fprintf(stderr, "Error: mrb_open() failed.\n");
        return -1;
    }

    strcpy(script, "100");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "3.14");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "\"abcde\"");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "false");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "true");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "nil");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, ":foo");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "[10, true, \"aaa\"]");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "[10, [\"aa\", \"bb\"], true]");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "{\"a\" => 100, \"b\" => 200, \"c\" => 300}");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    strcpy(script, "{\"a\" => 100, \"b\" => 200, \"c\" => 300}");
    ret = mrb_load_string(mrb, script);
    mrb2c(mrb, ret);
    puts("");


    mrb_close(mrb);

    return 0;
}

int mrb2c(mrb_state *mrb, mrb_value v)
{
    int i;
    mrb_value *ptr;

    switch (mrb_type(v)) {
    case MRB_TT_FALSE:
        printf("false");
        break;
    case MRB_TT_TRUE:
        printf("true");
        break;
    case MRB_TT_FIXNUM:
        printf("%d (fixnum)", mrb_fixnum(v));
        break;
    case MRB_TT_SYMBOL:
        printf("%d (symbol)", mrb_symbol(v));
        break;
    case MRB_TT_FLOAT:
        printf("%e (float)", mrb_float(v));
        break;
//    case MRB_TT_PROC:
    case MRB_TT_ARRAY:
        printf("type = array (len=%d)\n", RARRAY_LEN(v));

        ptr = RARRAY_PTR(v);
        for (i = 0; i < RARRAY_LEN(v); i++) {
            printf("  %d) ", i);
            mrb2c(mrb, ptr[i]);
            if (i + 1 < RARRAY_LEN(v))  puts("");
        }
        break;
    case MRB_TT_HASH:
        printf("type = hash\n");

        mrb_value keys = mrb_hash_keys(mrb, v);

        ptr = RARRAY_PTR(keys);
        for (i = 0; i < RARRAY_LEN(keys); i++) {
            mrb2c(mrb, ptr[i]);
            printf(" = ");
            mrb2c(mrb, mrb_hash_get(mrb, v, ptr[i]));

            if (i + 1 < RARRAY_LEN(keys))  puts("");
        }

        break;
    case MRB_TT_STRING:
        printf("%s (string)", RSTRING_PTR(v));
        break;
    default:
        printf("type = other(%d)", mrb_type(v));
        break;
    }

    return 0;
}

