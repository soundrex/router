#!/bin/ash

/etc/init.d/network restart
sleep 2
route -n add -net 224.0.0.0/3 dev br-lan
for i in bridge/multicast_*
do
	echo 0 > $i
done
ifconfig wlan1 txqueuelen 0
