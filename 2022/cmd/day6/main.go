package main

import (
	"fmt"
	"os"
)

var debug bool

func main() {
	_, debug = os.LookupEnv("AOC_DEBUG")

	dataStream, err := os.ReadFile("input/day6.txt")
	if err != nil {
		panic(err)
	}

	part1([]byte(dataStream))
}

func part1(d []byte) {
	position := detect(d, 4)
	fmt.Printf("day6 part1: found start-of-packet marker at position %v\n", position)

	position = detect(d, 14)
	fmt.Printf("day6 part2: found start-of-message marker at position %v\n", position)
}

func detect(d []byte, count int) int {
	buffer := make([]byte, count)

	for i, c := range d {
		for x := count; x > 1; x-- {
			buffer[x-1] = buffer[x-2]
		}

		buffer[0] = c

		if i > 3 && hasUniqueCharacters(buffer) {
			return i + 1
		}
	}

	return -1
}

func hasUniqueCharacters(b []byte) bool {
	byteMap := make(map[byte]int)

	for _, c := range b {
		if _, ok := byteMap[c]; ok {
			return false
		} else {
			byteMap[c] = 1
		}
	}

	return true
}
