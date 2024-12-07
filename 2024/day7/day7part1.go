package day7

import (
	"bufio"
	"fmt"
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/util"
)

type Part1Solver struct {
	Input string
}

func (s *Part1Solver) Run() {
	s.Input = util.GetInput(7, 1)
	log.Infof("🎄 day 7 part 1 result: %v", s.Solve())
}

func (s *Part1Solver) Solve() int {
	total := 0

	scanner := bufio.NewScanner(strings.NewReader(s.Input))
	for scanner.Scan() {
		line := scanner.Text()
		if line == "" {
			break
		}
		parts := strings.Split(line, ": ")
		result := util.ToInt(parts[0])
		operands := util.ToInts(strings.Split(parts[1], " "))

		if s.IsSolvable(result, operands) {
			total += result
		}
	}

	return total
}

type Calculation struct {
	operator rune
	operand  int
}

func (c Calculation) String() string {
	return fmt.Sprintf("%c %v", c.operator, c.operand)
}

func NextCombination(calculations []Calculation) bool {
	for i := len(calculations) - 1; i >= 1; i-- {
		if calculations[i].operator == '+' {
			calculations[i].operator = '*'
			return true
		}
		calculations[i].operator = '+'
	}

	return false
}

func (s *Part1Solver) IsSolvable(result int, operands []int) bool {
	calculations := make([]Calculation, len(operands))

	for i, o := range operands {
		calculations[i] = Calculation{operator: '+', operand: o}
	}

	for {
		calculated := calculate(calculations)

		if calculated == result {
			return true
		}

		more := NextCombination(calculations)
		if !more {
			break
		}
	}

	return false
}

func calculate(calculations []Calculation) int {
	result := 0
	for _, c := range calculations {
		switch c.operator {
		case '+':
			result += c.operand
		case '*':
			result *= c.operand
		}
	}

	log.Debugf("calculated: %v: %v", calculations, result)

	return result
}
