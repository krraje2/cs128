#include "functions.hpp"

#include <iostream>
#include <string>

char DashRules(std::string str, int pos) {
  if (pos != static_cast<int>(str.size()) - 1 && str[pos + 1] != ' ' &&
      str[pos + 1] != '\'') {
    return '-';
  }
  return ' ';
}

std::string Lowercase(std::string word) {
  std::string line;
  for (int pos = 0; pos < static_cast<int>(word.size()); ++pos) {
    line += tolower(word[pos]);
  }
  return line;
}
std::string WRules(std::string word, int pos) {
  std::string line;
  if (pos == 0 || word[pos - 1] == ' ' || word[pos - 1] == 'a' ||
      word[pos - 1] == 'u' || word[pos - 1] == 'o') {
    line += "w";
  } else if (pos != 0 && (word[pos - 1] == 'i' || word[pos - 1] == 'e')) {
    line += "v";
  }
  return line;
}

std::string ARules(std::string word, int pos) {
  std::string line;
  if (pos != static_cast<int>(word.size()) - 1 &&
      (word[pos + 1] == 'i' || word[pos + 1] == 'e')) {
    line = "eye";
  } else if (pos != static_cast<int>(word.size()) - 1 &&
             (word[pos + 1] == 'u' || word[pos + 1] == 'o')) {
    line = "ow";
  } else {
    line = "ah";
  }
  if (DashRules(word, pos) != ' ') {
    line += DashRules(word, pos);
  }
  return line;
}

std::string ERules(std::string word, int pos) {
  std::string line;
  if (pos != static_cast<int>(word.size()) - 1 && (word[pos + 1] == 'i')) {
    line += "ay";
  } else if (pos != static_cast<int>(word.size()) - 1 && word[pos - 1] == 'u') {
    line += "eh-oo";
  } else {
    line += "eh";
  }
  if (DashRules(word, pos) != ' ') {
    line += DashRules(word, pos);
  }
  return line;
}

std::string IRules(std::string word, int pos) {
  std::string line;
  if (pos != static_cast<int>(word.size()) - 1 && (word[pos + 1] == 'u')) {
    line += "ay";
  } else {
    line += "ee";
  }
  if (DashRules(word, pos) != ' ') {
    line += DashRules(word, pos);
  }
  return line;
}

std::string ORules(std::string word, int pos) {
  std::string line;
  if (pos != static_cast<int>(word.size()) - 1 && word[pos + 1] == 'i') {
    line += "oy";
  } else {
    line += "oh";
  }
  if (DashRules(word, pos) != ' ') {
    line += DashRules(word, pos);
  }
  return line;
}

std::string URules(std::string word, int pos) {
  std::string line;
  if (pos != static_cast<int>(word.size()) - 1 && word[pos + 1] == 'i') {
    line += "ooey";
  } else {
    line += "oo";
  }
  if (DashRules(word, pos) != ' ') {
    line += DashRules(word, pos);
  }
  return line;
}

/*int PosChecker(std::string word, int pos) {
  if (word[pos + 1] == 'a' || word[pos + 1] == 'e' || word[pos + 1] == 'i' ||
      word[pos + 1] == 'o' || word[pos + 1] == 'u') {
    return 1;
  }
  return 0;
} */

std::string NotValid(std::string& str, char c) {
  if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u' && c != 'p' &&
      c != 'k' && c != 'h' && c != 'l' && c != 'm' && c != 'n' && c != 'w' &&
      c != ' ' && c != '\'') {
    std::string message =
        str + " contains a character not a part of the Hawaiian language.";
    return message;
  }
  return " ";
}

int APos(std::string str, int pos) {
  char next = static_cast<char>(str[pos + 1]);
  if (next == 'i' || next == 'e' || next == 'o' || next == 'u') {
    pos += 1;
  }
  return pos;
}

std::string PhoneticPronunciation(std::string str) {
  std::string phonetics;
  str = Lowercase(str);
  for (int pos = 0; pos < static_cast<int>(str.size()); ++pos) {
    char c = static_cast<char>(str[pos]);
    char next = static_cast<char>(str[pos + 1]);
    if (NotValid(str, c) != " ") {
      return NotValid(str, c);
    }
    if (c == 'p' || c == 'k' || c == 'h' || c == 'l' || c == 'm' || c == 'n' ||
        c == ' ' || c == '\'') {
      phonetics += c;
    } else if (c == 'w') {
      phonetics += WRules(str, pos);
    } else if (c == 'a') {
      phonetics += ARules(str, pos);
      pos = APos(str, pos);
    } else if (c == 'e') {
      phonetics += ERules(str, pos);
      if (next == 'i' || next == 'u') {
        pos += 1;
      }
    } else if (c == 'i') {
      phonetics += IRules(str, pos);
      if (next == 'u') {
        pos += 1;
      }
    } else if (c == 'o') {
      phonetics += ORules(str, pos);
      if (next == 'i' || next == 'u') {
        pos += 1;
      }
    } else if (c == 'u') {
      phonetics += URules(str, pos);
      if (next == 'i') {
        pos += 1;
      }
    }
  }
  return phonetics;
}
