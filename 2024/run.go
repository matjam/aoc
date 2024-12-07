package main

import (
	"os"
	"strconv"

	"github.com/charmbracelet/log"
	"github.com/joho/godotenv"
	"github.com/matjam/aoc/2024/registry"

	_ "github.com/matjam/aoc/2024/day1"
	_ "github.com/matjam/aoc/2024/day2"
	_ "github.com/matjam/aoc/2024/day3"
	_ "github.com/matjam/aoc/2024/day4"
	_ "github.com/matjam/aoc/2024/day5"
	_ "github.com/matjam/aoc/2024/day6"
	_ "github.com/matjam/aoc/2024/day7"
)

var CLI struct {
	Day int `arg:""`
}

func main() {
	log.Info("🎄 Bootstrapping AOC 2024! 🎄")
	registry.LogSolvers()

	err := godotenv.Load()
	if err != nil {
		log.Error("😭 Couldn't load the .env file: %w", err)
	}

	if os.Getenv("DEBUG") != "" {
		log.SetLevel(log.DebugLevel)
	}

	if len(os.Args) != 3 {
		log.Fatal("🎄 Provide 2 numbers indicating which day and part you wish to solve for.")
	}

	day, err := strconv.Atoi(os.Args[1])
	if err != nil {
		log.Fatalf("😭 provided day was not an integer: %v", err.Error())
	}

	part, err := strconv.Atoi(os.Args[2])
	if err != nil {
		log.Fatalf("😭 provided part was not an integer: %v", err.Error())
	}

	solver := registry.GetSolver(day, part)
	if solver == nil {
		log.Fatalf("😭 no solver implemented for day %v", day)
	}
	solver.Run()
}
