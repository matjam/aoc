package util

// 😱 the dreaded util package, oh no! I shall surely be cast into the pits of hell for making a util package 😱

import (
	"strconv"
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/api"
)

func GetInput(day, part int) string {
	log.Infof("🕵️ solving for day %v part %v", day, part)

	var err error
	input, err := api.GetInput(day)
	if err != nil {
		log.Fatal("💣 oopsie woopsie we did a little fucky wucky 💣")
	}

	return input
}

// ToInt will take a string and convert it to an int, bombing if it can't.
func ToInt(v string) int {
	i, err := strconv.Atoi(v)
	if err != nil {
		log.Fatalf("💣 bad input string in ToInt(): %v", v)
	}
	return i
}

func ToInts(vs []string) []int {
	ints := make([]int, len(vs))
	for i, v := range vs {
		ints[i] = ToInt(v)
	}
	return ints
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

func Contains[T comparable](slice []T, v T) (bool, int) {
	for location, s := range slice {
		if s == v {
			return true, location
		}
	}
	return false, -1
}

// check if entry exists in map
func Exists[T comparable](m map[T]struct{}, key T) bool {
	_, ok := m[key]
	return ok
}

func SplitStringToIntArray(s string, sep string) []int {
	parts := strings.Split(s, sep)
	ints := make([]int, len(parts))
	for i, p := range parts {
		ints[i] = ToInt(p)
	}
	return ints
}
