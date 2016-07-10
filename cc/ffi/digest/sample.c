#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <ffi.h>

#include <openssl/md5.h>
#include <openssl/sha.h>

int test_md5(char *v);
int test_sha1(char *v);

int main(int argc, char *argv[])
{
	if (argc < 2) {
		return 0;
	}

	test_md5(argv[1]);
	test_sha1(argv[1]);

	return 0;
}

int test_md5(char *v)
{
	MD5_CTX ctx;

	void *handle;
	void *func_init;
	void *func_update;
	void *func_final;
	char *error;

	handle = dlopen("libcrypto.so", RTLD_LAZY);
	if (handle == NULL) {
		return 0;
	}
	dlerror();

	func_init = dlsym(handle, "MD5_Init");
	if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "%s\n", error);
		return 0;
	}

	func_update = dlsym(handle, "MD5_Update");
	func_final = dlsym(handle, "MD5_Final");

	{
		ffi_cif cif;
		ffi_type *args[1];
		void *values[1];
		int rc;
		MD5_CTX *s;

		args[0] = &ffi_type_pointer;

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 1, &ffi_type_uint, args) != FFI_OK) {
			return 0;
		}

		s = &ctx;

		values[0] = &s;

		ffi_call(&cif, FFI_FN(func_init), &rc, values);
	}

	{
		ffi_cif cif;
		ffi_type *args[3];
		void *values[3];
		int rc;

		MD5_CTX *s;
		char *d;
		size_t l;

		args[0] = &ffi_type_pointer;
		args[1] = &ffi_type_pointer;
		args[2] = &ffi_type_uint64;

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 3, &ffi_type_uint, args) != FFI_OK) {
			return 0;
		}

		s = &ctx;
		d = v;
		l = strlen(v);

		values[0] = &s;
		values[1] = &d;
		values[2] = &l;

		ffi_call(&cif, FFI_FN(func_update), &rc, values);
	}

	unsigned char md[16];
	{
		ffi_cif cif;
		ffi_type *args[2];
		void *values[2];
		int rc;

		MD5_CTX *s;
		unsigned char *m;

		args[0] = &ffi_type_pointer;
		args[1] = &ffi_type_pointer;

		if (ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_uint, args) != FFI_OK) {
			return 0;
		}

		s = &ctx;
		m = md;

		values[0] = &m;
		values[1] = &s;

		ffi_call(&cif, FFI_FN(func_final), &rc, values);
	}

	{
		int i;
		for (i = 0; i < sizeof(md); i++) {
			printf("%02x", md[i]);
		}
		puts("");
	}

	dlclose(handle);

	return 0;
}

int test_sha1(char *v)
{
	SHA_CTX ctx;

	void *handle;
	void *func_init;
	void *func_update;
	void *func_final;
	char *error;

	handle = dlopen("libcrypto.so", RTLD_LAZY);
	if (handle == NULL) {
		return 0;
	}
	dlerror();

	func_init = dlsym(handle, "SHA_Init");
	if ((error = dlerror()) != NULL)  {
		fprintf(stderr, "%s\n", error);
		return 0;
	}

	func_update = dlsym(handle, "SHA_Update");
	func_final = dlsym(handle, "SHA_Final");

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

		s = &ctx;

		values[0] = &s;

		ffi_call(&cif, FFI_FN(func_init), &rc, values);
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

		s = &ctx;
		d = v;
		l = strlen(v);

		values[0] = &s;
		values[1] = &d;
		values[2] = &l;

		ffi_call(&cif, FFI_FN(func_update), &rc, values);
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

		s = &ctx;
		m = md;

		values[0] = &m;
		values[1] = &s;

		ffi_call(&cif, FFI_FN(func_final), &rc, values);
	}

	{
		int i;
		for (i = 0; i < sizeof(md); i++) {
			printf("%02x", md[i]);
		}
		puts("");
	}

	dlclose(handle);

	return 0;
}

