package day1_test

import (
	"testing"

	"github.com/matjam/aoc/2024/day1"
)

func TestPart1Solve(t *testing.T) {
	input := `3   4
4   3
2   5
1   3
3   9
3   3`
	expected := 11

	solver := day1.Part1Solver{}
	result := solver.Solve(input)
	if result != expected {
		t.Fatalf("Solve() for day 1 part 1 expected %v but got %v", expected, result)
	}
}
