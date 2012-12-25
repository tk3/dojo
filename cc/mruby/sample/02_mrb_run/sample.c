#include <stdio.h>
#include <string.h>

#include "mruby.h"
#include "mruby/proc.h"
#include "mruby/compile.h"
#include "mruby/array.h"

#define p(mrb,obj) mrb_p(mrb,obj)

int main(int argc, char **argv)
{
    mrb_state               *mrb;
    mrbc_context            *ctx;
    struct mrb_parser_state *parser;
    FILE                    *fp;
    int                     r;
    int                     n;
    mrb_value               v;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return -1;
    }

    mrb = mrb_open();
    if (mrb == NULL) {
        fprintf(stderr, "Error: mrb_open() failed.\n");
        return -1;
    }

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

    parser = mrb_parse_file(mrb, fp, ctx);
    if (parser->nerr > 0) {
        fprintf(stderr, "Error: line %d; %s\n", parser->error_buffer[0].lineno, parser->error_buffer[0].message);
        mrb_close(mrb);
        fclose(fp);
        return -1;
    }

    n = mrb_generate_code(mrb, parser);

    r = 0;
    v = mrb_run(mrb, mrb_proc_new(mrb, mrb->irep[n]), mrb_top_self(mrb));
    if (mrb->exc) {
        p(mrb, mrb_obj_value(mrb->exc));
        r = 1;
    } else {
        printf(">> ");
        p(mrb, v);
    }

    mrb_parser_free(parser);
    mrbc_context_free(mrb, ctx);
    fclose(fp);
    mrb_close(mrb);

    return r;
}
