#include <stdio.h>
#include "ffi.h"

int add(int x, int y);

int main(int argc, char **argv)
{
    ffi_cif cif;
    ffi_type *arg_types[2];
    ffi_status status;
    int arg1;
    int arg2;
    void *arg_values[2];
    ffi_arg result;

    arg_types[0] = &ffi_type_sint32;
    arg_types[1] = &ffi_type_sint32;

    status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_sint32, arg_types);
    if (status != FFI_OK) {
        fprintf(stderr, "Error: ffi_prep_cif() failed\n");
        return -1;
    }

    arg1 = 10;
    arg2 = 20;

    arg_values[0] = &arg1;
    arg_values[1] = &arg2;

    ffi_call(&cif, FFI_FN(add), &result, arg_values);

    printf("return = [%d]\n", (int)result);

    return 0;
}

int add(int x, int y)
{
    return x + y;
}
