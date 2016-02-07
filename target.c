
#define NUM_ITERATIONS 1000*1000*1000

#ifdef META_MEASURE
#include <stdint.h>
#include <stdio.h>

extern uint64_t getMetaTime() {
	uint32_t low = 0;
	uint32_t high = 0;
	asm volatile ("rdtscp" : "=a" (low), "=d" (high));

	uint64_t cycles = ((uint64_t) high << 32) | low;
	return cycles * 1000 / 2500;
}
#endif

void foo() {}

int main() {

#ifdef META_MEASURE
	uint64_t start = getMetaTime();
#endif

	int i;
	for (i=0; i<NUM_ITERATIONS; i++) {
		foo();
	}

#ifdef META_MEASURE
	uint64_t end = getMetaTime();
	double diff = (double) (end - start) / (1000*1000*1000);
	printf("%f\n", diff);
#endif

	return 0;
}
