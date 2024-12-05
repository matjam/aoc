package day3

import "github.com/matjam/aoc/2024/registry"

func init() {
	registry.Register(3, 1, &Part1Solver{})
	registry.Register(3, 2, &Part2Solver{})
}
