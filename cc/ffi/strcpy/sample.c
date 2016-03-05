#include <ffi.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int test_call_strcpy(void);
int invoke_strcpy(void *func);

int main(int argc, char **argv)
{
    test_call_strcpy();

    return 0;
}

int test_call_strcpy(void)
{
    void *handle;
    char *dl_error;
    void *func;

    handle = dlopen("libc.so.6", RTLD_LAZY);
    if (handle == NULL) {
        fprintf(stderr, "Error: dlopen() failed. [%s]\n", dlerror());
        return -1;
    }
    dlerror();

    func = dlsym(handle, "strcpy");

    dl_error = dlerror();
    if (dl_error != NULL) {
        fprintf(stderr, "Error: dlopen() failed. [%s]\n", dl_error);
        return -1;
    }

    invoke_strcpy(func);

    dlclose(handle);

    return 0;
}

int invoke_strcpy(void *func)
{
    ffi_cif    cif;
    ffi_type   *arg_types[2];
    void       *arg_values[2];
    ffi_status status;
    ffi_arg    result;
    char       *arg1;
    char       *arg2;

    char       arg1_val[16] = "";
    char       arg2_val[]   = "Hello world";

    arg_types[0] = &ffi_type_pointer;
    arg_types[1] = &ffi_type_pointer;

    status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_pointer, arg_types);
    if (status != FFI_OK) {
        fprintf(stderr, "Error: ffi_prep_cif() failed\n");
        return -1;
    }

    arg1 = arg1_val;
    arg2 = arg2_val;

    arg_values[0] = &arg1;
    arg_values[1] = &arg2;

    ffi_call(&cif, FFI_FN(func), &result, arg_values);

    printf("return = [%s]\n",  (char *)result);
    printf("  arg1 = [%s]\n",  arg1);

    return 0;
}

