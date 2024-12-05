package util

// 😱 the dreaded util package, oh no! I shall surely be cast into the pits of hell for making a util package 😱

import (
	"strconv"

	"github.com/charmbracelet/log"
)

// ToInt will take a string and convert it to an int, bombing if it can't.
func ToInt(v string) int {
	i, err := strconv.Atoi(v)
	if err != nil {
		log.Fatalf("💣 bad input string in ToInt(): %v", v)
	}
	return i
}

func IntDistance(a, b int) int {
	if a > b {
		return a - b
	}
	return b - a
}

// omg, a use for generics
func Remove[T any](slice []T, s int) []T {
	return append(slice[:s], slice[s+1:]...)
}
