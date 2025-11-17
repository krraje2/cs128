#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;
  BLL(const BLL& to_copy);
  ~BLL();

  BLL& operator=(const BLL& rhs);
  Node* PushBack(char dat);
  char GetAt(size_t idx) const;
  void SetAt(size_t idx, char dat);
  void Join(size_t idx, BLL* list);
  std::string ToString() const;
  size_t Size() const;
  // helpers
  Node* Copier(Node* node);
  void Clear();
  size_t Counter(Node* node) const;
  Node* GetNode(size_t count, size_t idx, Node* start) const;
  std::string GetString(Node* node) const;
  bool FindIfCyclic(Node* node) const; 

private:
  Node* head_ = nullptr;
  bool IsBLLAcyclic() const;
};

#endif
