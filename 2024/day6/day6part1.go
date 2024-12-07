package day6

import (
	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/util"
)

type Part1Solver struct {
	Input string

	grid *Grid
	bot  *GridBot
}

func (s *Part1Solver) Run() {
	s.Input = util.GetInput(6, 1)
	log.Infof("🎄 day 6 part 1 result: %v", s.Solve())
}

func (s *Part1Solver) Solve() int {
	s.grid = NewGridFromString(s.Input)
	s.bot = NewGridBot(0, 0, North, s.grid)
	s.bot.X, s.bot.Y = s.grid.Find('^')

	log.Infof("🤖 Starting at %v, %v", s.bot.X, s.bot.Y)

	for {
		// Set the current cell to a X character
		s.grid.Set(s.bot.X, s.bot.Y, 'X')

		// move forward unless you hit a # character or walk off the map
		s.bot.Forward()

		if s.bot.OutOfBounds() {
			break
		}
	}

	log.Infof("🤖 Finished at %v, %v", s.bot.X, s.bot.Y)

	log.Debugf("🎄 Grid:\n%v", s.grid.String())

	return s.grid.Count('X')
}
