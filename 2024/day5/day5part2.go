package day5

import (
	"bufio"
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/util"
)

type Part2Solver struct {
	Input string

	rules            map[int][]int
	incorrectUpdates [][]int
}

func (s *Part2Solver) Run() {
	s.Input = util.GetInput(5, 2)
	log.Infof("🎄 day 5 part 1 result: %v", s.Solve())
}

func (s *Part2Solver) Solve() int {
	total := 0
	s.rules = make(map[int][]int)
	s.incorrectUpdates = make([][]int, 0)
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
		bad := false
		seen := make([]int, 0)
		line := scanner.Text()
		if line == "" {
			break
		}
		updates := util.SplitStringToIntArray(line, ",")
		if len(updates) == 0 {
			log.Fatalf("💣 expected at least 1 part but got %v", len(updates))
		}
		log.Debugf("update: %v", updates)

		for _, update := range updates {
			rule := s.rules[update]
			for _, r := range rule {
				if util.Contains(seen, r) {
					bad = true
					break
				}
			}

			if bad {
				break
			}

			seen = append(seen, update)
		}

		if bad {
			s.incorrectUpdates = append(s.incorrectUpdates, updates)
		}
	}

	log.Debugf("incorrect updates: %v", s.incorrectUpdates)

	return total
}

// Scans through each incorrect update and reoders each of them based on the rules.
func (s *Part2Solver) FixUpdates() []int {
	for _, update := range s.incorrectUpdates {
		s.ReorderUpdate(update)
	}
	return nil
}

func (s *Part2Solver) ReorderUpdate(update []int) []int {

	return nil
}
