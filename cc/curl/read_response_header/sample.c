#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curl/curl.h"

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);

int main(int argc, char **argv)
{
	CURL *curl;
	CURLcode ret;

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
	if (curl == NULL) {
		fprintf(stderr, "Error: curl_easy_init() failed\n");
		return 1;
	}

	curl_easy_setopt(curl, CURLOPT_URL, "http://localhost/");
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
	curl_easy_setopt(curl, CURLOPT_HEADERDATA, NULL);
	curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, write_callback);

	ret = curl_easy_perform(curl);
	if (ret != CURLE_OK) {
		fprintf(stderr, "Error: curl_easy_perform() failed: %s\n", curl_easy_strerror(ret));
		return 1;
	}

	curl_easy_cleanup(curl);

	curl_global_cleanup();

	return 0;
}

size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	char *p;
	size_t append_size = size * nmemb;

	printf("header: [%s]\n", ptr);

	return size * nmemb;
}

