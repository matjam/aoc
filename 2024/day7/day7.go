package day7

import (
	"github.com/matjam/aoc/2024/registry"
)

func init() {
	registry.Register(7, 1, &Part1Solver{})
	registry.Register(7, 2, &Part2Solver{})
}
