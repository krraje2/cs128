// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"
#include <vector>
#include <string>

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Horizonal checker", "Horizonal") {
  SECTION("Full Row") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("hello");
    std::string word = "hello";
    REQUIRE(result.word == word);
  }
}

TEST_CASE("Vertical checker", "Vertical") {
  SECTION("First col") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("cat");
    REQUIRE(result.word == "cat");
  }
}

TEST_CASE("Left Diag checker", "LeftDiag") {
  SECTION("Last col") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("mat");
    REQUIRE(result.word == "mat");
  }
  SECTION("Middle") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("lle");
    REQUIRE(result.word == "lle");
    result = wss.FindWord("eh");
    REQUIRE(result.word == "eh");
    result = wss.FindWord("ulle");
    REQUIRE(result.word == "ulle");
    result = wss.FindWord("ulles");
    REQUIRE_FALSE(result.word == "ulles");
    result = wss.FindWord("ulbet");
    REQUIRE_FALSE(result.word == "ulbet");
  }

  SECTION("5 by 6") {
    std::vector<std::vector<char>> puzzle2{{'d', 'e', 'a', 'o', 'u', 'r'},
                                           {'h', 'e', 'l', 'l', 'o', 'l'},
                                           {'c', 'a', 'l', 'o', 'm', 'l'},
                                           {'a', 'e', 't', 'a', 'u', 'e'},
                                           {'t', 'e', 't', 'o', 'u', 'd'}};
    WordSearchSolver wss2(puzzle2);
    WordLocation result = wss2.FindWord("root");
    REQUIRE(result.word == "root");
    result = wss2.FindWord("lle");
    REQUIRE(result.word == "lle");
    result = wss2.FindWord("ulse");
    REQUIRE_FALSE(result.word == "ulse");
    result = wss2.FindWord("lmao");
    REQUIRE_FALSE(result.word == "lmao");
  }

  SECTION("6 by 4") {
      std::vector<std::vector<char>> puzzle2{{'d', 'e', 'a', 'o'},
                                           {'h', 'e', 'l', 'l'},
                                           {'c', 'a', 'l', 'o'},
                                           {'a', 'e', 't', 'a'},
                                           {'t', 'e', 't', 'o'},
                                           {'b', 'a', 'l', 'i'},
                                           {'w', 'e', 'r', 'e'}};
    WordSearchSolver wss2(puzzle2);
    WordLocation result = wss2.FindWord("ata");
    REQUIRE(result.word == "ata");
    result = wss2.FindWord("taw");
    REQUIRE(result.word == "taw");
    result = wss2.FindWord("oteb");
    REQUIRE(result.word == "oteb");
    result = wss2.FindWord("ara");
    REQUIRE_FALSE(result.word == "ara");
    result = wss2.FindWord("otes");
    REQUIRE_FALSE(result.word == "otes");
    result = wss2.FindWord("eh");
    REQUIRE(result.word == "eh");
  }
}

TEST_CASE("Right Diag checker", "RightDiag") {
  SECTION("First col") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("hat");
    REQUIRE(result.word == "hat");
  }
  SECTION("Middle") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation result = wss.FindWord("ela");
    REQUIRE(result.word == "ela");
    result = wss.FindWord("la");
    REQUIRE(result.word == "la");
  }

  SECTION("5 by 6") {
    std::vector<std::vector<char>> puzzle2

        {{'d', 'e', 'a', 'o', 'u', 'r'},
         {'h', 'e', 'l', 'l', 'o', 'l'},
         {'c', 'a', 'l', 'o', 'm', 'l'},
         {'a', 'e', 't', 'a', 'u', 'e'},
         {'t', 'e', 't', 'o', 'u', 'd'}};
    WordSearchSolver wss2(puzzle2);
    WordLocation result = wss2.FindWord("hat");
    REQUIRE(result.word == "hat");
    result = wss2.FindWord("elau");
    REQUIRE(result.word == "elau");
    result = wss2.FindWord("loud");
    REQUIRE(result.word == "loud");
    result = wss2.FindWord("load");
    REQUIRE_FALSE(result.word == "load");
    result = wss2.FindWord("oal");
    REQUIRE_FALSE(result.word == "oal");
    result = wss2.FindWord("elam");
    REQUIRE_FALSE(result.word == "elam");
  }

  SECTION("6 by 4") {
    std::vector<std::vector<char>> puzzle2

        {{'d', 'e', 'a', 'o'},
         {'h', 'e', 'l', 'l'},
         {'c', 'a', 'l', 'o'},
         {'a', 'e', 't', 'a'},
         {'t', 'e', 't', 'o'},
         {'b', 'a', 'l', 'i'},
         {'w', 'e', 'r', 'e'}};
    WordSearchSolver wss2(puzzle2);
    WordLocation result = wss2.FindWord("hat");
    REQUIRE(result.word == "hat");
    result = wss2.FindWord("ele");
    REQUIRE(result.word == "ele");
    result = wss2.FindWord("tar");
    REQUIRE(result.word == "tar");
    result = wss2.FindWord("hate");
    REQUIRE_FALSE(result.word == "hate");
    result = wss2.FindWord("eli");
    REQUIRE_FALSE(result.word == "eli");
    result = wss2.FindWord("le");
    REQUIRE(result.word == "le");
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////
