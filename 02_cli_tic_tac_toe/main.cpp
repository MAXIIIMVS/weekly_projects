#include <cstddef>
#include <cstdio>
#include <iostream>
#include <limits>
#include <print>

class TicTacToe {
public:
  void play() {
    while (!is_game_over()) {
      clear_screen();
      draw_board();

      int choice{};
      std::print("Player {}, enter your choice (1-9): ", _turn);
      std::cin >> choice;
      // FIX: code breaks when entering <C-D> instead of an index
      if (std::cin.fail() || (choice < 1 || choice > 9) ||
          _board[choice - 1] != 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }

      _board[choice - 1] = _turn;
      if (did_player_win()) {
        clear_screen();
        draw_board();
        std::println("Player {} won!", _turn);
        return;
      }
      _turn = _turn == 1 ? 2 : 1;
    }
    clear_screen();
    draw_board();
    std::println("It's a draw!");
  }

  void clear_screen() { std::cout << "\033[2J\033[1;1H"; }

  bool is_game_over() const {
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

  void draw_board(int cell_width = 5) const {
    std::println("+{0:-^{1}}+{0:-^{1}}+{0:-^{1}}+", "", cell_width);
    for (std::size_t i = 0; i < 9; ++i) {
      if (i % 3 == 0) { // first column
        std::print("|");
      }

      std::print("{0:^{1}}|",
                 _board[i] == 1   ? 'X'
                 : _board[i] == 2 ? 'O'
                                  : ' ',
                 cell_width);

      if ((i + 1) % 3 == 0) { // last column
        std::println("\n+{0:-^{1}}+{0:-^{1}}+{0:-^{1}}+", "", cell_width);
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
