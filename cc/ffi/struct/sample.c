#include <stdio.h>
#include "ffi.h"

struct Foo {
  int x;
  int y;
};

int foo_add(struct Foo foo);

int main(int argc, char **argv)
{
    ffi_cif cif;
    ffi_type foo_struct_type = {};
    ffi_type *foo_member_types[2 + 1];
    ffi_type *arg_types[1];
    ffi_status status;
    void *arg_values[1];
    ffi_arg result;

    struct Foo f = {};

    foo_struct_type.size = 0;
    foo_struct_type.alignment = 0;
    foo_struct_type.type = FFI_TYPE_STRUCT;
	foo_struct_type.elements = foo_member_types;

    foo_member_types[0] = &ffi_type_sint32;
    foo_member_types[1] = &ffi_type_sint32;
    foo_member_types[2] = NULL;

    arg_types[0] = &foo_struct_type;

    status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_sint32, arg_types);
    if (status != FFI_OK) {
        fprintf(stderr, "Error: ffi_prep_cif() failed\n");
        return -1;
    }

	f.x = 11;
	f.y = 17;

    arg_values[0] = &f;

    ffi_call(&cif, FFI_FN(foo_add), &result, arg_values);

    printf("return = [%d]\n", (int)result);

    return 0;
}

int foo_add(struct Foo f)
{
	return f.x + f.y;
}
