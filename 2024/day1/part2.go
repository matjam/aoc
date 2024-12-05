package day1

import (
	"bufio"
	"sort"
	"strconv"
	"strings"

	"github.com/charmbracelet/log"
	"github.com/matjam/aoc/2024/api"
	"github.com/matjam/aoc/2024/registry"
)

func init() {
	registry.Register(1, 2, Part2Solver{})
}

type Part2Solver struct{}

func (s Part2Solver) Run() {
	log.Info("🕵️ solving for day 1 part 2")

	input, err := api.GetInput(1)
	if err != nil {
		log.Fatal("💣 oopsie woopsie we did a little fucky wucky 💣")
	}

	totalDistance := s.Solve(input)

	log.Infof("🎄 day 1 part 2 result: %v", totalDistance)
}

func (s Part2Solver) Solve(input string) int {
	list1 := make([]int, 0)
	list2 := make([]int, 0)

	scanner := bufio.NewScanner(strings.NewReader(input))
	for scanner.Scan() {
		line := scanner.Text()
		nums := strings.Split(line, "   ") // all the numbers are split by 3 spaces
		if len(nums) != 2 {
			log.Fatalf("💣 did not expect string with this format [%v]", line)
		}
		num1, err := strconv.Atoi(nums[0])
		if err != nil {
			log.Fatalf("💣 couldn't convert [%v] to int: %v", nums[0], err.Error())
		}
		list1 = append(list1, num1)

		num2, err := strconv.Atoi(nums[1])
		if err != nil {
			log.Fatalf("💣 couldn't convert [%v] to int: %v", nums[1], err.Error())
		}
		list2 = append(list2, num2)
	}

	log.Infof("💡 loaded two lists with %v numbers each", len(list1))

	// process the lists
	sort.Ints(list1)

	list2map := make(map[int]int)
	for _, num := range list2 {
		if v, ok := list2map[num]; ok {
			v += 1
			list2map[num] = v
		} else {
			list2map[num] = 1
		}
	}

	totalDistance := 0

	for _, num := range list1 {
		// multiply each number in the first list by the number of times it appears in the second list
		if count, ok := list2map[num]; ok {
			totalDistance += num * count
		}
	}

	return totalDistance
}
