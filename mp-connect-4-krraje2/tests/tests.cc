// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

Board b;
const int kWidth = Board::kBoardWidth;
// const int kHeight = Board::kBoardHeight;

TEST_CASE("Disk Dropper", "Drop") {
  InitBoard(b);
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, 7));
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  REQUIRE(b.board[0][1] == DiskType::kPlayer1);
  DropDiskToBoard(b, DiskType::kPlayer1, 2);
  REQUIRE_FALSE(b.board[0][2] == DiskType::kEmpty);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  DropDiskToBoard(b, DiskType::kPlayer1, 1);
  REQUIRE_THROWS(DropDiskToBoard(b, DiskType::kPlayer1, 1));
}

// Helpers Checking + Winning checks
TEST_CASE("Win Checker -- Horizontal", "CheckHor") {
  SECTION("Starting from col O to col kWidth - 1") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, kWidth - 2);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kHorizontal) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kHorizontal) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, kWidth - 1);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
  SECTION("Winning is added in the middle") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kHorizontal) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kHorizontal) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
  SECTION("Middle win") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kHorizontal) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kHorizontal) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
  SECTION("Not to pass") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kHorizontal) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kHorizontal) == true);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == false);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    REQUIRE_FALSE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kHorizontal) == true);
    REQUIRE_FALSE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
}

TEST_CASE("Win Checker - Vertical", "CheckVer") {
  SECTION("Starting from row 0 to row 3") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kVertical) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kVertical) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kVertical) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kVertical) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kVertical) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
  SECTION("Winning is added in the middle") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kVertical) == false);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kVertical) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kVertical) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kVertical) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kVertical) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
  SECTION("Middle Win") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kVertical) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kVertical) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kVertical) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kVertical) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kVertical) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
  SECTION("Not to pass") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kVertical) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kVertical) == true);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kVertical) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kVertical) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kVertical) == false);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == false);
  }
}

TEST_CASE("Win Checker - Right Diag", "RDiag") {
  SECTION("Scenario 1 - Easy") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kRightDiag) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kRightDiag) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kRightDiag) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kRightDiag) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kRightDiag) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
  SECTION("Scenario 2 - Harder") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, kWidth - 2);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kRightDiag) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, kWidth - 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kRightDiag) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kRightDiag) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kRightDiag) == true);
    DropDiskToBoard(b, DiskType::kPlayer2, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer1, 4);
    DropDiskToBoard(b, DiskType::kPlayer2, 5);
    DropDiskToBoard(b, DiskType::kPlayer2, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 5);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    DropDiskToBoard(b, DiskType::kPlayer1, 6);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kRightDiag) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }

  SECTION("Middle Win") {
    InitBoard(b);
    b.board[2][2] = DiskType::kPlayer1;
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kRightDiag) == false);
    b.board[3][3] = DiskType::kPlayer1;
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kRightDiag) == true);
    b.board[4][4] = DiskType::kPlayer1;
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kRightDiag) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kRightDiag) == true);
    b.board[5][5] = DiskType::kPlayer1;
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kRightDiag) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
}

TEST_CASE("Win Checker - Left Diag", "LDiag") {
  SECTION("Scenario 1 - Easy") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kLeftDiag) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kLeftDiag) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kLeftDiag) == true);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kLeftDiag) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }

  SECTION("Scenario 2 - Harder") {
    InitBoard(b);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer2, 3);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kLeftDiag) == true);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kLeftDiag) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kLeftDiag) == true);
    DropDiskToBoard(b, DiskType::kPlayer2, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 3);
    DropDiskToBoard(b, DiskType::kPlayer2, 0);
    DropDiskToBoard(b, DiskType::kPlayer2, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 2);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    DropDiskToBoard(b, DiskType::kPlayer1, 1);
    DropDiskToBoard(b, DiskType::kPlayer1, 0);
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kLeftDiag) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
  SECTION("Middle Win") {
    InitBoard(b);
    b.board[1][4] = DiskType::kPlayer1;
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kLeftDiag) == false);
    b.board[2][3] = DiskType::kPlayer1;
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kLeftDiag) == true);
    b.board[3][2] = DiskType::kPlayer1;
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer1,
                                  WinningDirection::kLeftDiag) == true);
    REQUIRE_FALSE(SearchForWinner(b,
                                  DiskType::kPlayer2,
                                  WinningDirection::kLeftDiag) == true);
    b.board[4][1] = DiskType::kPlayer1;
    REQUIRE(SearchForWinner(
                b, DiskType::kPlayer1, WinningDirection::kLeftDiag) == true);
    REQUIRE(CheckForWinner(b, DiskType::kPlayer1) == true);
  }
}

TEST_CASE("Board Bounds Checker", "Board Check") {
  REQUIRE(BoardLocationInBounds(3, 6) == true);
  REQUIRE_FALSE(BoardLocationInBounds(7, 6) == true);
  REQUIRE_FALSE(BoardLocationInBounds(0, 9) == true);
  REQUIRE_FALSE(BoardLocationInBounds(-1, 6) == true);
  REQUIRE_FALSE(BoardLocationInBounds(3, -1) == true);
  REQUIRE(BoardLocationInBounds(0, 0) == true);
}
/////////////////////////////////////////////////////////////////////////////////////////////