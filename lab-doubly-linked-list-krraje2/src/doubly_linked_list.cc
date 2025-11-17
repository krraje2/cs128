#include <iomanip>
#include <sstream>
#include <stdexcept>
using std::endl;
using std::ostream;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;

#include "doubly_linked_list.hpp"

// Functions provided to you
ostream& operator<<(ostream& os, const DoublyLinkedList& ll) {
  constexpr unsigned int kWidth = 16;
  os << "Doubly Linked List" << endl;
  os << "Head: " << ll.head_ << "\t Tail: " << ll.tail_ << endl;
  os << "Size: " << ll.size_ << endl;
  if (ll.head_ == nullptr) return (os << "Empty" << endl);
  const Node* curr = ll.head_;
  os << "Nodes (accessible from head to tail):" << endl << endl;
  os << setw(kWidth) << setfill(' ') << ' ' << ' ' << Center("prev", kWidth - 1)
     << ' ' << Center("data", kWidth - 1) << ' ' << Center("next", kWidth - 1)
     << endl;
  while (curr != nullptr) {
    ostringstream oss;
    oss << (curr->prev);
    string prev = oss.str();
    oss.str("");
    oss << (curr->next);
    string next = oss.str();
    oss.str("");
    oss << (curr->data);
    string data = oss.str();
    oss.str("");
    oss << curr;
    string address = oss.str();
    os << setw(kWidth) << setfill(' ') << ' ' << '.' << setw(kWidth)
       << setfill('-') << '.' << setw(kWidth) << '.' << setw(kWidth) << '.'
       << endl;
    os << setw(kWidth) << setfill(' ') << Center(address, kWidth - 1) << '|'
       << setw(kWidth - 1) << setfill(' ') << Center(prev, kWidth - 1) << '|'
       << setw(kWidth - 1) << Center(data, kWidth - 1) << '|'
       << setw(kWidth - 1) << Center(next, kWidth - 1) << '|' << endl;
    os << setw(kWidth) << setfill(' ') << ' ' << '\'' << setw(kWidth)
       << setfill('-') << '\'' << setw(kWidth) << '\'' << setw(kWidth) << '\''
       << endl;
    os << endl;
    curr = curr->next;
  }
  return os;
}

std::string Center(const std::string& str, decltype(str.length()) col_width) {
  // quick and easy (but error-prone) implementation
  decltype(str.length()) padl = (col_width - str.length()) / 2;
  decltype(str.length()) padr = (col_width - str.length()) - padl;
  string strf = string(padl, ' ') + str + string(padr, ' ');
  return strf;
}

// start here
DoublyLinkedList::DoublyLinkedList(char val) {
  head_ = tail_ = new Node(val);
  size_++;
}
DoublyLinkedList::DoublyLinkedList(const std::vector<char>& values) {
  if (values.empty()) {
    head_ = tail_ = nullptr;
    size_ = 0;
  } else {
    for (char val : values) {
      PushBack(val);
    }
  }
}
DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& rhs) {
  if (rhs.Empty()) {
    head_ = tail_ = nullptr;
  } else {
    Node* node = rhs.head_;
    while (node != nullptr) {
      PushBack(node->data);
      node = node->next;
    }
  }
  size_ = rhs.size_;
}
DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& rhs) {
  if (this == &rhs) {
    return *this;
  }
  Clear();
  if (rhs.Empty()) {
    head_ = tail_ = nullptr;
  } else {
    Node* node = rhs.head_;
    while (node != nullptr) {
      PushBack(node->data);
      node = node->next;
    }
  }
  size_ = rhs.size_;
  return *this;
}
DoublyLinkedList::~DoublyLinkedList() { Clear(); }

char& DoublyLinkedList::Back() {
  if (head_ == nullptr) {
    throw std::exception();
  }
  return tail_->data;
}
char& DoublyLinkedList::Front() {
  if (head_ == nullptr) {
    throw std::exception();
  }
  return head_->data;
}
void DoublyLinkedList::PopBack() {
  if (Empty()) {
    throw std::invalid_argument("Empty List");
  }
  Node* temp = tail_;
  tail_ = tail_->prev;
  delete temp;
  if (tail_ != nullptr) {
    tail_->next = nullptr;
  } else {
    head_ = nullptr;
  }
  size_--;
}
void DoublyLinkedList::PopFront() {
  if (Empty()) {
    throw std::invalid_argument("Empty List");
  }
  Node* temp = head_;
  head_ = head_->next;
  delete temp;
  if (head_ != nullptr) {
    head_->prev = nullptr;
  } else {
    tail_ = nullptr;
  }
  size_--;
}

void DoublyLinkedList::PushBack(char val) {
  Node* temp = new Node(val);
  if (head_ == nullptr) {
    head_ = tail_ = temp;
  } else {
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;
  }
  size_++;
}
void DoublyLinkedList::PushFront(char val) {
  Node* temp = new Node(val);
  if (head_ == nullptr) {
    head_ = tail_ = temp;
  } else {
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
  }
  size_++;
}

void DoublyLinkedList::InsertAt(size_t idx, char val) {
  if (idx < 0 || idx > size_) {
    throw std::invalid_argument("Index out of bounds");
  }
  if (idx == 0) {
    PushFront(val);
  } else if (idx == size_) {
    PushBack(val);
  } else {
    Node* current = head_;
    Node* temp = new Node(val);
    for (size_t index = 0; index < idx; index++) {
      current = current->next;
    }
    Node* behind = current->prev;
    // point forward
    behind->next = temp;
    temp->next = current;
    // point behind
    current->prev = temp;
    temp->prev = behind;
    size_++;
  }
}
void DoublyLinkedList::EraseAt(size_t idx) {
  if (idx < 0 || idx >= size_) {
    throw std::invalid_argument("Index out of bounds");
  }
  if (idx == 0) {
    PopFront();
  } else if (idx == size_ - 1) {
    PopBack();
  } else {
    size_t index = 0;
    Node* current = head_;
    while (index < idx) {
      current = current->next;
      index++;
    }
    Node* nexter = current->next;
    Node* behind = current->prev;
    delete current;
    behind->next = nexter;
    nexter->prev = behind;
    size_--;
  }
}

char& DoublyLinkedList::Find(char val) {
  bool found = false;
  Node* current = head_;
  Node* holder = current;
  for (size_t pos = 0; pos < size_; pos++) {
    if (current->data == val) {
      found = true;
      holder = current;
    }
    current = current->next;
  }
  if (!found) {
    throw std::runtime_error("Value not found");
  }
  return holder->data;
}
void DoublyLinkedList::Clear() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
  tail_ = nullptr;
  size_ = 0;
}
