package util

import (
	"os"
	"strconv"
	"strings"
)

func Atoi(s string) int {
	v, err := strconv.Atoi(s)
	if err != nil {
		panic(err)
	}

	return v
}

func GetInputLines(name string) []string {
	input, err := os.ReadFile(name)
	if err != nil {
		panic(err)
	}

	return strings.Split(string(input), "\n")
}
