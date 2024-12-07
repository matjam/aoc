package day7_test

import (
	"testing"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/day7"
)

var input = `190: 10 19
3267: 81 40 27
83: 17 5
156: 15 6
7290: 6 8 6 15
161011: 16 10 13
192: 17 8 14
21037: 9 7 18 13
292: 11 6 16 20`

func TestPart1(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 3749

	solver := day7.Part1Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 5 part 1 expected %v but got %v", expected, result)
	}
}

func TestPart2(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 11387

	solver := day7.Part2Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 5 part 2 expected %v but got %v", expected, result)
	}
}
