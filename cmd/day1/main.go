package main

import (
	"fmt"
	"sort"

	"github.com/matjam/aoc2022/util"
)

func main() {
	part1()
	part2()
}

func part1() {
	lines := util.GetInputLines("input/day1.txt")
	mostCalories := 0
	currentCalories := 0

	for _, amount := range lines {
		if amount == "" {
			if currentCalories > mostCalories {
				mostCalories = currentCalories
			}
			currentCalories = 0
			continue
		}

		currentCalories += util.Atoi(amount)
	}

	fmt.Printf("Part 1: The Elf carrying the most Calories is carrying %v calories.\n", mostCalories)
}

func part2() {
	type elf struct {
		number   int
		calories int
	}

	lines := util.GetInputLines("input/day1.txt")
	elves := []elf{}
	currentCalories := 0
	currentElf := 0

	for _, amount := range lines {
		if amount == "" {
			elves = append(elves, elf{currentElf, currentCalories})
			currentCalories = 0
			currentElf++
			continue
		}

		currentCalories += util.Atoi(amount)
	}

	sort.Slice(elves, func(d, e int) bool {
		return elves[d].calories > elves[e].calories
	})

	total := elves[0].calories + elves[1].calories + elves[2].calories
	fmt.Printf("Part 2: The 3 Elves carrying the most calories are carrying %v Calories\n", total)
}
