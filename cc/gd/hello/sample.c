#include <stdio.h>
#include "gd.h"

int main(int argc, char **argv)
{
    gdImagePtr image;

    //image = gdImageCreate(100, 200);
    FILE *fin = fopen("in.jpg", "r");
    //image = gdImageCreateFromPng(fin);
    //image = gdImageCreateFromJpeg(fin);
    //fclose(fin);
    image = gdImageCreateFromWebp(fin);

    //FILE *fout = fopen("out.png", "w");
    //gdImagePng(image, fout);
    //FILE *fout = fopen("out.jpg", "w");
    //gdImageJpeg(image, fout, 100);
    //fclose(fout);

    gdImageDestroy(image);

    return 0;
}
