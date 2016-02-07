#include <stdint.h>
#include <stdlib.h>	// malloc
#include <stdio.h>	// fopen

#include <time.h>
#ifndef CLOCK_MONOTONIC_RAW	// fix for sles11
	#define CLOCK_MONOTONIC_RAW 4
#endif

#ifdef USE_TSC	
	#define FILE_NAME "buffer-tsc.txt"
#elif USE_MONO
	#define FILE_NAME "buffer-mono.txt"
#elif USE_RAW
	#define FILE_NAME "buffer-raw.txt"
#else
	#define FILE_NAME "buffer-none.txt"
#endif

static const int CPU_MHZ = 2500;

static uint64_t start;

static uint64_t* buffer;
static uint32_t bufferPos;
static uint64_t* funcIdBuffer;
static uint32_t funcIdBufferPos;


__attribute__ ((constructor))
void initRuntime() {
	buffer = (uint64_t*) malloc(100*1000*1000 * sizeof(uint64_t*));
	bufferPos = 0;
	funcIdBuffer = (uint64_t*) malloc(100*1000*1000 * sizeof(uint64_t*));
	funcIdBufferPos = 0;
}

__attribute__ ((destructor))
void finiRuntime() {
#ifndef SKIP_BUFFER
	FILE* file = fopen(FILE_NAME, "w");
	if (file) {
		int i;
		for (i=0; i<bufferPos; i++) {
			fprintf(file, "%lu\n", buffer[i]);
		}
		fclose(file);
	}		
#endif
}

#ifdef USE_MONO
__attribute__((always_inline))
inline uint64_t getTimeClock() {
	struct timespec tspec;
	clock_gettime(CLOCK_MONOTONIC, &tspec);
	return (uint64_t) tspec.tv_sec * 1000000000 + tspec.tv_nsec;
}
#endif

#ifdef USE_RAW
__attribute__((always_inline))
inline uint64_t getTimeClockRaw() {
	struct timespec tspec;
	clock_gettime(CLOCK_MONOTONIC_RAW, &tspec);
	return (uint64_t) tspec.tv_sec * 1000000000 + tspec.tv_nsec;
}
#endif

#ifdef USE_TSC
__attribute__ ((always_inline))
inline uint64_t getTimeTSC() {
	uint32_t low = 0;
	uint32_t high = 0;
	asm volatile ("rdtscp" : "=a" (low), "=d" (high));

	uint64_t cycles = ((uint64_t) high << 32) | low;
	return cycles * 1000 / CPU_MHZ;	
}
#endif


inline uint64_t getTime() {
#ifdef USE_TSC	
	return getTimeTSC();
#elif USE_MONO
	return getTimeClock();
#elif USE_RAW
	return getTimeClockRaw();
#else
	return 0;
#endif 
	
}

void __cyg_profile_func_enter(void *func_ptr, void *call_site) {
	start = getTime();
}

void __cyg_profile_func_exit(void *func_ptr, void *call_site) {

	uint64_t end = getTime();
	
	uint64_t diff = end - start;
	buffer[bufferPos++] = diff;

	uint64_t funcId = (uint64_t) func_ptr;
	funcIdBuffer[funcIdBufferPos++] = funcId;
}



