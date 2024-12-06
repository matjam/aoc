package day5

import (
	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/registry"
	"github.com/matjam/aoc/2024/util"
)

func init() {
	registry.Register(5, 1, &Part1Solver{})
	registry.Register(5, 2, &Part2Solver{})
}

func IsValidUpdate(update []int, rules map[int][]int) bool {
	bad := false
	seen := make([]int, 0)

	log.Debugf("update: %v", update)

	for _, entry := range update {
		rule := rules[entry]
		for _, r := range rule {
			if ok, _ := util.Contains(seen, r); ok {
				bad = true
				break
			}
		}

		if bad {
			break
		}

		seen = append(seen, entry)
	}

	return !bad
}

func calculateSumOfMiddleValue(updates [][]int) int {
	total := 0
	for _, update := range updates {
		middleNumber := update[len(update)/2]
		total += middleNumber
	}
	return total
}
