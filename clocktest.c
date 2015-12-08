
#include <time.h>

#define NUM_ITERATIONS 1000*1000*100

#ifndef CLOCK_MONOTONIC_RAW
	#define CLOCK_MONOTONIC_RAW 4
#endif

#ifndef USED_CLOCK
	#define USED_CLOCK CLOCK_MONOTONIC
#endif


int main() {
	int i;
	for (i=0; i<NUM_ITERATIONS; i++) {
		struct timespec startTime;
		clock_gettime(USED_CLOCK, &startTime);
	
	}
	return 0;
}
