cut -d' ' -f3 hyper.real | sort -u > hyper.back
mv hyper.back hyper
for val in `echo "2 4 6 8"`
do
	grep val vm | cut -d'l' -f2,3,4,5  | cut -d' ' -f$val |sort -u > vm$val
	./checkMatching.sh vm$val > result_$val
done
