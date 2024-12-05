package day3

import (
	"regexp"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/api"
	"github.com/matjam/aoc/2024/util"
)

type Part1Solver struct {
	Input string
}

func (s *Part1Solver) Run() {
	log.Info("🕵️ solving for day 3 part 1")

	var err error
	s.Input, err = api.GetInput(3)
	if err != nil {
		log.Fatal("💣 oopsie woopsie we did a little fucky wucky 💣")
	}

	result := s.Solve()

	log.Infof("🎄 day 3 part 1 result: %v", result)
}

func (s *Part1Solver) Solve() int {
	total := 0
	re := regexp.MustCompile(`mul\((\d+),(\d+)\)`)

	for _, match := range re.FindAllStringSubmatch(s.Input, -1) {
		log.Debugf("found match: %v", match)
		total += util.ToInt(match[1]) * util.ToInt(match[2])
	}

	return total
}
