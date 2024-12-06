package day4

import (
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/api"
)

type Part2Solver struct {
	Input string

	grid   []string
	width  int
	height int
}

func (s *Part2Solver) Run() {
	log.Info("🕵️ solving for day 4 part 2")

	var err error
	s.Input, err = api.GetInput(4)
	if err != nil {
		log.Fatal("💣 oopsie woopsie we did a little fucky wucky 💣")
	}

	result := s.Solve()

	log.Infof("🎄 day 4 part 2 result: %v", result)
}

func (s *Part2Solver) Solve() int {
	s.grid = strings.Split(s.Input, "\n")
	s.width = len(s.grid[0])
	s.height = len(s.grid)

	count := 0

	log.Debugf("width: %v, height: %v", s.width, s.height)

	for y := 0; y < s.height; y++ {
		for x := 0; x < s.width; x++ {
			count += s.findMas(x, y)
		}
	}

	return count
}

func (s *Part2Solver) getRune(x int, y int) rune {
	if x < 0 || x >= s.width || y < 0 || y >= s.height {
		return ' '
	}

	return rune(s.grid[y][x])
}

var patterns = [][]string{
	{
		"M S",
		" A ",
		"M S",
	},
	{
		"S M",
		" A ",
		"S M",
	},
	{
		"M M",
		" A ",
		"S S",
	},
	{
		"S S",
		" A ",
		"M M",
	},
}

// find the string "MAS" in the shape of an X centered on the A at x, y
func (s *Part2Solver) findMas(x int, y int) int {
	count := 0
	// if we're out of bounds, die
	if x < 0 || x >= s.width || y < 0 || y >= s.height {
		log.Fatalf("out of bounds: %v, %v", x, y)
	}

	// if we're on an edge, we can't find MAS
	if x == 0 || x == s.width-1 || y == 0 || y == s.height-1 {
		return 0
	}

	// if the center isn't an A, we can't find MAS
	if s.getRune(x, y) != 'A' {
		return 0
	}

	// Test each pattern centered on the A
	for _, pattern := range patterns {
		if s.matchPattern(x, y, pattern) {
			log.Debugf("found MAS at %v, %v", x, y)
			log.Debugf("%c%c%c", s.getRune(x-1, y-1), s.getRune(x, y-1), s.getRune(x+1, y-1))
			log.Debugf("%c%c%c", s.getRune(x-1, y), s.getRune(x, y), s.getRune(x+1, y))
			log.Debugf("%c%c%c", s.getRune(x-1, y+1), s.getRune(x, y+1), s.getRune(x+1, y+1))
			count += 1
		}
	}

	return count
}

func (s *Part2Solver) matchPattern(x int, y int, pattern []string) bool {
	for dy, line := range pattern {
		for dx, r := range line {
			if r != ' ' && s.getRune(x+dx-1, y+dy-1) != rune(r) {
				return false
			}
		}
	}

	return true
}
