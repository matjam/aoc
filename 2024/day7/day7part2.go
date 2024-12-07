package day7

import (
	"bufio"
	"fmt"
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/util"
)

type Part2Solver struct {
	Input string
}

func (s *Part2Solver) Run() {
	s.Input = util.GetInput(7, 1)
	log.Infof("🎄 day 7 part 1 result: %v", s.Solve())
}

func (s *Part2Solver) Solve() int {
	total := 0

	scanner := bufio.NewScanner(strings.NewReader(s.Input))
	for scanner.Scan() {
		log.Infof("total: %v line: %v", total, scanner.Text())

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

func (s *Part2Solver) IsSolvable(result int, operands []int) bool {
	calculations := make([]Calculation, len(operands))

	for i, o := range operands {
		calculations[i] = Calculation{operator: '+', operand: o}
	}

	for {
		calculated := calculateWithConcatenation(calculations)

		if calculated == result {
			return true
		}

		more := NextCombinationWithConcatenation(calculations)
		if !more {
			break
		}
	}

	return false
}

// we support +, * and . operators. The . operator is concatenation
// which takes the digits and concatenates them together to make a new number
func NextCombinationWithConcatenation(calculations []Calculation) bool {
	for i := len(calculations) - 1; i >= 1; i-- {
		if calculations[i].operator == '+' {
			calculations[i].operator = '*'
			return true
		}

		if calculations[i].operator == '*' {
			calculations[i].operator = '.'
			return true
		}

		calculations[i].operator = '+'
	}

	return false
}

func calculateWithConcatenation(calculations []Calculation) int {
	result := 0
	for _, c := range calculations {
		switch c.operator {
		case '+':
			result += c.operand
		case '*':
			result *= c.operand
		case '.':
			resultString := fmt.Sprintf("%v%v", result, c.operand)
			result = util.ToInt(resultString)
		}
	}

	log.Debugf("calculated: %v: %v", calculations, result)

	return result
}
