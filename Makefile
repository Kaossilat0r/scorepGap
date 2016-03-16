EXE=target.exe.$(HOSTNAME)

all: scorep scorep-run

scorep:
	scorep gcc target.c -o $(EXE)

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

MEASURE_FLAGS=-finstrument-functions -finstrument-functions-exclude-function-list=main -DMETA_MEASURE
LIBMEASURE_FLAGS=-fPIC -shared -Wall -O3 -DSKIP_BUFFER
libmeasure:
	gcc $(LIBMEASURE_FLAGS) -DUSE_TSC       measure.c -o libmeasure-tsc.so
	gcc $(LIBMEASURE_FLAGS) -DUSE_MONO -lrt measure.c -o libmeasure-mono.so
	gcc $(LIBMEASURE_FLAGS) -DUSE_RAW  -lrt measure.c -o libmeasure-raw.so
	gcc $(LIBMEASURE_FLAGS) -lrt measure.c -o libmeasure-none.so
	gcc $(MEASURE_FLAGS) libmeasure-tsc.so  target.c -o measure-tsc.exe
	gcc $(MEASURE_FLAGS) libmeasure-mono.so target.c -o measure-mono.exe
	gcc $(MEASURE_FLAGS) libmeasure-raw.so  target.c -o measure-raw.exe
	gcc $(MEASURE_FLAGS) libmeasure-none.so target.c -o measure-none.exe
	
	scorep  gcc  $(MEASURE_FLAGS) target.c -o measure-scorep.exe

target:
	gcc -DMETA_MEASURE target.c -o target.exe
	gcc -DMETA_MEASURE target-rec.c -o target-rec.exe

clean:
	rm -rf scorep-* target.exe* test.* testtsc.* testraw.* 
	rm -rf libmeasure-*.so measure-*.exe glibc-version
