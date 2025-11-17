#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

const int kWidth = Board::kBoardWidth;
const int kHeight = Board::kBoardHeight;
void InitBoard(Board& b) {
  for (int row = 0; row < kHeight; row++) {
    for (int col = 0; col < kWidth; col++) {
      b.board[row][col] = DiskType::kEmpty;
    }
  }
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (col >= kWidth || col < 0) {
    throw std::runtime_error("Invalid column index");
  }
  if (b.board[kHeight - 1][col] != DiskType::kEmpty) {
    throw std::runtime_error("Column is full");
  }
  for (int row = 0; row < kHeight; row++) {
    if (b.board[row][col] == DiskType::kEmpty) {
      b.board[row][col] = disk;
      return;
    }
  }
}

bool CheckForWinner(Board& b, DiskType disk) {
  bool ver = SearchForWinner(b, disk, WinningDirection::kVertical);
  bool hor = SearchForWinner(b, disk, WinningDirection::kHorizontal);
  bool ldiag = SearchForWinner(b, disk, WinningDirection::kLeftDiag);
  bool rdiag = SearchForWinner(b, disk, WinningDirection::kRightDiag);
  return ver || hor || ldiag || rdiag;
}

bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    return CheckHor(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    return CheckVer(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    return CheckLeftDiag(b, disk);
  }
  return CheckRightDiag(b, disk);
}

bool CheckHor(Board& b, DiskType disk) {
  for (int row = 0; row < kHeight; row++) {
    for (int col = 0; col < kWidth - 3; col++) {
      if (b.board[row][col] != DiskType::kEmpty) {
        if (b.board[row][col] == disk && b.board[row][col + 1] == disk &&
            b.board[row][col + 2] == disk && b.board[row][col + 3] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool CheckVer(Board& b, DiskType disk) {
  for (int col = 0; col < kWidth; col++) {
    for (int row = 0; row < kHeight - 3; row++) {
      if (b.board[row][col] != DiskType::kEmpty) {
        if (b.board[row][col] == disk && b.board[row + 1][col] == disk &&
            b.board[row + 2][col] == disk && b.board[row + 3][col] == disk) {
          return true;
        }
      }
    }
  }
  return false;
}

bool CheckLeftDiag(Board& b, DiskType disk) {
  for (int col = 3; col < kWidth; col++) {
    int row = 0;
    for (int i = row; i < kHeight; i++) {
      for (int j = col; j >= 3; j--) {
        if (b.board[i][j] != DiskType::kEmpty) {
          if (b.board[i][j] == disk && b.board[i + 1][j - 1] == disk &&
              b.board[i + 2][j - 2] == disk && b.board[i + 3][j - 3] == disk) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool CheckRightDiag(Board& b, DiskType disk) {
  for (int col = 3; col >= 0; col--) {
    int row = 0;
    for (int i = row; i < kHeight; i++) {
      for (int j = col; j < kWidth; j++) {
        if (b.board[i][j] != DiskType::kEmpty) {
          if (b.board[i][j] == disk && b.board[i + 1][j + 1] == disk &&
              b.board[i + 2][j + 2] == disk && b.board[i + 3][j + 3] == disk) {
            return true;
          }
        }
      }
    }
  }
  return false;
}

bool BoardLocationInBounds(int row, int col) {
  return row < kHeight && row >= 0 && col < kWidth && col >= 0;
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}