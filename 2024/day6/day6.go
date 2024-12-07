package day6

import (
	"fmt"
	"strings"

	"github.com/charmbracelet/log"

	"github.com/matjam/aoc/2024/registry"
)

func init() {
	registry.Register(6, 1, &Part1Solver{})
	registry.Register(6, 2, &Part2Solver{})
}

type Direction int

const (
	North Direction = iota
	East
	South
	West
)

func (d Direction) TurnRight() Direction {
	return (d + 1) % 4
}

func (d Direction) String() string {
	return [...]string{"North", "East", "South", "West"}[d]
}

type Grid struct {
	Width  int
	Height int

	Cells [][]byte
}

func NewGrid(width, height int) *Grid {
	cells := make([][]byte, height)
	for i := range cells {
		cells[i] = make([]byte, width)
	}

	return &Grid{
		Width:  width,
		Height: height,
		Cells:  cells,
	}
}

func NewGridFromString(s string) *Grid {
	rows := strings.Split(s, "\n")
	height := len(rows)
	width := len(rows[0])

	grid := NewGrid(width, height)

	for y, row := range rows {
		for x, r := range row {
			grid.Cells[y][x] = byte(r)
		}
	}

	return grid
}

func (g *Grid) Copy() *Grid {
	grid := NewGrid(g.Width, g.Height)

	for y, row := range g.Cells {
		for x, r := range row {
			grid.Cells[y][x] = r
		}
	}

	return grid
}

func (g *Grid) Get(x, y int) byte {
	if y < 0 || y >= g.Height || x < 0 || x >= g.Width {
		return ' '
	}

	return g.Cells[y][x]
}

func (g *Grid) Set(x, y int, v byte) {
	if y < 0 || y >= g.Height || x < 0 || x >= g.Width {
		return
	}

	g.Cells[y][x] = v
}

func (g *Grid) Find(r byte) (int, int) {
	for y, row := range g.Cells {
		for x, v := range row {
			if v == r {
				return x, y
			}
		}
	}
	return -1, -1
}

func (g *Grid) Look(x, y int, d Direction) byte {
	if d == North {
		return g.Get(x, y-1)
	}
	if d == East {
		return g.Get(x+1, y)
	}
	if d == South {
		return g.Get(x, y+1)
	}
	if d == West {
		return g.Get(x-1, y)
	}

	log.Fatalf("invalid direction: %v", d)
	return ' '
}

func (g *Grid) SetAhead(x, y int, d Direction, b byte) {
	if d == North {
		g.Set(x, y-1, b)
	}
	if d == East {
		g.Set(x+1, y, b)
	}
	if d == South {
		g.Set(x, y+1, b)
	}
	if d == West {
		g.Set(x-1, y, b)
	}
}

func (g *Grid) Count(r byte) int {
	count := 0
	for _, row := range g.Cells {
		for _, v := range row {
			if v == r {
				count++
			}
		}
	}
	return count
}

func (g *Grid) String() string {
	var sb strings.Builder
	for _, row := range g.Cells {
		sb.Write(row)
		sb.WriteByte('\n')
	}
	return sb.String()
}

type GridBot struct {
	X, Y int
	D    Direction

	hitObstacle bool

	Grid *Grid
}

func NewGridBot(x, y int, d Direction, g *Grid) *GridBot {
	return &GridBot{
		X:    x,
		Y:    y,
		D:    d,
		Grid: g,
	}
}

func (b *GridBot) Forward() {
	lookAhead := b.Grid.Look(b.X, b.Y, b.D)

	if lookAhead == '#' || lookAhead == 'O' {
		b.Grid.SetAhead(b.X, b.Y, b.D, 'O')
		b.D = b.D.TurnRight()
	} else {
		b.X, b.Y = b.NextPosition()
	}

	b.hitObstacle = lookAhead == 'O'

	b.Grid.Set(b.X, b.Y, 'X')
}

func (b *GridBot) NextPosition() (int, int) {
	if b.D == North {
		return b.X, b.Y - 1
	}
	if b.D == East {
		return b.X + 1, b.Y
	}
	if b.D == South {
		return b.X, b.Y + 1
	}
	if b.D == West {
		return b.X - 1, b.Y
	}

	log.Fatalf("invalid direction: %v", b.D)
	return -1, -1
}

func (b *GridBot) OutOfBounds() bool {
	return b.X < 0 || b.X >= b.Grid.Width || b.Y < 0 || b.Y >= b.Grid.Height
}

func (b *GridBot) String() string {
	return fmt.Sprintf("🤖 %v at %v, %v", b.D, b.X, b.Y)
}

func (b *GridBot) HitObstacle() bool {
	return b.hitObstacle
}
