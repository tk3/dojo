#include <stdio.h>
#include <ClearSilver.h>

NEOERR *render_cb(void *data, char *s)
{
    printf("%s", s);
    return STATUS_OK;
}

int main()
{
    HDF *hdf;
    CSPARSE *cs;

    hdf_init(&hdf);
    hdf_set_value(hdf, "name", "hoge");

    cs_init(&cs, hdf);
    cs_parse_file(cs, "template.cs");
    cs_render(cs, NULL, render_cb);

    cs_destroy(&cs);
    hdf_destroy(&hdf);

    return 0;
}

