reset 
unset  multiplot

set terminal png
set output "wss.png"

#set term tikz standalone size 2.5in,2in
#set output "plotGlobal.tex"


set size 1,1
set multiplot layout 1,1
set origin 0,0

#set yrange [0:2500]
#set xrange [-1:12]
#set ytics nomirror
#set xtics  norangelimit
#set xtics offset 0,0,0
set ylabel "WSS\/Nbpages" offset 1,0,0
set xlabel "Time\/s" 
set ytics  norangelimit autofreq offset 1,0,0
set grid y
set bmargin 6
set offset .05, .05
set style func linespoints
set title("Working set size estimation")

#set label 11 center at graph 0.5,char 1 "Working set size estimation"  
#set style line  1 lt 1 lc rgb '#000004' # black

plot "./to\_plot.csv" u 1:2 ps 2 pt 6 lw 3 lc 3 w lp notitle
#lt 1 lc rgb '#1c1044'  

