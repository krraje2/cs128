#include "roster.hpp"

#include <iostream>

Roster::Roster(const Student& student) {
  head_ = std::make_unique<RosterEntry>(student, nullptr);
}

void Roster::AddStudent(const Student& student) {
  if (head_ == nullptr) {
    head_ = std::make_unique<RosterEntry>(student, nullptr);
    return;
  }
  // less than head, make a new head
  RosterEntry* current = head_.get();
  if (student <= head_->student) {
    auto* new_head = new RosterEntry(student, head_.release());
    head_.reset(new_head);

  }  // essentially the "tail"
  else if (current->next == nullptr) {
    current->next = std::make_unique<RosterEntry>(student, nullptr);
  }  // in the body
  else {
    while (current -> next != nullptr && current->next->student <= student) {
      current = current->next.get();
    }
    if (current->next == nullptr) {
      current->next = std::make_unique<RosterEntry>(student, nullptr);
    } else {
      auto* replace = new RosterEntry(student, current->next.release());
      current->next.reset(replace);
    }
  }
}

Roster::Iterator Roster::begin() const { return Iterator(head_.get()); }

Roster::Iterator Roster::end() const { return Iterator(); }
