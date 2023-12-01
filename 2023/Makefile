CC=gcc
CFLAGS=-g -std=c17 -arch arm64

all: run/day1

run/day1: day1/day1.c strutil.h
	$(CC) $(CFLAGS) -o run/day1 day1/day1.c -I.