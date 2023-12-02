CC=gcc
CFLAGS=-g -std=c17 -arch arm64

all: 2023/run/day1

2023/run/day1: 2023/day1/day1.c 2023/strutil.h
	$(CC) $(CFLAGS) -o run/day1 day1/day1.c -I2023