#include <stdio.h>
#include <wand/magick_wand.h>

int main(int argc, char *argv[])
{
	printf("Copyright: %s\n", MagickGetCopyright());
	printf("PackageName: %s\n", MagickGetPackageName());
	printf("ReleaseDate: %s\n", MagickGetReleaseDate());
	printf("Version: %s\n", MagickGetVersion(NULL));

	return 0;
}

