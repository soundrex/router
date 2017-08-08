#!/bin/ash

ps | grep python | grep -v grep | awk '{print $1}' | xargs kill
