#include <stdio.h>
#include <stdlib.h>
#include <gnu/libc-version.h>

#include <time.h>

#ifndef CLOCK_MONOTONIC_RAW
    #define CLOCK_MONOTONIC_RAW 4
#endif

void printRes(const struct timespec result) {
	printf("resolution is %ld.%09ld seconds.\n", result.tv_sec, result.tv_nsec);
}

int main(int argc, char *argv[]) {
	printf("GNU libc version: %s\n", gnu_get_libc_version());
	
	struct timespec resolution;

	clock_getres(CLOCK_MONOTONIC, &resolution);
	printf("CLOCK_MONOTONIC ");
	printRes(resolution);
	
	clock_getres(CLOCK_MONOTONIC_RAW, &resolution);
	printf("CLOCK_MONOTONIC_RAW ");
	printRes(resolution);

	exit(EXIT_SUCCESS);
}
