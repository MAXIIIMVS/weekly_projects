#include <cstddef>
#include <iostream>
#include <print>

class TicTacToe {
public:
  void play() {
    while (true) {
      clear_screen();
      draw_board();

      int choice{0};
      std::print("Player {}, enter your choice: ", _turn);
      std::cin >> choice;
      if (choice < 1 || choice > 9) {
        continue;
      }
      if (_board[choice - 1] != 0) {
        continue;
      }

      _board[choice - 1] = _turn;
      if (did_player_win()) {
        clear_screen();
        draw_board();
        std::println("Player {} won!", _turn);
        return;
      }
      if (is_game_draw()) {
        clear_screen();
        draw_board();
        std::println("It's a draw!");
        return;
      }
      _turn = _turn == 1 ? 2 : 1;
    }
  }

  void clear_screen() { std::cout << "\033[2J\033[1;1H"; }

  bool is_game_draw() const {
    for (int i = 0; i < 9; ++i) {
      if (_board[i] == 0) { // there's more to play
        return false;
      }
    }
    return true;
  }

  bool did_player_win() const {
    return (_board[0] == _turn && _board[1] == _turn && _board[2] == _turn) ||
           (_board[3] == _turn && _board[4] == _turn && _board[5] == _turn) ||
           (_board[6] == _turn && _board[7] == _turn && _board[8] == _turn) ||
           (_board[0] == _turn && _board[3] == _turn && _board[6] == _turn) ||
           (_board[1] == _turn && _board[4] == _turn && _board[7] == _turn) ||
           (_board[2] == _turn && _board[5] == _turn && _board[8] == _turn) ||
           (_board[0] == _turn && _board[4] == _turn && _board[8] == _turn) ||
           (_board[2] == _turn && _board[4] == _turn && _board[6] == _turn);
  }

  void draw_board() const {
    std::println("+---+---+---+");
    for (std::size_t i = 0; i < 9; ++i) {
      if (i % 3 == 0) { // first column
        std::print("|");
      }

      std::printf(" %c |", _board[i] == 1 ? 'X' : _board[i] == 2 ? 'O' : ' ');

      if ((i + 1) % 3 == 0) { // last column
        std::println("\n+---+---+---+");
      }
    }
  }

private:
  // 1 means player 1 and 2 means player 2
  int _turn{1};
  // 1 means player 1 and 2 means player 2 - 0 is empty
  int _board[9]{0};
};

int main() {
  TicTacToe game;
  game.play();

  return 0;
}
