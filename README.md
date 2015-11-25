# scorepGap
An example for the additional Scorep runtime on CentOS.

The instrumented binary requires ~50% additional runtime (in form of kernel time) on CentOS machines.
The behavior is reproduceable with modules "scorep/gcc/ompi/1.4.2" or "scorep/gcc-4.9.3-plugin/ompi/1.4.2".
