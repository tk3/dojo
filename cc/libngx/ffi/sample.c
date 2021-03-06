#include <stdio.h>

#include <ffi.h>

#include <ngx_sha1.h>
#include <ngx_md5.h>
#include <ngx_times.h>
#if 0
#endif

ngx_module_t  ngx_core_module = {
    NGX_MODULE_V1,
    NULL,                  /* module context */
    NULL,                  /* module directives */
    NGX_CORE_MODULE,       /* module type */
    NULL,                  /* init master */
    NULL,                  /* init module */
    NULL,                  /* init process */
    NULL,                  /* init thread */
    NULL,                  /* exit thread */
    NULL,                  /* exit process */
    NULL,                  /* exit master */
    NGX_MODULE_V1_PADDING
};

// ./nginx-1.11.1/src/core/nginx.c
char ** ngx_set_environment(ngx_cycle_t *cycle, ngx_uint_t *last);
ngx_cpuset_t * ngx_get_cpu_affinity(ngx_uint_t n);
ngx_pid_t ngx_exec_new_binary(ngx_cycle_t *cycle, char *const *argv);

static void sample_time();
static void sample_sha1();
static void sample_md5();
static void sample_base64();

int main(int argc, char **argv)
{
    ngx_time_init();

	sample_time();

#if 0
	sample_sha1();
	sample_md5();
	sample_base64();
#endif

    return 0;
}

static void sample_time()
{
	u_char *p;
	u_char buf[64];
    ffi_status status;
    ffi_cif cif;
    ffi_type *arg_types[2];

    arg_types[0] = &ffi_type_pointer;
    arg_types[1] = &ffi_type_uint64;  // size_t

    status = ffi_prep_cif(&cif, FFI_DEFAULT_ABI, 2, &ffi_type_pointer, arg_types);
    if (status != FFI_OK) {
       fprintf(stderr, "Error: ffi_prep_cif() failed\n");
       return -1;
	}


	{
    	void *arg_values[2];
		char buf[64];
		char *v;
		time_t tm;
		char *ret;

		v = &buf;
		tm = time(NULL);

    	arg_values[0] = &v;
    	arg_values[1] = &tm;

    	ffi_call(&cif, FFI_FN(ngx_http_cookie_time), &ret, arg_values);

		printf("ngx_http_cookie_time = %.*s\n", ret - buf, buf);
	}

	//p = ngx_http_cookie_time(buf, time(NULL));

#if 0
	puts("sample_time --------");
	printf("sizeof(time_t) = %d\n", sizeof(time_t));
	printf("ngx_time = %ld\n", ngx_time());
	printf("ngx_http_cookie_time = %.*s\n", p - buf, buf);
#endif

	return;
}

#if 0
static void sample_time()
{
	u_char *p;
	u_char buf[64];

	p = ngx_http_cookie_time(buf, time(NULL));

	puts("sample_time --------");
	printf("sizeof(time_t) = %d\n", sizeof(time_t));
	printf("ngx_time = %ld\n", ngx_time());
	printf("ngx_http_cookie_time = %.*s\n", p - buf, buf);

	return;
}

static void sample_sha1()
{
	char key[] = "test_string";
	ngx_sha1_t sha1;
	u_char digest[20];
	int i;

    ngx_sha1_init(&sha1);
    ngx_sha1_update(&sha1, key, ngx_strlen(key));
    ngx_sha1_final(digest, &sha1);

	puts("sample_sha1 --------");
	printf("string = [%s]\n", key);
	for (i = 0; i < sizeof(digest); i++) {
		printf("%02x", digest[i]);
	}
	printf("\n");

	return;
}

static void sample_md5()
{
	char key[] = "test_string";
	ngx_md5_t md5;
	u_char digest[16];
	int i;

    ngx_md5_init(&md5);
    ngx_md5_update(&md5, key, ngx_strlen(key));
    ngx_md5_final(digest, &md5);

	puts("sample_md5 --------");
	printf("string = [%s]\n", key);
	for (i = 0; i < sizeof(digest); i++) {
		printf("%02x", digest[i]);
	}
	printf("\n");

	return;
}

static void sample_base64()
{
	ngx_str_t src = ngx_string("test_string");
	ngx_str_t base64;

    base64.len = ngx_base64_encoded_length(src.len);
    base64.data = malloc(base64.len);
    if (base64.data == NULL) {
		fprintf(stderr, "Error: malloc() failed.");
        return;
    }

	ngx_encode_base64(&base64, &src);

	puts("sample_base64 --------");
	printf("string = [%.*s]\n", src.len, src.data);
	printf("base64 = [%.*s]\n", base64.len, base64.data);

	return;
}
#endif

char ** ngx_set_environment(ngx_cycle_t *cycle, ngx_uint_t *last)
{
	return NULL;
}

ngx_cpuset_t * ngx_get_cpu_affinity(ngx_uint_t n)
{
	return NULL;
}

ngx_pid_t ngx_exec_new_binary(ngx_cycle_t *cycle, char *const *argv)
{
	return NGX_INVALID_PID;
}

