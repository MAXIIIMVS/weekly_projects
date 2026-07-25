package main

import (
	"fmt"
	"log"
	"math/rand"
	"time"
)

type Game struct {
	rows, cols int
	world      [][]bool // front buffer
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
		world: make([][]bool, rows),
		back:  make([][]bool, rows),
	}
	for i := range g.world {
		g.world[i] = make([]bool, cols)
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
		g.world[rand.Intn(g.rows)][rand.Intn(g.cols)] = true
	}
}

func (g *Game) show() {
	for r := 0; r < g.rows; r++ {
		for c := 0; c < g.cols; c++ {
			if g.world[r][c] {
				fmt.Print("")
			} else {
				fmt.Print(" ")
			}
		}
		fmt.Println()
	}
}

// verify exits the program if row and col are out of range
func (g *Game) verify(row, col int) {
	// return x >= 0 && y >= 0 && x < g.rows && y < g.cols
	if row < 0 || col < 0 || row >= g.rows || col >= g.cols {
		log.Fatalf("invalid values for x, and y: %d, %d", row, col)
	}
}

// isValid checks if row and col are in range of the front buffer
func (g *Game) isValid(row, col int) bool {
	return row >= 0 && col >= 0 && row < g.rows && col < g.cols
}

// swap swaps front and back buffers
func (g *Game) swap() {
	g.world, g.back = g.back, g.world
}

func (g *Game) isAlive(row, col int) bool {
	return g.world[row][col]
}

func (g *Game) liveNeighborCount(row, col int) int {
	g.verify(row, col)
	liveNeighbors := 0
	if g.isValid(row-1, col-1) && g.isAlive(row-1, col-1) {
		liveNeighbors++
	}
	if g.isValid(row-1, col) && g.isAlive(row-1, col) {
		liveNeighbors++
	}
	if g.isValid(row-1, col+1) && g.isAlive(row-1, col+1) {
		liveNeighbors++
	}
	if g.isValid(row, col-1) && g.isAlive(row, col-1) {
		liveNeighbors++
	}
	if g.isValid(row, col+1) && g.isAlive(row, col+1) {
		liveNeighbors++
	}
	if g.isValid(row+1, col-1) && g.isAlive(row+1, col-1) {
		liveNeighbors++
	}
	if g.isValid(row+1, col) && g.isAlive(row+1, col) {
		liveNeighbors++
	}
	if g.isValid(row+1, col+1) && g.isAlive(row+1, col+1) {
		liveNeighbors++
	}
	return liveNeighbors
}

// update updates the back buffer based on the rules of Conway's Game of Life,
// and swaps the front and back buffer and returns if the world was updated or
// not, (false means the world didn't update (i.e. game over)).
func (g *Game) update() bool {
	/* Rules:
	 * A live cell with less than two live neighbors dies.
	 * A live cell with two or three live neighbors lives on to the next
	 * generation.
	 * A live cell with more than three live neighbors dies.
	 * A dead cell with exactly three live neighbors becomes a live cell.
	 */
	didWorldUpdate := false
	for i, r := range g.world {
		for j, alive := range r {
			// TODO: wrap around
			n := g.liveNeighborCount(i, j)
			g.back[i][j] = n == 3 || n == 2 && alive
			if !didWorldUpdate {
				didWorldUpdate = g.back[i][j] != alive
			}
		}
	}
	g.swap()
	return didWorldUpdate
}

func clearScreen() { fmt.Print("\033[2J\033[1;1H") }

func main() {
	game := NewGame(40, 70)
	game.randomize(50)
	for {
		didWorldStop := !game.update()
		game.show()
		if didWorldStop {
			fmt.Println("the world didn't change. stopping the game")
			break
		}
		time.Sleep(time.Second / 60)
		clearScreen()
	}
}
