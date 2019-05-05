#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ffi.h"

struct Foo {
  int x;
  int y;
  int z;
  char name[16];
};

struct Foo *foo_new(void);

int main(int argc, char **argv)
{
    ffi_cif cif;
    ffi_status status;
    ffi_arg result;

    status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 0, &ffi_type_pointer, NULL);
    if (status != FFI_OK) {
        fprintf(stderr, "Error: ffi_prep_cif() failed\n");
        return -1;
    }

    ffi_call(&cif, FFI_FN(foo_new), &result, NULL);

    printf("return = [%p]\n", (void *)result);

    return 0;
}

void test_struct_foo(void)
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

struct Foo *foo_new(void)
{
	struct Foo *f;

	f = (struct Foo *)malloc(sizeof(struct Foo));
	f->x = 1;
	f->y = 2;
	f->z = 3;
	strcpy(f->name, "sample");

	return f;
}
