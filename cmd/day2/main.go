package main

import (
	"fmt"
	"strings"

	"github.com/matjam/aoc2022/util"
)

type hand int

const (
	rock     hand = 1
	paper    hand = 2
	scissors hand = 3
)

func (h hand) String() string {
	switch h {
	case rock:
		return "rock"
	case paper:
		return "paper"
	case scissors:
		return "scissors"
	}

	panic("should not get here")
}

// LossHand returns the hand that will lose the given hand.
func (h hand) LossHand() hand {
	switch h {
	case rock:
		return scissors
	case paper:
		return rock
	case scissors:
		return paper
	}

	panic("should not get here")
}

// WinHand returns the hand that will win the given hand.
func (h hand) WinHand() hand {
	switch h {
	case rock:
		return paper
	case paper:
		return scissors
	case scissors:
		return rock
	}

	panic("should not get here")
}

// DrawHand returns the hand that will win the given hand.
func (h hand) DrawHand() hand {
	return h
}

type roundResult int

const (
	win  roundResult = 6
	draw roundResult = 3
	loss roundResult = 0
)

func (h roundResult) String() string {
	switch h {
	case win:
		return "win"
	case draw:
		return "draw"
	case loss:
		return "loss"
	}

	panic("should not get here")
}

func playerRoundResult(elfHand hand, playerHand hand) roundResult {
	switch elfHand {
	case rock:
		switch playerHand {
		case rock:
			return draw
		case paper:
			return win
		case scissors:
			return loss
		}
	case paper:
		switch playerHand {
		case rock:
			return loss
		case paper:
			return draw
		case scissors:
			return win
		}
	case scissors:
		switch playerHand {
		case rock:
			return win
		case paper:
			return loss
		case scissors:
			return draw
		}
	}

	panic("we shouldn't get here")
}

func getHand(v string) hand {
	switch v {
	case "A":
		return rock
	case "B":
		return paper
	case "C":
		return scissors
	case "X":
		return rock
	case "Y":
		return paper
	case "Z":
		return scissors
	}

	panic("we should not get here")
}

func getDesiredResult(v string) roundResult {
	switch v {
	case "X":
		return loss
	case "Y":
		return draw
	case "Z":
		return win
	}

	panic("we should not get here")
}

func main() {
	part1()
	part2()
}

func part1() {
	lines := util.GetInputLines("input/day2.txt")

	playerScore := 0
	for _, line := range lines {
		hands := strings.Split(line, " ")
		elfHand := getHand(hands[0])
		playerHand := getHand(hands[1])
		result := playerRoundResult(elfHand, playerHand)

		playerScore += int(result) + int(playerHand)
	}

	fmt.Printf("Part 1: The strategy nets a score of %v\n", playerScore)
}

func part2() {
	lines := util.GetInputLines("input/day2.txt")

	playerScore := 0
	for _, line := range lines {
		hands := strings.Split(line, " ")
		elfHand := getHand(hands[0])
		desiredResult := getDesiredResult(hands[1])

		var playerHand hand
		switch desiredResult {
		case loss:
			playerHand = elfHand.LossHand()
		case draw:
			playerHand = elfHand.DrawHand()
		case win:
			playerHand = elfHand.WinHand()
		}

		result := playerRoundResult(elfHand, playerHand)

		playerScore += int(result) + int(playerHand)
	}

	fmt.Printf("Part 1: The strategy nets a score of %v\n", playerScore)
}
