CC=gcc
CFLAGS=-g -std=gnu17

COMMON_HEADERS := $(shell find common -name '*.h')
COMMON_SRC := $(shell find common -name '*.c')
COMMON_OBJ := $(COMMON_SRC:.c=.o)

DAY1_SRC := $(shell find day1 -name '*.c')
DAY1_OBJ := $(DAY1_SRC:.c=.o)

.DEFAULT_GOAL := all

all: bin/day1

bin/day1: $(DAY1_OBJ) $(COMMON_OBJ)
	$(CC) $(CFLAGS) -o bin/day1 $(DAY1_OBJ) $(COMMON_OBJ)

day1/%.o: day1/%.c $(HEADERS) $(COMMON_HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -Icommon

common/%.o: common/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -Icommon

run: bin/day1
	./bin/day1

test: bin/day1
	./bin/day1 test

clean: 
	rm -rf ./bin/*
	rm -rf ./day1/*.o
	rm -rf ./common/*.o
