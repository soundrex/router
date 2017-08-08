#!/bin/ash

awk '{print $4}' | sort -nr | uniq -c
