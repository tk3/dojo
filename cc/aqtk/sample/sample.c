#include <stdio.h>
#include "AquesTalk2.h"

int main(int argc, char *argv[])
{
	int size;
	char message[128];
	unsigned char *wav;
	int rate_of_speech = 100;

	if (fgets(message, sizeof(message) - 1, stdin) == 0) {
		return 0;
	}

	wav = AquesTalk2_Synthe_Utf8(message, rate_of_speech, &size, NULL);
	if (wav == 0) {
		fprintf(stderr, "error: code=%d\n", size);
		return -1;
	}

	fwrite(wav, 1, size, stdout);

	AquesTalk2_FreeWave(wav);
 
	return 0;
}
