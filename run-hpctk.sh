#!/bin/bash

if [ -z "$1" ]; then
	echo "ERROR: specify target binary"
	exit 1
fi

TARGET=$1
OUT=tmp-measurement
LOG=hpctk-$TARGET.log
ITERATIONS=10

echo "$TARGET ${@:2}" > $LOG
echo "$TARGET" > $LOG.samples

FREQS="2,500,000 1,250,000 250,000 125,000 50,000 25,000 12,500 10,000 5,000 2,500"
for freq in ${FREQS//,}; do

	CLOCK=PAPI_TOT_CYC@$freq
	echo -e "$CLOCK \c"
	RUNTIMES=""
	SAMPLES=""

	for i in {1..$ITERATIONS}; do

		rm -rf $OUT
		taskset -c 5 hpcrun -e $CLOCK -o $OUT $TARGET ${@:2} > /dev/null 2> /tmp/Runtime
		RUNTIME=$(</tmp/Runtime)
		profile=`find $OUT/ -name "*.log"`
	
		SAMPLE=`grep -r SUMMARY $profile | awk '{print $3}'`

		RUNTIMES+="$RUNTIME "
		SAMPLES+="$SAMPLE "

		echo -e "$i \c"
	done
	echo ""
	echo "$CLOCK	time $RUNTIMES" >> $LOG
	echo "$CLOCK	samples $SAMPLES" >> $LOG.samples
done

cat $LOG.samples >> $LOG

echo "reference" >> $LOG
for i in {1..$ITERATIONS}; do 

	taskset -c 5 $TARGET ${@:2} > /dev/null 2> /tmp/Runtime
	RUNTIME=$(</tmp/Runtime)

	echo -e "$RUNTIME \c" >> $LOG
	echo -e "$i \c"
done
