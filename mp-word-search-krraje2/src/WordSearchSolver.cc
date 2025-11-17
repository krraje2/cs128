#include "WordSearchSolver.hpp"

#include <limits>
#include <string>
#include <vector>

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle):
    puzzle_(puzzle),
    puzzle_height_(puzzle.size()),
    puzzle_width_(puzzle.at(0).size()) {}

WordLocation WordSearchSolver::Returner(std::string& word) {
  WordLocation w = WordLocation{};
  std::string line = word;
  if (!(WordSearchSolver::HorizontalChecker(line).empty())) {
    w.char_positions = WordSearchSolver::HorizontalChecker(line);
    w.word = line;
  } else if (!(WordSearchSolver::VerticalChecker(line).empty())) {
    w.char_positions = WordSearchSolver::VerticalChecker(line);
    w.word = line;
  } else if (!(WordSearchSolver::RightDiagChecker(line).empty())) {
    w.char_positions = WordSearchSolver::RightDiagChecker(line);
    w.word = line;
  } else if (!(WordSearchSolver::LeftDiagChecker(line).empty())) {
    w.char_positions = WordSearchSolver::LeftDiagChecker(line);
    w.word = line;
  }
  return w;
}
WordLocation WordSearchSolver::FindWord(const std::string& word) {
  WordLocation w = WordLocation{};
  std::string line = word;

  return Returner(line);
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  WordLocation w;
  std::string line = word;
  std::vector<CharPositions> vect;
  if (direction == CheckDirection::kHorizontal) {
    vect = WordSearchSolver::HorizontalChecker(line);
  } else if (direction == CheckDirection::kVertical) {
    vect = WordSearchSolver::VerticalChecker(line);
  } else if (direction == CheckDirection::kLeftDiag) {
    vect = WordSearchSolver::LeftDiagChecker(line);
  } else {
    vect = WordSearchSolver::RightDiagChecker(line);
  }
  if (!(vect.empty())) {
    w.char_positions = vect;
    w.word = line;
    return w;
  }

  return WordLocation{};
} 

std::vector<CharPositions> WordSearchSolver::HorizontalChecker(
    std::string& word) {
  std::vector<CharPositions> vect;
  for (size_t row = 0; row < puzzle_height_; row++) {
    for (size_t col = 0; col < puzzle_width_ - (word.size() - 1); col++) {
      int count = 0;
      for (size_t pos = 0; pos < word.size(); pos++) {
        if (puzzle_.at(row).at(col + pos) == word[pos]) {
          count++;
        }
      }
      if (count == static_cast<int>(word.size())) {
        for (size_t i = 0; i < word.size(); i++) {
          CharPositions c = CharPositions{};
          c.character = word[i];
          c.row = row;
          c.col = col + i;
          vect.push_back(c);
        }
      }
    }
  }
  return vect;
}

std::vector<CharPositions> WordSearchSolver::VerticalChecker(
    std::string& word) {
  std::vector<CharPositions> vect;
  for (size_t col = 0; col < puzzle_width_; col++) {
    for (size_t row = 0; row < puzzle_height_ - (word.size() - 1); row++) {
      int count = 0;
      for (size_t pos = 0; pos < word.size(); pos++) {
        if (puzzle_.at(row + pos).at(col) == word[pos]) {
          count++;
        }
      }
      if (count == static_cast<int>(word.size())) {
        for (size_t i = 0; i < word.size(); i++) {
          CharPositions c = CharPositions{};
          c.character = word[i];
          c.row = row + i;
          c.col = col;
          vect.push_back(c);
        }
      }
    }
  }
  return vect;
}


std::vector<CharPositions> WordSearchSolver::LeftDiagChecker(
    std::string& word) {
  std::vector<CharPositions> vect;
  for (size_t col = word.size() - 1; col < puzzle_width_; col++) {
    for (size_t row = 0; row < puzzle_height_ - (word.size() - 1); row++) {
      int count = 0;
      for (size_t pos = 0; pos < word.size(); pos++) {
        if (puzzle_.at(row + pos).at(col - pos) == word[pos]) {
          count++;
        }
      }
     if (count == static_cast<int>(word.size())) {
          for (size_t k = 0; k < word.size(); k++) {
            CharPositions c = CharPositions{};
            c.character = word[k];
            c.row = row + k;
            c.col = col - k;
            vect.push_back(c);
          }
        }
    }
  }
  return vect;
}


/* std::vector<CharPositions> WordSearchSolver::RightDiagChecker(
    std::string& word) {
  std::vector<CharPositions> vect;
  for (size_t col = puzzle_width_ - word.size();
       col != std::numeric_limits<size_t>::max();
       col--) {
    for (size_t row = 0; row < puzzle_height_ - (word.size() - 1); row++) {
      int count = 0;
      for (size_t pos = 0; pos < word.size(); pos++) {
        if (puzzle_.at(row + pos).at(col + pos) == word[pos]) {
          count++;
        }
        if (count == static_cast<int>(word.size())) {
          for (size_t k = 0; k < word.size(); k++) {
            CharPositions c = CharPositions{};
            c.character = word[k];
            c.row = row + k;
            c.col = col + k;
            vect.push_back(c);
          }
        }
      }
    }
  }
  return vect;
} */

std::vector<CharPositions> WordSearchSolver::RightDiagChecker(
    std::string& word) {
  std::vector<CharPositions> vect;
  for (size_t col = puzzle_width_ - word.size();
       col != std::numeric_limits<size_t>::max();
       col--) {
    for (size_t row = 0; row < puzzle_height_ - (word.size() - 1); row++) {
     bool found = true;
      for (size_t pos = 0; pos < word.size(); pos++) {
        if (puzzle_.at(row + pos).at(col + pos) != word[pos]) {
          found = false;
        }
        }  
        if (found) {
          for (size_t k = 0; k < word.size(); k++) {
            CharPositions c = CharPositions{};
            c.character = word[k];
            c.row = row + k;
            c.col = col + k;
            vect.push_back(c);
          }
      }
    }
  }
  return vect;
}

