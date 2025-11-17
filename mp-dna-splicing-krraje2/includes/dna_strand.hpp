#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include <stdexcept>

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  void Deleter(size_t index, const char* pattern);
  void Adder(size_t index, DNAstrand& to_splice_in);
  unsigned int StrLen(const char* c_str);
  size_t Length();
  // void PopBack();
  // void PopFront();

  void PushBack(char val);
  // void PushBack(Node* val);
  // void PushFront(Node* val);

  void InsertAt(size_t idx, Node* val);
  void EraseAt(size_t idx);
  //void Print();

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif