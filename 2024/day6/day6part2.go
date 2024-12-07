package day6

import (
	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/util"
)

type Location struct {
	X, Y int
}

type Part2Solver struct {
	Input string
	Bot   *GridBot
}

func (s *Part2Solver) Run() {
	s.Input = util.GetInput(6, 2)
	log.Infof("🎄 day 6 part 1 result: %v", s.Solve())
}

func (s *Part2Solver) Solve() int {
	// First find all the places the bot will visit unrestrained.

	grid := NewGridFromString(s.Input)
	locations := make([]Location, 0)
	loopLocations := make([]Location, 0)
	s.CheckLoop(grid) // we know this won't loop the first time, but we need to find the locations it visits

	for y, row := range grid.Cells {
		for x, v := range row {
			if v == 'X' {
				locations = append(locations, Location{X: x, Y: y})
			}
		}
	}

	log.Debugf("🤖 Visited %v locations not including the start", len(locations))

	// put an obstacle in each of the locations the bot visited, running
	// the bot each time to see if it hits an obstacle (loops)

	for i, loc := range locations {
		grid := NewGridFromString(s.Input) // seems expensive
		grid.Set(loc.X, loc.Y, 'O')
		if s.CheckLoop(grid) {
			loopLocations = append(loopLocations, loc)
			log.Infof("🤖 %v/%v Looping at %v", i, len(locations), loc)
		} else {
			log.Infof("🤖 %v/%v Didn't loop at %v", i, len(locations), loc)
		}
	}

	log.Infof("🤖 Found %v loop locations", len(loopLocations))

	return len(loopLocations)
}

func (s *Part2Solver) CheckLoop(grid *Grid) bool {
	hitObstacle := false

	bot := NewGridBot(0, 0, North, grid)

	// Runs the bot and returns a list of all the locations it visited
	bot.X, bot.Y = grid.Find('^')
	bot.D = North
	bot.hitObstacle = false

	for {
		log.Debugf("🤖 %v %v %v\n%v", bot.X, bot.Y, bot.D, grid)

		// move forward unless you hit a wall or obstacle, or walk off the grid
		bot.Forward()

		if bot.OutOfBounds() {
			return false
		}

		if bot.HitObstacle() && hitObstacle {
			return true
		}

		if bot.HitObstacle() {
			hitObstacle = true
		}
	}
}
