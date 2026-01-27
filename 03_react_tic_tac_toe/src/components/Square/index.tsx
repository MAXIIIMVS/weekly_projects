import type { FC, MouseEventHandler } from "react";
import "./Square.css";

export type SquareValue = "X" | "O" | null;

interface SquareProps {
  disabled?: boolean;
  value: SquareValue;
  onSquareClick: MouseEventHandler<HTMLButtonElement>;
}

const Square: FC<SquareProps> = ({ disabled, value, onSquareClick }) => {
  return (
    <button disabled={disabled} className="square" onClick={onSquareClick}>
      {value}
    </button>
  );
};

export default Square;
