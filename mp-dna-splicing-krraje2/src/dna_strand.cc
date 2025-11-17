#include "dna_strand.hpp"
#include <stdexcept>
DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
}
/*void DNAstrand::Print() {
  Node* current = head_;
  std::cout << "head" << std::endl;
  while (current != nullptr) {
    std::cout << current->data << std::endl;
    current = current->next;
  }
  std::cout << "tail" << std::endl;
} */

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  if (*pattern == '\0' || to_splice_in.head_ == nullptr ||
      &to_splice_in == this) {
    return;
  }
  // finding and checking
  int found = 0;
  int count = 0;
  int index = 0;
  Node* current = head_;
  while (current != nullptr && count + StrLen(pattern) <= Length()) {
    bool notmatch = false;
    Node* thru = current;
    for (size_t pos = 0; pos < StrLen(pattern); pos++) {
      if (thru->data != pattern[pos]) {
        notmatch = true;
        break;
      }
      thru = thru->next;
    }
    if (!notmatch) {
      index = count;
      found++;
    }
    // std::cout << index << std::endl;
    count++;
    current = current->next;
  }

  // end
  if (found == 0) {
    throw std::runtime_error("No match found");
  }
  Deleter(index, pattern);
  Adder(index, to_splice_in);
}

void DNAstrand::Adder(size_t index, DNAstrand& to_splice_in) {
  Node* header = to_splice_in.head_;
  Node* tailer = to_splice_in.tail_;
  if (index == 0) {
    tailer->next = head_;
    head_ = header;
  } else if (index == Length() + 1) {
    tail_->next = header;
    tail_ = tailer;
  } else {
    Node* current = head_;
    for (size_t pos = 0; pos < index - 1; pos++) {
      current = current->next;
    }
    Node* nexter = current->next;
    current->next = header;
    tailer->next = nexter;
  }
  to_splice_in.head_ = to_splice_in.tail_ = nullptr;
}
void DNAstrand::Deleter(size_t index, const char* pattern) {
  for (size_t pos = 0; pos < StrLen(pattern); pos++) {
    EraseAt(index);
  }
}
// helpers

unsigned int DNAstrand::StrLen(const char* c_str) {
  unsigned int count = 0;
  int pos = 0;
  while (c_str[pos] != '\0') {
    count++;
    pos++;
  }
  return count;
}

size_t DNAstrand::Length() {
  Node* current = head_;
  size_t count = 0;
  while (current != nullptr) {
    count++;
    current = current->next;
  }
  return count;
}

// to help test
void DNAstrand::PushBack(char val) {
  Node* temp = new Node(val);
  if (head_ == nullptr) {
    head_ = tail_ = temp;
  } else {
    tail_->next = temp;
    tail_ = temp;
  }
}

/* void DNAstrand::PushBack(Node* val) {
  if (head_ == nullptr) {
    head_ = tail_ = val;
  } else {
    tail_->next = val;
    tail_ = val;
  }
} */
/* void DNAstrand::PushFront(Node* val) {
  if (head_ == nullptr) {
    head_ = tail_ = val;
  } else {
    val->next = head_;
    head_ = val;
  }
} */

/*void DNAstrand::InsertAt(size_t idx, Node* val) {
  if (idx == 0) {
    head_ = val;
  } else if (idx == Length()) {
    tail_->next = val;
  } else {
    Node* current = head_;
    for (size_t index = 0; index < idx - 1; index++) {
      current = current->next;
    }
    // point forward
    current->next = val;
  }
}*/
void DNAstrand::EraseAt(size_t idx) {
  if (idx == 0) {
    // pop front
    Node* temp = head_;
    head_ = head_->next;
    delete temp;
  } else if (idx == Length() - 1) {
    // pop back
    Node* prev = head_;
    while (prev->next->next != nullptr) {
      prev = prev->next;
    }
    delete prev->next;
    tail_ = prev;
    if (tail_ != nullptr) {
      tail_->next = nullptr;
    } else {
      head_ = nullptr;
    }
  } else {
    // in the middle so find position before the index
    size_t index = 0;
    Node* behind = head_;
    Node* current = head_->next;
    while (index < idx - 1) {
      behind = behind->next;
      current = current->next;
      index++;
    }
    Node* nexter = current->next;
    delete current;
    behind->next = nexter;
  }
}