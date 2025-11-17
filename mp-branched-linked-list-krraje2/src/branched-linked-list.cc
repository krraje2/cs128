#include "branched-linked-list.hpp"

#include <stdexcept>

BLL::BLL(const BLL& to_copy) {
  // copier should take care of entire branched list bc of recursion
  head_ = Copier(to_copy.head_);
}
BLL::~BLL() { Clear(); }

void BLL::Clear() {
  Node* temp = head_;
  while (temp != nullptr) {
    Node* next = temp->next_node_;
    // delete the next BLL
    delete temp->next_bll_;
    temp->next_bll_ = nullptr;
    delete temp;
    temp = next;
  }
  head_ = nullptr;
}

Node* BLL::Copier(Node* node) {
  if (node == nullptr) {
    return nullptr;
  }
  // go thru to make the first branch
  Node* deep_copy = new Node(node->data_);
  deep_copy->next_node_ = Copier(node->next_node_);
  if (node->next_bll_ != nullptr) {
    // creates the new bll that's been found by calling the function
    deep_copy->next_bll_ = new BLL();
    deep_copy->next_bll_->head_ = Copier(node->next_bll_->head_);
  }
  return deep_copy;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (this == &rhs) {
    return *this;
  }
  // BLL deleting
  Clear();
  // copier
  head_ = Copier(rhs.head_);
  return *this;
}

Node* BLL::PushBack(char dat) {
  Node* add = new Node(dat);
  if (head_ == nullptr) {
    head_ = add;
    return add;
  }
  Node* current = head_;
  while (current->next_node_ != nullptr) {
    current = current->next_node_;
  }
  current->next_node_ = add;
  return add;
}

Node* BLL::GetNode(size_t count, size_t idx, Node* start) const {
  if (start == nullptr || count == idx) {
    return start;
  }
  // prioritize the next BLL first
  if (start->next_bll_ != nullptr) {
    return GetNode(count + 1, idx, start->next_bll_->head_);
  }
  // otherwise the other nodes
  return GetNode(count + 1, idx, start->next_node_);
}

char BLL::GetAt(size_t idx) const {
  if (idx < 0 || idx >= Size()) {
    throw std::invalid_argument("Index out of bounds");
  }
  return GetNode(0, idx, head_)->data_;
}

void BLL::SetAt(size_t idx, char dat) {
  if (idx < 0 || idx >= Size()) {
    throw std::invalid_argument("Index out of bounds");
  }
  // use the getter
  Node* temp = GetNode(0, idx, head_);
  temp->data_ = dat;
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx < 0 || idx >= Size()) {
    throw std::invalid_argument("Index out of bounds");
  }
  Node* node = GetNode(0, idx, head_);
  if (node->next_bll_ != nullptr) {
    throw std::invalid_argument("Already a list");
  }
  node->next_bll_ = list;
  if (FindIfCyclic(head_)) {
    throw std::invalid_argument("Makes it cyclic");
  }
}
std::string BLL::ToString() const { return GetString(head_); }

std::string BLL::GetString(Node* node) const {
  if (node == nullptr) {
    return "";
  }
  std::string char_to_string(1, node->data_);
  // if there's a Bll, prioritize BLL first, then rest
  if (node->next_bll_ != nullptr) {
    return char_to_string + GetString(node->next_bll_->head_) +
           GetString(node->next_node_);
  }
  // no BLL, so go thru rest
  return char_to_string + GetString(node->next_node_);
}

size_t BLL::Size() const { return Counter(head_); }
size_t BLL::Counter(Node* node) const {
  if (node == nullptr) {
    return 0;
  }
  // if there's a Bll, count for both the next BLL and the rest of list
  if (node->next_bll_ != nullptr) {
    return 1 + Counter(node->next_node_) + Counter(node->next_bll_->head_);
  }
  // next node (no bll)
  return 1 + Counter(node->next_node_);
}

bool BLL::IsBLLAcyclic() const { return !(FindIfCyclic(head_)); }
bool BLL::FindIfCyclic(Node* node) const {
  if (node == nullptr) {
    return false;
  }
  // use video idea, but must move differently instead of just next_node_, can
  // use get node to navigate start at index 0
  size_t oog_index = 0;
  Node* oogway = GetNode(0, oog_index, head_);
  // index 1
  size_t shifu_index = 1;
  Node* shifu = GetNode(0, shifu_index, head_);
  while (oogway != nullptr && shifu != nullptr) {
    // to move to next bll
    if (oogway == shifu) {
      return true;
    }
    // forward by 1
    oog_index++;
    oogway = GetNode(0, oog_index, head_);
    // forward by 2
    shifu_index += 2;
    shifu = GetNode(0, shifu_index, head_);
  }
  return false;
}