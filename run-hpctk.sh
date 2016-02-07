#!/bin/bash

if [ -z "$1" ]; then
	echo "ERROR: specify target binary"
	exit 1
fi

TARGET=$1
OUT=tmp-measurement
LOG=hpctk-$TARGET.log

echo "$TARGET ${@:2}" > $LOG
echo "$TARGET" > $LOG.samples

FREQS="2500000 1250000 250000 125000 500000 250000 12500 10000 5000 2500"
for freq in $FREQS; do

	CLOCK=PAPI_TOT_CYC@$freq
	echo -e "$CLOCK \c"
	RUNTIMES=""
	SAMPLES=""

	for i in {1..10}; do

		rm -rf $OUT
		RUNTIME=`taskset -c 5 hpcrun -e $CLOCK -o $OUT $TARGET ${@:2}`
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

