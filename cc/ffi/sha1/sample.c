#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <ffi.h>

#include <openssl/sha.h>

int main(int argc, char *argv[])
{
	SHA_CTX sha;

	if (argc < 2) {
		return 0;
	}

	{
		ffi_cif cif;
		ffi_type *args[1];
		void *values[1];
		int rc;
		SHA_CTX *s;

		args[0] = &ffi_type_pointer;

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_uint, args) != FFI_OK) {
			return 0;
		}

		s = &sha;

		values[0] = &s;

		ffi_call(&cif, FFI_FN(SHA_Init), &rc, values);
	}

	{
		ffi_cif cif;
		ffi_type *args[3];
		void *values[3];
		int rc;

		SHA_CTX *s;
		char *d;
		size_t l;

		args[0] = &ffi_type_pointer;
		args[1] = &ffi_type_pointer;
		args[2] = &ffi_type_uint64;

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 3, &ffi_type_uint, args) != FFI_OK) {
			return 0;
		}

		s = &sha;
		d = argv[1];
		l = strlen(argv[1]);

		values[0] = &s;
		values[1] = &d;
		values[2] = &l;

		ffi_call(&cif, FFI_FN(SHA_Update), &rc, values);
	}

	unsigned char md[20];
	{
		ffi_cif cif;
		ffi_type *args[2];
		void *values[2];
		int rc;

		SHA_CTX *s;
		unsigned char *m;

		args[0] = &ffi_type_pointer;
		args[1] = &ffi_type_pointer;

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_uint, args) != FFI_OK) {
			return 0;
		}

		s = &sha;
		m = md;

		values[0] = &m;
		values[1] = &s;

		ffi_call(&cif, FFI_FN(SHA_Final), &rc, values);
	}

	{
		int i;
		for (i = 0; i < 20; i++) {
			printf("%02x", md[i]);
		}
		puts("");
	}

	return 0;
}

