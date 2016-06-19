#include <stdio.h>
#include <wand/magick_wand.h>

int main(int argc, char *argv[])
{
	MagickWand *wand = NULL;
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

	printf("Format: %s\n", MagickGetImageFormat(wand));
	printf("Filename: %s\n", MagickGetImageFilename(wand));
	printf("Compression Quality: %ld\n", MagickGetCompressionQuality(wand));
	printf("Signature: %s\n", MagickGetImageSignature(wand));
	printf("Width: %ld\n", MagickGetImageWidth(wand));
	printf("Height: %ld\n", MagickGetImageHeight(wand));

	if (wand != NULL) {
		DestroyMagickWand(wand);
	}

	MagickWandTerminus();

	return 0;
}

