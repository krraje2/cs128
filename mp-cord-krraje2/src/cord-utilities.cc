#include "cord-utilities.hpp"

#include <map>
std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord,
                                  std::shared_ptr<Cord> right_cord) {
  std::shared_ptr<Cord> lefter = std::move(left_cord);
  std::shared_ptr<Cord> righter = std::move(right_cord);
  bool valid = lefter->IsValidCord() && righter->IsValidCord();
  if (!valid) {
    throw std::invalid_argument("Not creating a valid cord");
  }
  std::shared_ptr<Cord> cord = std::make_shared<Cord>(lefter, righter);
  return cord;
}

void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords) {
  std::map<std::string, std::shared_ptr<Cord>> visited;
  for (std::shared_ptr<Cord>& val : cords) {
    ReduceHelper(val, visited);
  }
}

void ReduceHelper(std::shared_ptr<Cord>& cord,
                  std::map<std::string, std::shared_ptr<Cord>>& visited) {
  // std::shared_ptr<Cord> hold = std::move(cord);
  if (visited.find(cord->ToString()) != visited.end()) {
    cord = visited[cord->ToString()];
  } else {
    visited.insert(
        std::pair<std::string, std::shared_ptr<Cord>>(cord->ToString(), cord));
    if (cord->left_ != nullptr) {
      ReduceHelper(cord->left_, visited);
    }
    if (cord->right_ != nullptr) {
      ReduceHelper(cord->right_, visited);
    }
  }
}