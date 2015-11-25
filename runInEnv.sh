#!/bin/bash

module unload gcc scorep papi && \ 
module load scorep/gcc/ompi/1.4.2 gcc/4.9.3 papi && \
make 
