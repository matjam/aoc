package day5

import (
	"bufio"
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/util"
)

type Part1Solver struct {
	Input string

	rules map[int][]int
}

func (s *Part1Solver) Run() {
	s.Input = util.GetInput(5, 1)
	log.Infof("🎄 day 5 part 1 result: %v", s.Solve())
}

func (s *Part1Solver) Solve() int {
	total := 0
	s.rules = make(map[int][]int)
	scanner := bufio.NewScanner(strings.NewReader(s.Input))
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			break
		}
		parts := strings.Split(line, "|")
		if len(parts) != 2 {
			log.Fatalf("💣 expected 2 parts but got %v", len(parts))
		}

		key := util.ToInt(parts[0])
		value := util.ToInt(parts[1])

		if _, ok := s.rules[key]; !ok {
			s.rules[key] = make([]int, 0)
		}
		s.rules[key] = append(s.rules[key], value)

	}
	log.Debugf("rules: %v", s.rules)

	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			break
		}
		updates := util.SplitStringToIntArray(line, ",")
		if len(updates) == 0 {
			log.Fatalf("💣 expected at least 1 part but got %v", len(updates))
		}

		if IsValidUpdate(updates, s.rules) {
			middleNumber := updates[len(updates)/2]
			total += middleNumber
		}
	}

	return total
}
