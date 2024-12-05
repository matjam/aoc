package day2_test

import (
	"testing"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/day2"
)

var input = `7 6 4 2 1
1 2 7 8 9
9 7 6 2 1
1 3 2 4 5
8 6 4 4 1
1 3 6 7 9`

func TestPart1Solve(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 2

	solver := day2.Part1Solver{}
	result := solver.Solve(input)
	if result != expected {
		t.Fatalf("Solve() for day 2 part 1 expected %v but got %v", expected, result)
	}
}

func TestPart2Solve(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 4

	solver := day2.Part2Solver{}
	result := solver.Solve(input)
	if result != expected {
		t.Fatalf("Solve() for day 2 part 1 expected %v but got %v", expected, result)
	}
}
