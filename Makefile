EXE=target.exe.$(HOSTNAME)

all: build run

build:
	scorep gcc -std=c99 target.c -o $(EXE)

run:
	time ./$(EXE)

clean:
	rm -rf scorep-* target.exe.*
