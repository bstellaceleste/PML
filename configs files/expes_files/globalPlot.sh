gnuplot plotGlobal.gnu
pdflatex plotGlobal.tex
rm *.aux
rm *.log
evince plotGlobal.pdf 
