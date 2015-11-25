#define NUM_ITERATIONS 1000*1000*30

void foo() {}

int main() {
	for (int i=0; i<NUM_ITERATIONS; i++) {
		foo();
	}
	return 0;
}
