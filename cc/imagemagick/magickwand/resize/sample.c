#include <stdio.h>
#include <wand/magick_wand.h>

int main(int argc, char *argv[])
{
	MagickWand *wand = NULL;
	int original_width;
	int original_height;
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
		fprintf(stderr, "%s %s %lu %s\n", GetMagickModule(), description);
		MagickRelinquishMemory(description);
		return 1;
	}

	ret = MagickReadImage(wand, argv[1]);
	if (ret != MagickTrue) {
		description = MagickGetException(wand, &excep);
		fprintf(stderr, "%s %s %lu %s\n", GetMagickModule(), description);
		MagickRelinquishMemory(description);
		return 1;
	}

	original_width = MagickGetImageWidth(wand);
	original_height = MagickGetImageHeight(wand);

	width = original_width / 2 < 1 ? 1 : original_width / 2;
	height = original_height / 2 < 1 ? 1 : original_height / 2;

	MagickResizeImage(wand, width, height, LanczosFilter, 1);

	MagickSetImageCompressionQuality(wand, 95);

	MagickWriteImage(wand, "logo_resize.jpg");

	if (wand != NULL) {
		DestroyMagickWand(wand);
	}

	MagickWandTerminus();

	return 0;
}

