#include <stdio.h>
#include "apr_pools.h"
#include "apr_tables.h"

int main()
{
    apr_pool_t *pool;
    apr_array_header_t *arr;
    int *val;
    int i;

    apr_initialize();

    apr_pool_create(&pool, NULL);

    arr = apr_array_make(pool, 8, sizeof(int));

    val = apr_array_push(arr);
    *val = 10;

    val = apr_array_push(arr);
    *val = 20;

    val = apr_array_push(arr);
    *val = 30;

    for (i = 0; i < arr->nelts; i++) {
        *val = APR_ARRAY_IDX(arr, i, int);
        printf("%d) ... %d\n", i, *val);
    }

    apr_pool_destroy(pool);

    apr_terminate();

    return 0;
}

