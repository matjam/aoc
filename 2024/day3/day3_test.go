package day3_test

import (
	"testing"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/day3"
)

var input = `xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))`

func TestPart1Solve(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 161

	solver := day3.Part1Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 3 part 1 expected %v but got %v", expected, result)
	}
}

func TestPart2Solve(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 48

	solver := day3.Part2Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 3 part 2 expected %v but got %v", expected, result)
	}
}
