package main

import (
	"fmt"
	"log"
	"math/rand"
	"time"
)

type Game struct {
	rows, cols int
	front      [][]bool // front buffer
	back       [][]bool // back buffer
}

// NewGame populates a Game struct and returns it.
func NewGame(rows, cols int) Game {
	if rows <= 0 || cols <= 0 {
		log.Fatal("rows and cols should be positive integers")
	}
	g := Game{
		rows:  rows,
		cols:  cols,
		front: make([][]bool, rows),
		back:  make([][]bool, rows),
	}
	for i := range g.front {
		g.front[i] = make([]bool, cols)
		g.back[i] = make([]bool, cols)
	}
	return g
}

// randomize sets a percentage of cells to true, randomly.
// NOTE: percentage should be in (0, 100] range.
// NOTE: the number of cells set to a random value, might be less than provided
// percentage.
func (g *Game) randomize(percentage int) {
	if percentage <= 0 || percentage > 100 {
		log.Fatal("provided percentage value should be in (0, 100] range")
	}
	for range g.rows * g.cols / (100 / percentage) {
		g.front[rand.Intn(g.rows)][rand.Intn(g.cols)] = true
	}
}

func (g *Game) show() {
	for r := 0; r < g.rows; r++ {
		for c := 0; c < g.cols; c++ {
			if g.front[r][c] {
				fmt.Print("*")
			} else {
				fmt.Print(".")
			}
		}
		fmt.Println()
	}
}

func clearScreen() { fmt.Print("\033[2J\033[1;1H") }

func main() {
	game := NewGame(3, 4)
	game.randomize(25)
	fmt.Println(game.front)
	for {
		// TODO: update game
		game.show()
		time.Sleep(100 * time.Millisecond)
		clearScreen()
	}
}
