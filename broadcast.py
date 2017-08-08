#!/usr/bin/env python3
from datetime import datetime, timedelta

import io
import socket
import sys

UDP_ADDR = ("239.28.4.94", 5005)
num_samples = 384
packet_size = num_samples*3+1

sock = socket.socket(type=socket.SOCK_DGRAM)
sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, 1)

def send_starter():
    if (len(sys.argv) < 3):
        return
    tcp_sock = socket.socket()
    tcp_sock.connect((sys.argv[1], int(sys.argv[2])))
    tcp_sock.close()

with io.open("music.txt", "rb") as music:
    send_starter()
    tm = datetime.now() + timedelta(microseconds=50000)
    print(tm)
    for packet in iter(lambda: music.read(packet_size), b''):
        if packet[0] == 255:
            sock.sendto(packet[:packet.find(bytes([254, 254, 254, 254, 254]))], UDP_ADDR)
        else:
            wait_time = timedelta(microseconds=num_samples*125//3)
            while datetime.now()-tm < wait_time:
                pass
            tm += wait_time
            sock.sendto(packet, UDP_ADDR)
