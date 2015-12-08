EXE=target.exe.$(HOSTNAME)

all: scorep scorep-run

scorep:
	scorep gcc -std=c99 target.c -o $(EXE)

scorep-run:
	taskset -c 5 time ./$(EXE)

testraw:
	gcc -DUSED_CLOCK=CLOCK_MONOTONIC_RAW -lrt clocktest.c -o testraw.$(HOSTNAME)
	taskset -c 5 time ./testraw.$(HOSTNAME)

test:
	gcc -DUSED_CLOCK=CLOCK_MONOTONIC     -lrt clocktest.c -o test.$(HOSTNAME)
	taskset -c 5 time ./test.$(HOSTNAME)
	
tsc:
	gcc tsctest.c -o testtsc.$(HOSTNAME)
	taskset -c 5 time ./testtsc.$(HOSTNAME)

version:
	gcc -lrt glibc-version.c -o glibc-version
	./glibc-version

clean:
	rm -rf scorep-* target.exe.* test.* testtsc.* testraw.* glibc-version
