package registry

import (
	"fmt"

	"github.com/charmbracelet/log"
)

type Solver interface {
	Run()
}

var solvers map[string]Solver

func Register(day int, part int, solver Solver) {
	if solvers == nil {
		solvers = make(map[string]Solver)
	}

	if _, ok := solvers[key(day, part)]; ok {
		log.Fatalf("💣 attempt to register day %v part %v twice", day, part)
	}

	solvers[key(day, part)] = solver
	log.Infof("✨ registered solver for day %v part %v", day, part)
}

func GetSolver(day int, part int) Solver {
	return solvers[key(day, part)]
}

func key(day int, part int) string {
	return fmt.Sprintf("day %v part %v", day, part)
}
