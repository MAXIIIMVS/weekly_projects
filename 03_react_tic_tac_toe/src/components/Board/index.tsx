import { useState } from "react";
import Square, { type SquareValue } from "../Square";
import "./Board.css";

const Board = () => {
  const [squares, setSquares] = useState<SquareValue[]>(Array(9).fill(null));
  const xTurn = squares.filter(Boolean).length % 2 === 0;
  const playerTurn = `Next player: ${xTurn ? "X" : "O"} `;
  const winner = findWinner(squares);
  const isDrawn = !winner && squares.every((v) => v !== null);

  function handleSquareClick(squareIndex: number) {
    if (squares[squareIndex]) {
      return;
    }
    const updatedSquares = squares.slice();
    updatedSquares[squareIndex] = xTurn ? "X" : "O";
    setSquares(updatedSquares);
  }

  function resetGame() {
    setSquares(Array(9).fill(null));
  }

  return (
    <>
      <div className="status-bar">
        <p>
          {winner ? `Player ${winner} won!` : isDrawn ? "DRAW" : playerTurn}
        </p>
        <button
          className="reset-button"
          onClick={resetGame}
          style={{ visibility: winner || isDrawn ? "visible" : "hidden" }}
        >
          Reset
        </button>
      </div>
      <div className="board">
        {squares.map((value, i) => (
          <Square
            key={i}
            disabled={!!winner || isDrawn}
            value={value}
            onSquareClick={() => handleSquareClick(i)}
          />
        ))}
      </div>
    </>
  );
};

function findWinner(squares: readonly SquareValue[]): SquareValue {
  const indices = [
    [0, 1, 2],
    [3, 4, 5],
    [6, 7, 8],
    [0, 3, 6],
    [1, 4, 7],
    [2, 5, 8],
    [0, 4, 8],
    [2, 4, 6],
  ];
  for (let i = 0; i < indices.length; ++i) {
    const [a, b, c] = indices[i];
    if (squares[a] && squares[a] === squares[b] && squares[a] === squares[c]) {
      return squares[a];
    }
  }
  return null;
}

export default Board;
