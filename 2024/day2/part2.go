package day2

import (
	"bufio"
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/api"
	"github.com/matjam/aoc/2024/registry"
	"github.com/matjam/aoc/2024/util"
)

func init() {
	registry.Register(2, 2, Part2Solver{})
}

type Part2Solver struct{}

func (s Part2Solver) Run() {
	log.Info("🕵️ solving for day 2 part 2")

	input, err := api.GetInput(2)
	if err != nil {
		log.Fatal("💣 oopsie woopsie we did a little fucky wucky 💣")
	}

	result := s.Solve(input)

	log.Infof("🎄 day 2 part 2 result: %v", result)
}

func (s Part2Solver) Solve(input string) int {
	totalSafe := 0
	scanner := bufio.NewScanner(strings.NewReader(input))

	var safe bool

	// each line is a "report"
	for scanner.Scan() {
		// each line is a list of numbers separated by space
		levels := strings.Split(scanner.Text(), " ")

		log.Debugf("considering %v", levels)

		safe = isSafe(levels)
		if safe {
			log.Debugf("%v is SAFE", levels)
			totalSafe += 1
		} else {
			// a bit bruteforcy
			for i := range levels {
				levelsCopy := make([]string, len(levels))
				copy(levelsCopy, levels)
				levelsCopy = util.Remove(levelsCopy, i)
				log.Debugf("removed %v", levelsCopy)
				if isSafe(levelsCopy) {
					safe = true
					break
				}
			}
			if safe {
				log.Debugf("%v is SAFE", levels)
				totalSafe += 1
			} else {
				log.Debugf("%v is UNSAFE", levels)
			}
		}
	}

	return totalSafe
}
