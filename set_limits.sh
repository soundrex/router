#!/bin/ash

for f in queues/tx*
do
	echo 4096 > $f/byte_queue_limits/limit_max
done
