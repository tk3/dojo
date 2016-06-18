#include <stdio.h>
#include <magick/MagickCore.h>

int main(int argc,char **argv)
{
	const char *version;
	size_t ver;

	version = GetMagickVersion(NULL);
	GetMagickVersion(&ver);

	printf("Version: %s\n", version);
	printf("Ver: %lx\n", ver);

	return 0;
}

