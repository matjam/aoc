package main

import (
	"fmt"

	"github.com/matjam/aoc/2022/util"
)

// recursively find the first character in the first string that is also in the second
// string. If the string is not found, then remove the first item off the first string
// and try again
func recursiveFindItem(first []rune, second []rune) rune {
	if len(first) == 0 {
		return ' '
	}

	candidate := first[0]
	if contains(second, candidate) {
		return candidate
	}

	// didn't find it, take an item off the front.
	first = first[1:]

	// we must go deeper
	return recursiveFindItem(first, second)
}

// This does the same thing as above but probably performs better.
func findItem(rucksacks [][]rune) rune {
	// scan rucksack 0
	for _, x := range rucksacks[0] {
		// scan rucksack 1
		for _, y := range rucksacks[1] {
			if y == x {
				return x
			}
		}
	}

	return ' '
}

func main() {
	part1a()
	part2()
}

func part1a() {
	lines := util.GetInputLines("input/day3.txt")
	priorities := 0

	for _, line := range lines {
		first := line[0 : len(line)/2]
		second := line[len(line)/2:]

		found := recursiveFindItem([]rune(first), []rune(second))

		priorities += runePriority(found)
	}

	fmt.Printf("Part 1: sum of the priorities is %v\n", priorities)
}

// gives the elven rune priority for a given rune
func runePriority(r rune) int {
	// Lowercase item types a through z have priorities 1 through 26.
	// Uppercase item types A through Z have priorities 27 through 52.

	if r > 96 && r < 123 {
		return int(r) - 96
	}

	if r > 64 && r < 92 {
		return int(r) - 38
	}

	panic("shouldn't get here")
}

func contains(s []rune, e rune) bool {
	for _, a := range s {
		if a == e {
			return true
		}
	}
	return false
}

// given 3 rune slices, we search for the each character in the first slice,
// through both slices. If we find it, we return it.
//
// reusing recursiveFindItem() will result in a stack overflow. A neat example
// where recursion is not always your friend.
func findCommon(rucksacks [][]rune) rune {
	// scan rucksack 0
	for _, x := range rucksacks[0] {
		// scan rucksack 1
		for _, y := range rucksacks[1] {
			if y == x {
				// scan rucksack 2
				for _, z := range rucksacks[2] {
					if x == z {
						return x
					}
				}
			}
		}
	}

	return 0
}

func part2() {
	lines := util.GetInputLines("input/day3.txt")
	priorities := 0

	var rucksacks [][]rune

	for _, line := range lines {
		// if the length is none or 1 then we add another then
		// continue the loop.
		if len(rucksacks) < 2 {
			// need to add another bunch
			rucksacks = append(rucksacks, []rune(line))
			continue
		}

		// add the current rucksack and look for the common rune
		rucksacks = append(rucksacks, []rune(line))

		found := findCommon(rucksacks)
		priorities += runePriority(found)
		rucksacks = [][]rune{}
	}

	fmt.Printf("Part 2: sum of the badge priorities is %v\n", priorities)
}
