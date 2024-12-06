package day5_test

import (
	"testing"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/day5"
)

var input = `47|53
97|13
97|61
97|47
75|29
61|13
75|53
29|13
97|29
53|29
61|53
97|53
61|29
47|13
75|47
97|75
47|61
75|61
47|29
75|13
53|13

75,47,61,53,29
97,61,53,29,13
75,29,13
75,97,47,61,53
61,13,29
97,13,75,29,47`

func TestPart1(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 143

	solver := day5.Part1Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 5 part 1 expected %v but got %v", expected, result)
	}
}

func TestPart2(t *testing.T) {
	log.SetLevel(log.DebugLevel)

	expected := 9

	solver := day5.Part2Solver{Input: input}
	result := solver.Solve()
	if result != expected {
		t.Fatalf("Solve() for day 5 part 2 expected %v but got %v", expected, result)
	}
}
