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

	size_t num = 0;
	char **property_name = MagickGetImageProperties(wand, "*", &num);
	printf("number of property: %ld\n", num);

	int i;
	for (i = 0; i < num; i++) {
		printf("name: %s\n", property_name[i]);
	}

	if (wand != NULL) {
		DestroyMagickWand(wand);
	}

	MagickWandTerminus();

	return 0;
}

