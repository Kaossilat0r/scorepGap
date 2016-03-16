#ifndef TARGET_METAMEASURE_H_
#define TARGET_METAMEASURE_H_

#include <stdint.h>
#include <stdio.h>

static uint64_t startCycles, stopCycles;
const uint64_t cpuMHz = 2500;

__attribute__ ((no_instrument_function))
void startMeasurement() {
	uint32_t low = 0;
	uint32_t high = 0;
	asm volatile ("rdtscp" : "=a" (low), "=d" (high));

	startCycles = ((uint64_t) high << 32) | low;
}

__attribute__ ((no_instrument_function))
void stopMeasurement() {
	uint32_t low = 0;
	uint32_t high = 0;
	asm volatile ("rdtscp" : "=a" (low), "=d" (high));

	stopCycles = ((uint64_t) high << 32) | low;
}

__attribute__ ((no_instrument_function))
void printResult() {
	uint64_t cycles = stopCycles - startCycles;
	uint64_t nanoSeconds = cycles * 1000 / cpuMHz; 
	double seconds = (double) nanoSeconds / (double) (1000*1000*1000);	
	fprintf(stderr, "%f\n", seconds);
}

#endif	// TARGET_METAMEASURE_H_
