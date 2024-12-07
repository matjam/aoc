package day6_test

import (
	"testing"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/day6"
)

var input = `....#.....
.........#
..........
..#.......
.......#..
..........
.#..^.....
........#.
#.........
......#...`

func TestPart1(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 41

	solver := day6.Part1Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 5 part 1 expected %v but got %v", expected, result)
	}
}

func TestPart2(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 6

	solver := day6.Part2Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 5 part 2 expected %v but got %v", expected, result)
	}
}
