#include <stdio.h>
#include <wand/magick_wand.h>

int main(int argc, char *argv[])
{
	MagickWand *wand = NULL;
	int width;
	int height;
	MagickBooleanType ret;
	char *description;
	ExceptionType excep;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s file\n", argv[0]);
		return 1;
	}

	MagickWandGenesis();

	wand = NewMagickWand();
	if (wand == NULL) {
		description = MagickGetException(wand, &excep);
		fprintf(stderr, "%s; %s\n", "NewMagickWand() failed", description);
		MagickRelinquishMemory(description);
		return 1;
	}

	ret = MagickReadImage(wand, argv[1]);
	if (ret != MagickTrue) {
		description = MagickGetException(wand, &excep);
		fprintf(stderr, "%s; %s\n", "MagickReadImage() failed", description);
		MagickRelinquishMemory(description);
		return 1;
	}

	width = MagickGetImageWidth(wand);
	height = MagickGetImageHeight(wand);

	printf("width: %d\n", width);
	printf("height: %d\n", height);

	if (wand != NULL) {
		DestroyMagickWand(wand);
	}

	MagickWandTerminus();

	return 0;
}

