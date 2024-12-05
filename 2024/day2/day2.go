package day2

import "github.com/matjam/aoc/2024/util"

type Direction int

const (
	UNKNOWN Direction = iota
	INCREASING
	DECREASING
)

func isSafe(levels []string) (safe bool) {
	safe = true
	var direction Direction
	var i, a, b, distance int
	var num string
	for i, num = range levels {
		if i == 0 {
			continue
		}
		b = util.ToInt(num)
		a = util.ToInt(levels[i-1])

		// check if anything is changing too quickly
		distance = util.IntDistance(a, b)
		if distance > 3 || distance == 0 {
			safe = false
			break
		}

		if a < b {
			if direction == UNKNOWN {
				direction = INCREASING
			} else if direction == DECREASING {
				safe = false
				break
			}
		}

		if a > b {
			if direction == UNKNOWN {
				direction = DECREASING
			} else if direction == INCREASING {
				safe = false
				break
			}
		}
	}

	return safe
}
