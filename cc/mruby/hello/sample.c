#include <stdio.h>
#include <string.h>

#include "mruby.h"
#include "mruby/proc.h"
#include "mruby/compile.h"
#include "mruby/array.h"

int main(int argc, char **argv)
{
    mrb_state                *mrb;
    struct mrb_parser_state  *p;
    int                      n;
    FILE                     *fp;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return -1;
    }

    mrb = mrb_open();
    if (mrb == NULL) {
        fprintf(stderr, "Error: mrb_open() failed.\n");
        return -1;
    }

    fp = fopen(argv[1], "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error: Cannot open file. filename=[%s]\n", argv[1]);
        return -1;
    }

    p = mrb_parser_new(mrb);

    mrb_parser_filename(p, argv[1]);
    p->f = fp;
    mrb_parser_parse(p);
    if (!p || !p->tree || p->nerr) {
        fclose(fp);
        return -1;
    }

    n = mrb_generate_code(mrb, p->tree);

    mrb_pool_close(p->pool);

    mrb_run(mrb, mrb_proc_new(mrb, mrb->irep[n]), mrb_top_self(mrb));

    fclose(fp);

    return 0;
}

