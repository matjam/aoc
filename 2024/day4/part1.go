package day4

import (
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/api"
)

type Part1Solver struct {
	Input string

	grid   []string
	width  int
	height int
}

func (s *Part1Solver) Run() {
	log.Info("🕵️ solving for day 4 part 1")

	var err error
	s.Input, err = api.GetInput(4)
	if err != nil {
		log.Fatal("💣 oopsie woopsie we did a little fucky wucky 💣")
	}

	result := s.Solve()

	log.Infof("🎄 day 4 part 1 result: %v", result)
}

func (s *Part1Solver) Solve() int {
	s.grid = strings.Split(s.Input, "\n")
	s.width = len(s.grid[0])
	s.height = len(s.grid)

	count := 0

	log.Debugf("width: %v, height: %v", s.width, s.height)

	for y := 0; y < s.height; y++ {
		for x := 0; x < s.width; x++ {
			for d := North; d <= NorthWest; d++ {
				if s.findXmas(x, y, d) {
					count++
				}
			}
		}
	}

	return count
}

func (s *Part1Solver) getRune(x int, y int) rune {
	if x < 0 || x >= s.width || y < 0 || y >= s.height {
		return ' '
	}

	return rune(s.grid[y][x])
}

// find the string XMAS in the grid starting at x, y and moving in the given direction
func (s *Part1Solver) findXmas(x int, y int, direction Direction) bool {
	// if we're out of bounds, die
	if x < 0 || x >= s.width || y < 0 || y >= s.height {
		log.Fatalf("out of bounds: %v, %v", x, y)
	}

	if direction == North {
		if s.getRune(x, y) == 'X' && s.getRune(x, y-1) == 'M' && s.getRune(x, y-2) == 'A' && s.getRune(x, y-3) == 'S' {
			return true
		}
	} else if direction == NorthEast {
		if s.getRune(x, y) == 'X' && s.getRune(x+1, y-1) == 'M' && s.getRune(x+2, y-2) == 'A' && s.getRune(x+3, y-3) == 'S' {
			return true
		}
	} else if direction == East {
		if s.getRune(x, y) == 'X' && s.getRune(x+1, y) == 'M' && s.getRune(x+2, y) == 'A' && s.getRune(x+3, y) == 'S' {
			return true
		}
	} else if direction == SouthEast {
		if s.getRune(x, y) == 'X' && s.getRune(x+1, y+1) == 'M' && s.getRune(x+2, y+2) == 'A' && s.getRune(x+3, y+3) == 'S' {
			return true
		}
	} else if direction == South {
		if s.getRune(x, y) == 'X' && s.getRune(x, y+1) == 'M' && s.getRune(x, y+2) == 'A' && s.getRune(x, y+3) == 'S' {
			return true
		}
	} else if direction == SouthWest {
		if s.getRune(x, y) == 'X' && s.getRune(x-1, y+1) == 'M' && s.getRune(x-2, y+2) == 'A' && s.getRune(x-3, y+3) == 'S' {
			return true
		}
	} else if direction == West {
		if s.getRune(x, y) == 'X' && s.getRune(x-1, y) == 'M' && s.getRune(x-2, y) == 'A' && s.getRune(x-3, y) == 'S' {
			return true
		}
	} else if direction == NorthWest {
		if s.getRune(x, y) == 'X' && s.getRune(x-1, y-1) == 'M' && s.getRune(x-2, y-2) == 'A' && s.getRune(x-3, y-3) == 'S' {
			return true
		}
	}

	return false
}
