package main

import (
	"fmt"
	"strings"

	"github.com/matjam/aoc2022/util"
)

// 34-43,42-42
func main() {
	contains := 0
	overlaps := 0
	lines := util.GetInputLines("input/day4.txt")
	for _, line := range lines {
		pairs := strings.Split(line, ",")
		aPair := strings.Split(pairs[0], "-")
		bPair := strings.Split(pairs[1], "-")

		if fullyContainedRange(util.Atoi(aPair[0]),
			util.Atoi(aPair[1]),
			util.Atoi(bPair[0]),
			util.Atoi(bPair[1])) {
			contains++
		}

		if overlappingRange(util.Atoi(aPair[0]),
			util.Atoi(aPair[1]),
			util.Atoi(bPair[0]),
			util.Atoi(bPair[1])) {
			overlaps++
		}

	}

	fmt.Printf("day4 Part1: found %v assignments where one is fully contained by the other.\n", contains)
	fmt.Printf("day4 Part2: found %v assignments where one overlaps another.\n", overlaps)

}

func fullyContainedRange(ax, ay, bx, by int) bool {
	return (ax >= bx && ay <= by) || (bx >= ax && by <= ay)
}

func overlappingRange(leftA, leftB, rightA, rightB int) bool {
	return (leftA >= rightA && leftA <= rightB) ||
		(leftB >= rightA && leftB <= rightB) ||
		(rightA >= leftA && rightA <= leftB) ||
		(rightB >= leftA && rightB <= leftB)
}
