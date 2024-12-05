package day3

import (
	"regexp"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/api"
	"github.com/matjam/aoc/2024/util"
)

type Part2Solver struct {
	Input string
}

func (s *Part2Solver) Run() {
	log.Info("🕵️ solving for day 3 part 2")

	var err error
	s.Input, err = api.GetInput(3)
	if err != nil {
		log.Fatal("💣 oopsie woopsie we did a little fucky wucky 💣")
	}

	result := s.Solve()

	log.Infof("🎄 day 3 part 2 result: %v", result)
}

func (s *Part2Solver) Solve() int {
	total := 0
	enabled := true
	re := regexp.MustCompile(`mul[(]([0-9]{1,3}),([0-9]{1,3})[)]|do[(][)]|don't[(][)]`)
	matches := re.FindAllStringSubmatch(s.Input, -1)

	log.Debugf("matches: %q", matches)

	for _, match := range matches {
		if match[0] == "do()" {
			enabled = true
			continue
		} else if match[0] == "don't()" {
			enabled = false
			continue
		} else if enabled {
			if len(match[1]) > 3 || len(match[2]) > 3 {
				log.Infof("skipping long params: %v * %v", match[1], match[2])
				continue
			}
			log.Debugf("calculating: %v * %v", match[1], match[2])
			total += util.ToInt(match[1]) * util.ToInt(match[2])
		} else {
			log.Debugf("skipping: %v * %v", match[1], match[2])
		}
	}

	return total
}
