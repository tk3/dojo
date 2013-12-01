#include <stdio.h>
#include "ClearSilver.h"

/**
NEOERR* hdf_set_attr (HDF *hdf, const char *name, const char *key,
                      const char *value);
NEOERR* hdf_set_value (HDF *hdf, const char *name, const char *value);
NEOERR* hdf_set_valuef (HDF *hdf, const char *fmt, ...)
                        ATTRIBUTE_PRINTF(2,3);
NEOERR* hdf_set_valuevf (HDF *hdf, const char *fmt, va_list ap);
NEOERR* hdf_set_int_value (HDF *hdf, const char *name, int value);
NEOERR* hdf_set_buf (HDF *hdf, const char *name, char *value);
**/

int main()
{
    HDF *hdf;

    hdf_init(&hdf);

    hdf_set_value(hdf, "name", "hoge");
    hdf_set_attr(hdf, "name", "key_attr", "fff_attr");

    hdf_set_attr(hdf, "age", "attr", "after");
    hdf_set_int_value(hdf, "age", 33);

    // children
    {
        HDF *child1 = hdf_obj_child(hdf);

        hdf_set_value(child1, "name", "child node 01");
        hdf_set_int_value(child1, "age", 24);

        child1->top = hdf;

        HDF *child2 = hdf_obj_next(child1);

        hdf_set_value(child2, "name", "child node 02");
        hdf_set_int_value(child2, "age", 22);

        //child1->next = child2;
        //child1->top = hdf;

        // two levels
        {
            HDF *child3 = hdf_obj_child(child1);

            hdf_set_value(child3, "name", "child node 03");
            hdf_set_int_value(child3, "age", 20);

            child1->top = child3;
        }
    }

    hdf_set_value(hdf, "group.alpha", "OK");
    hdf_set_value(hdf, "group.bravo", "OK");
    hdf_set_value(hdf, "group.charlie", "NG");

    hdf_dump(hdf, "sample");

    hdf_destroy(&hdf);

    return 0;
}

