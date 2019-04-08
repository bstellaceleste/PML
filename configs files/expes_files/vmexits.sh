#!/bin/sh
xl dmesg > vmexits
grep "##Th" vmexits | cut -d":" -f2 | cut -d"," -f1 > handler.time
#cut -d' ' -f2 vmexits | grep "##vmexit" > vmexits.total_$1
#grep full vmexits.total_$1 > vmexits.pml.full_$1
wc -l handler.time #vmexits.total_$1
#wc -l vmexits.pml.full_$1
