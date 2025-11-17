#include "solution.hpp"

unsigned int StrLen(const char* c_str) {
  unsigned int count = 0;
  int pos = 0;
  while (c_str[pos] != '\0') {
    count++;
    pos++;
  }
  return count;
}

void StrCpy(char*& to, const char* from) {
  if (from == nullptr) {
    return;
  }
  char* str1 = new char[StrLen(from) + 1];
  for (unsigned int i = 0; i < StrLen(from) + 1; i++) {
    str1[i] = from[i];
  }
  delete[] to;
  to = str1;
}