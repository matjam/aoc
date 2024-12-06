package day4

import "github.com/matjam/aoc/2024/registry"

func init() {
	registry.Register(4, 1, &Part1Solver{})
	registry.Register(4, 2, &Part2Solver{})
}

type Direction int

const (
	North Direction = iota
	NorthEast
	East
	SouthEast
	South
	SouthWest
	West
	NorthWest
)

func (d Direction) String() string {
	return [...]string{"North", "NorthEast", "East", "SouthEast", "South", "SouthWest", "West", "NorthWest"}[d]
}
