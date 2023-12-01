package main

import (
	"fmt"
	"strings"

	"github.com/matjam/aoc/2022/util"
)

func main() {
	part1()
	part2()
}

// Toyed around with making a special type for this, but it really isn't necessary, and you
// can just operate on the slices directly.

// builds the initial slice of rune slices that we represent the stacks in.
func initialState() ([][]rune, []string) {
	// the containing slice
	stack := make([][]rune, 9)

	// allocate the initial slice
	for x := 0; x < 9; x++ {
		stack[x] = make([]rune, 0, 100)
	}

	lines := util.GetInputLines("input/day5.txt")

	for y := 0; y < 8; y++ {
		line := lines[y]

		for x := 0; x < 9; x++ {
			// get character at each column and put it in the stringstack directly
			r := rune(line[1+4*x])
			if r != ' ' {
				if len(stack[x]) < 7-y {
					stack[x] = make([]rune, 8-y, 100)
				}
				stack[x][7-y] = r
			}
		}
	}

	return stack, lines[10:]
}

// for debugging
func printStack(stack [][]rune) {
	for i, item := range stack {
		fmt.Printf("%v: %c\n", i+1, item)
	}
}

func mover(part string, move func(stack [][]rune, from, to, count int)) {
	stack, lines := initialState()

	for _, line := range lines {
		command := strings.Fields(line)

		if len(command) != 6 {
			continue
		}

		if command[0] != "move" {
			continue
		}

		count := util.Atoi(command[1])
		from := util.Atoi(command[3]) - 1
		to := util.Atoi(command[5]) - 1

		if len(stack[from]) == 0 {
			panic("unsure what we should do here, but this is unexpected")
		}

		move(stack, from, to, count)
	}
	topCrates := ""

	for i := range stack {
		count := len(stack[i])
		if count > 0 {
			topCrates = topCrates + string(stack[i][count-1])
		}
	}

	fmt.Printf("day 5 %v: top crate on each stack: %v\n", part, topCrates)
}

func part1() {
	mover("part1", func(stack [][]rune, from int, to int, count int) {
		// be nice if we could just move slices around
		for i := 0; i < count; i++ {
			var r rune

			// This is moving count number of items like a tower of hanoi. We have to do it
			// one at a time because there isn't an easy way to reverse a slice. Take one rune:
			r, stack[from] = stack[from][len(stack[from])-1], stack[from][:len(stack[from])-1]

			// now add it to the destination
			stack[to] = append(stack[to], r)
		}

	})
}

func part2() {
	mover("part2", func(stack [][]rune, from int, to int, count int) {
		// ooh cool
		offset := len(stack[from]) - count

		// takes the count number of items from the from stack, and appends them
		stack[to] = append(stack[to], stack[from][offset:]...)

		// removes those items from the from stack
		stack[from] = stack[from][:offset]
	})
}
