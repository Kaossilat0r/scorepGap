
#define NUM_ITERATIONS 1000*1000*100

#ifdef META_MEASURE
#include "target-measure.h"
#endif

void foo() {}

int main() {

#ifdef META_MEASURE
	startMeasurement();
#endif

	int i;
	for (i=0; i<NUM_ITERATIONS; i++) {
		foo();
	}

#ifdef META_MEASURE
	stopMeasurement();
	printResult();
#endif

	return 0;
}
