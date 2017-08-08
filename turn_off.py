#!/usr/bin/env python3
import socket

sock = socket.socket(type=socket.SOCK_DGRAM)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 1)
sock.sendto(bytes([254,254,254]), ("239.28.4.94",5005))
