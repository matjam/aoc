package main

import "github.com/matjam/aoc/2022/util"

func main() {
	lines := util.GetInputLines("input/day7test.txt")

	part1(lines)
}

type node struct {
	name string
	size int

	children map[string]node
}

func part1(lines []string) {
	if lines[0] != "$ cd /" {
		panic("first line should be '$ cd /' so there's something wrong")
	}

	addFolder(lines[1:], "/")
}

// creates a new node and parses lines, returning what it hasn't parsed
func addFolder(lines []string, name string) (node, []string) {
	n := node{
		name:     name,
		size:     0,
		children: make(map[string]node),
	}

	return n, lines
}
