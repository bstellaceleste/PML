/etc/init.d/xencommons start
brctl addbr xenbr0
ifconfig xenbr0 10.0.0.1
