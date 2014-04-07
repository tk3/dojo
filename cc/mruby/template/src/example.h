#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <mruby.h>
#include <stdio.h>

void mrb_c_extension_example_gem_init(mrb_state* mrb);
void mrb_c_extension_example_gem_final(mrb_state* mrb);

#endif
