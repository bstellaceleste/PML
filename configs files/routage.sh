#brctl addbr xenbr0
ifconfig xenbr0 10.0.0.1
brctl addif xenbr0 vif1.0
iptables --flush
iptables -t nat --flush
iptables -A FORWARD -o wlp2s0 -i xenbr0 -s 10.0.0.0/24 -m conntrack --ctstate NEW -j ACCEPT
iptables -A FORWARD -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
iptables -t nat -A POSTROUTING -o wlp2s0 -j MASQUERADE
echo 1 > /proc/sys/net/ipv4/ip_forward

