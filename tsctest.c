

#define NUM_ITERATIONS 1000*1000*100


int main() {
	int i;
	for (i=0; i<NUM_ITERATIONS; i++) {

		unsigned int low = 0;
		unsigned int high = 0;
		asm volatile ("rdtscp" : "=a" (low), "=d" (high));

		unsigned long int counter = ((unsigned long int) high << 32) + low;
	
	}
	return 0;
}
