package day2

import (
	"bufio"
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/api"
	"github.com/matjam/aoc/2024/registry"
)

func init() {
	registry.Register(2, 1, Part1Solver{})
}

type Part1Solver struct{}

func (s Part1Solver) Run() {
	log.Info("🕵️ solving for day 2 part 1")

	input, err := api.GetInput(2)
	if err != nil {
		log.Fatal("💣 oopsie woopsie we did a little fucky wucky 💣")
	}

	result := s.Solve(input)

	log.Infof("🎄 day 2 part 1 result: %v", result)
}

func (s Part1Solver) Solve(input string) int {
	totalSafe := 0
	scanner := bufio.NewScanner(strings.NewReader(input))

	// each line is a "report"
	for scanner.Scan() {
		// each line is a list of numbers separated by space
		levels := strings.Split(scanner.Text(), " ")

		safe := isSafe(levels)

		if safe {
			log.Debugf("%v is SAFE", levels)
			totalSafe += 1
		} else {
			log.Debugf("%v is UNSAFE", levels)
		}
	}

	return totalSafe
}
