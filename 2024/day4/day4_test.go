package day4_test

import (
	"testing"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/day4"
)

var input = `MMMSXXMASM
MSAMXMSMSA
AMXSXMAAMM
MSAMASMSMX
XMASAMXAMM
XXAMMXXAMA
SMSMSASXSS
SAXAMASAAA
MAMMMXMMMM
MXMXAXMASX`

func TestPart1(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 18

	solver := day4.Part1Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 4 part 1 expected %v but got %v", expected, result)
	}
}

func TestPart2(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 9

	solver := day4.Part2Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 4 part 2 expected %v but got %v", expected, result)
	}
}
