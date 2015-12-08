# scorepGap

An example for the additional Scorep runtime on CentOS.

### Update

The additional runtime on CentOS was caused by a different measurement system.
Since the preferred macro `CLOCK_MONOTONIC_RAW` is not defined in `<bits/time.h>` on SLES11 scorep did a fallback to `CLOCK_MONOTONIC`. `clock_gettime(..)` simply has more overhead with `CLOCK_MONOTONIC_RAW`.

### Behavior

The instrumented binary requires ~50% additional runtime (in form of kernel time) on CentOS machines.
The behavior is reproduceable with modules "scorep/gcc/ompi/1.4.2" or "scorep/gcc-4.9.3-plugin/ompi/1.4.2".


