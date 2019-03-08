#!/bin/bash

### Params : 
## $1 : Domain id
## $2 : Time of observation
## $3 : Interval of every observations

### Example : 
## ./script_collect.sh 2 5 10
## This collects the dirty logs on the domain of id 2 for an observation period of 5 mins every 10 seconds

i=0
rm to_plot.txt
sudo xl clean-dirty-bitmap $1
sudo xl dmesg -c
period=$((SECONDS + 60*$2))
while(("$SECONDS" <= "$period"))
do
	sleep $3
	sudo xl collect-dirty-logs $1
	sudo xl dmesg -c > log.txt
	./read_log $SECONDS
	cp to_plot.txt to_plot.csv
	gnuplot plotGlobal.gnu
	pdflatex plotGlobal.tex
	rm *.aux
	rm *.log
	evince plotGlobal.pdf &
	
	((i++))
done

#mv to_plot.txt to_plot.csv
#./globalPlot.sh
