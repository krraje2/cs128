
#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  // helpers for insert
  void InsertAscending(const T& data);
  void InsertDescending(const T& data);

  void Reverse();
  size_t Length();
  // helpers
  void Print();
  void SwitchOrder();
  bool CircleCheck();
  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

// given
template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
  } else {
    Node<T>* current = source.head_;
    while (current->next != source.head_) {
      InsertInOrder(current->data);
      current = current->next;
    }
    // stopped at tail so now add tail
    InsertInOrder(source.tail_->data);
  }
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  //delete it
  if (!(head_ == nullptr && tail_ == nullptr)) {
  tail_-> next = nullptr;
  while (head_ != nullptr) {
    Node<T>* next = head_->next;
    delete head_;
    head_ = next;
  }
  tail_ = nullptr;
  }

  node_order_ = source.node_order_;
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr;
  } else {
    Node<T>* current = source.head_;
    while (current->next != source.head_) {
      InsertInOrder(current->data);
      current = current->next;
    }
    // stopped at tail so now add tail
    InsertInOrder(source.tail_->data);
  }
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr && tail_ == nullptr) {
    return;
  }
  tail_->next = nullptr;
  while (head_ != nullptr) {
    Node<T>* next = head_->next;
    delete head_;
    head_ = next;
  }
  tail_ = nullptr;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = tail_ = new Node<T>(data);
    head_->next = tail_;
    tail_->next = head_;
  } else {
    if (node_order_ == Order::kASC) {
      InsertAscending(data);
    } else {
      InsertDescending(data);
    }
  }
}

template <typename T>
void CircularLinkedList<T>::InsertAscending(const T& data) {
  auto* temp = new Node<T>(data);
  if (head_->data >= data) {
    tail_->next = temp;
    temp->next = head_;
    head_ = temp;
  } else if (tail_->data <= data) {
    tail_->next = temp;
    temp->next = head_;
    tail_ = temp;
  } else {
    Node<T>* current = head_;
    Node<T>* nexter = current->next;
    while (nexter != head_ && nexter->data < data) {
      current = current->next;
      nexter = current->next;
    }
    current->next = temp;
    temp->next = nexter;
  }
}

template <typename T>
void CircularLinkedList<T>::InsertDescending(const T& data) {
  auto* temp = new Node<T>(data);
  if (head_->data <= data) {
    tail_->next = temp;
    temp->next = head_;
    head_ = temp;
  } else if (tail_->data >= data) {
    tail_->next = temp;
    temp->next = head_;
    tail_ = temp;
  } else {
    Node<T>* current = head_;
    Node<T>* nexter = current->next;
    while (nexter != head_ && nexter->data > data) {
      current = current->next;
      nexter = current->next;
    }
    current->next = temp;
    temp->next = nexter;
  }
}
template <typename T>
void CircularLinkedList<T>::Reverse() {
  SwitchOrder();
  if (Length() == 0 || Length() == 1) {
    return;
  }
  Node<T>* prev = head_;
  Node<T>* current = head_->next;

  while (current != tail_) {
    Node<T>* next = current->next;
    current->next = prev;
    prev = current;
    current = next;
  }
  // for tail
  tail_->next = prev;
  head_->next = current;

  // swap head and tail
  Node<T>* temp = head_;
  head_ = tail_;
  tail_ = temp;
}

// helpers
template <typename T>
size_t CircularLinkedList<T>::Length() {
  if (head_ == nullptr) {
    return 0;
  }
  size_t count = 0;
  Node<T>* current = head_;
  while (current != tail_) {
    count++;
    current = current->next;
  }
  count++;
  return count;
}
template <typename T>
void CircularLinkedList<T>::Print() {
  if (head_ == nullptr) {
    std::cout << "Empty list" << std::endl;
    return;
  }
  Node<T>* current = head_;
  std::cout << "head" << std::endl;
  while (current->next != head_) {
    std::cout << current->data << std::endl;
    current = current->next;
  }
  std::cout << current->data << std::endl;
  std::cout << "tail" << std::endl;

}

template <typename T>
void CircularLinkedList<T>::SwitchOrder() {
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
}

template <typename T>
bool CircularLinkedList<T>::CircleCheck() {
  return tail_->next == head_;
}

#endif