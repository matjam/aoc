package day1_test

import (
	"testing"

	"github.com/matjam/aoc/2024/day1"
)

func TestPart2Solve(t *testing.T) {
	input := `3   4
4   3
2   5
1   3
3   9
3   3`
	expected := 31

	solver := day1.Part2Solver{}
	result := solver.Solve(input)
	if result != expected {
		t.Fatalf("Solve() for day 1 part 2 expected %v but got %v", expected, result)
	}
}
