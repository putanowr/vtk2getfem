#!/bin/sh

PROG=$1
DATADIR=$2

$PROG $DATADIR/data/simple_ugrid.vtk -i -s > infoTest.out 2>&1

if [ ! -x $PROG ]; then
  echo "$PROG does not exesits"
fi 	
if cmp -s infoTest.out $DATADIR/results/infoTest.out; then
  exit 0
else
  echo "ACTUAL versu EXPECTED diff"
  diff infoTest.out $DATADIR/results/infoTest.out
  exit 1
fi
