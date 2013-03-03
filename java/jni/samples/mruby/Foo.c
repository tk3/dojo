#include "Foo.h"

#include "mruby.h"
#include "mruby/proc.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/compile.h"
#include "mruby/dump.h"
#include "mruby/compile.h"

#include <stdio.h>

JNIEXPORT void JNICALL Java_Foo_run(JNIEnv *jenv, jclass clazz, jobjectArray argv)
{
    static char mrb_src[] = \
      "ARGV.each do |a|\n"  \
      "    puts \"#{a}, #{a.class}\"\n"  \
      "end\n";
    int len;
    int i;
    jstring s;
    const char *val;

    mrb_state *mrb;
    mrbc_context *ctx;
    mrb_value mrb_argv;
    mrb_value ret;
    mrb_value output;

    mrb = mrb_open();
    ctx = mrbc_context_new(mrb);

    mrb_argv = mrb_ary_new(mrb);

    len = (*jenv)->GetArrayLength(jenv, argv);

    for (i = 0; i < len; i++) {
        s = (*jenv)->GetObjectArrayElement(jenv, argv, i);
        val = (*jenv)->GetStringUTFChars(jenv, s, 0);

        mrb_ary_push(mrb, mrb_argv, mrb_str_new(mrb, val, strlen(val)));

        (*jenv)->ReleaseStringUTFChars(jenv, s, val);
    }

    mrb_define_global_const(mrb, "ARGV", mrb_argv);

    ret = mrb_load_string(mrb, mrb_src);

    if (mrb->exc) {
        if (!mrb_undef_p(ret)) {
            output = mrb_obj_value(mrb->exc);

            output = mrb_funcall(mrb, output, "inspect", 0);
            fwrite(RSTRING_PTR(output), RSTRING_LEN(output), 1, stdout);
        }
    }

    if (ctx != NULL) {
        mrbc_context_free(mrb, ctx);
    }
    if (mrb != NULL) {
        mrb_close(mrb);
    }

    return;
}
