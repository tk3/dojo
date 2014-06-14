#include <stdio.h>
#include "httpd.h"
#include "apr_pools.h"
#include "apr_tables.h"

apr_array_header_t *parse_path(apr_pool_t *pool, const char *path);

int main()
{
    apr_pool_t *pool;

    apr_initialize();

    apr_pool_create(&pool, NULL);

    parse_path(pool, "/");
    parse_path(pool, "/aaa/bbb/ccc");

    apr_pool_destroy(pool);

    apr_terminate();

    return 0;
}

apr_array_header_t *parse_path(apr_pool_t *pool, const char *path)
{
    apr_array_header_t *arr;
    const char *val;

    arr = apr_array_make(pool, 8, sizeof(char *));

    while (*path && (val = ap_getword(pool, &path, '/'))){
        printf(">> [%s]\n", val);
    }

    return arr;
}

