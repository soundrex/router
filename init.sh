#!/bin/ash

ln -s /sys/devices/soc/soc\:pcie-controller/pci0000\:00/0000\:00\:02.0/0000\:02\:00.0/net/wlan1/queues/ .
ln -s /sys/devices/virtual/net/br-lan/bridge/ .
