#!/bin/bash

SCRIPT=`basename $0`
DIR=`echo $BASH_SOURCE | sed "s/$SCRIPT//"`
cd $DIR

../geoip <./test1_infile | diff - ./test1_outfile && echo "Test 1 passed"