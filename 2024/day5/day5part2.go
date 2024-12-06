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
	correctedUpdates [][]int
}

func (s *Part2Solver) Run() {
	s.Input = util.GetInput(5, 2)
	log.Infof("🎄 day 5 part 1 result: %v", s.Solve())
}

func (s *Part2Solver) Solve() int {
	s.rules = make(map[int][]int)
	s.correctedUpdates = make([][]int, 0)
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
		line := scanner.Text()
		if line == "" {
			break
		}
		update := util.SplitStringToIntArray(line, ",")
		if len(update) == 0 {
			log.Fatalf("💣 expected at least 1 part but got %v", len(update))
		}

		if !IsValidUpdate(update, s.rules) {
			s.incorrectUpdates = append(s.incorrectUpdates, update)
		}
	}

	log.Debugf("incorrect updates: %v", s.incorrectUpdates)

	s.FixUpdates()

	return calculateSumOfMiddleValue(s.correctedUpdates)
}

// Scans through each incorrect update and reoders each of them based on the rules.
func (s *Part2Solver) FixUpdates() {
	for _, update := range s.incorrectUpdates {
		log.Debugf("!!! incorrect update: %v", update)

		for {
			update = s.ReorderUpdate(update)

			if IsValidUpdate(update, s.rules) {
				break
			}
		}

		log.Debugf("!!! fixed update: %v", update)

		s.correctedUpdates = append(s.correctedUpdates, update)
	}
}

func (s *Part2Solver) ReorderUpdate(update []int) []int {
	// work backwards through the update for each element and check if it's in the right place
	// if it's not, find the correct place and move it there. The ruleset contains a key for
	// a number which must be before any number in the value list for that key. If the number
	// is not in the correct place, move it to the correct place.

	// for each element in the update
	for i := len(update) - 1; i >= 0; i-- {
		pageNumber := update[i]
		if rule, ok := s.rules[pageNumber]; ok {
			// for each number in the rule, check if it's in the update
			for _, r := range rule {
				if ok, location := util.Contains(update, r); ok {
					if location < i {
						// move the number to the correct place
						t := update[location]
						update[location] = update[i]
						update[i] = t
					}
				}
			}
		}
	}

	return update
}
