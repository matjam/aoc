package main

import (
	"testing"
)

var result rune
var line = "hCPQbPZPbjSbwwjCPChSClJJfzqTggTFDfsJngDg"
var first = line[0 : len(line)/2]
var second = line[len(line)/2:]

func BenchmarkRecursiveFind1(b *testing.B) {
	for n := 0; n < b.N; n++ {
		result = recursiveFindItem([]rune(first), []rune(second))
	}
}

func BenchmarkFind1(b *testing.B) {
	for n := 0; n < b.N; n++ {
		result = findItem([][]rune{[]rune(first), []rune(second)})
	}
}
