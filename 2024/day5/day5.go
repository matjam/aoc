package day5

import "github.com/matjam/aoc/2024/registry"

func init() {
	registry.Register(5, 1, &Part1Solver{})
	registry.Register(5, 2, &Part2Solver{})
}
