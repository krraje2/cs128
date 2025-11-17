#include "cord.hpp"

#include "cord-utilities.hpp"
Cord::Cord(const std::string& dat) {
  data_ = dat;
  length_ = dat.length();
}

Cord::Cord(const std::shared_ptr<Cord>& left_cord,
           const std::shared_ptr<Cord>& right_cord) {
  left_ = left_cord;
  right_ = right_cord;
  size_t left_length = 0;
  size_t right_length = 0;
  if (left_cord != nullptr) {
    left_length = left_cord->length_;
  }
  if (right_cord != nullptr) {
    right_length = right_cord->length_;
  }
  length_ = left_length + right_length;
}

size_t Cord::Length() const { return length_; }

std::shared_ptr<Cord> Cord::GetLeft() const { return left_; }

std::shared_ptr<Cord> Cord::GetRight() const { return right_; }

const std::string& Cord::GetData() const { return data_; }

std::string Cord::ToString() const {
  std::string line;
  if (left_ == nullptr && right_ == nullptr) {
    return data_;
  }
  line = StringHelper(left_) + StringHelper(right_);
  return line;
}

std::string Cord::StringHelper(const std::shared_ptr<Cord>& cord) const {
  // std::string line;
  if (cord->left_ != nullptr && cord->right_ != nullptr) {
    return StringHelper(cord->left_) + StringHelper(cord->right_);
  }
  if (cord->left_ != nullptr) {
    return StringHelper(cord->left_);
  }
  if (cord->right_ != nullptr) {
    return StringHelper(cord->right_);
  }
  return cord->data_;
}

std::shared_ptr<Cord> Cord::SubString(size_t lower_idx, size_t upper_idx) {
  size_t length = upper_idx - lower_idx;
  if (lower_idx < 0 || upper_idx > length_) {
    throw std::invalid_argument("Index out of bounds");
  }
  // std::cout << "Not out of bounds" << std::endl;
  if (lower_idx == 0 && length == length_) {
    return shared_from_this();
  }
  // std::cout << "Not a match" << std::endl;
  if (left_ == nullptr && right_ == nullptr) {
    // true if leaf or not
    return std::make_shared<Cord>(data_.substr(lower_idx, length));
  }
  if (upper_idx <= left_->length_) {
    return left_->SubString(lower_idx, upper_idx);
  }
  if (lower_idx >= left_->length_) {
    return right_->SubString(lower_idx - left_->length_,
                             upper_idx - left_->length_);
  }
  std::shared_ptr<Cord> lefter = left_->SubString(lower_idx, left_->length_);
  std::shared_ptr<Cord> righter =
      right_->SubString(0, upper_idx - left_->length_);
  return std::make_shared<Cord>(lefter, righter);
}

char Cord::At(size_t idx) const {
  if (idx >= length_) {
    throw std::invalid_argument("Index out of bounds");
  }
  if (left_ == nullptr && right_ == nullptr) {
    return data_.at(idx);
  }
  if (left_ != nullptr && CharHelper(left_, 0, idx) != '\0') {
    return CharHelper(left_, 0, idx);
  }
  if (right_ != nullptr && CharHelper(right_, left_->length_, idx) != '\0') {
    return CharHelper(right_, left_->length_, idx);
  }
  // std::string line;
  // line = CharHelper(left_, 0, idx) + CharHelper(right_, left_->length_, idx);
  // return line.at(idx);
  return '\0';
}

char Cord::CharHelper(const std::shared_ptr<Cord>& cord,
                      size_t count,
                      size_t index) const {
  if (cord->left_ == nullptr && cord->right_ == nullptr) {
    count += cord->length_;
    if (count > index) {
      size_t before = count - cord->length_;
      index = index - before;
      return cord->data_.at(index);
    }
  }
  if (cord->left_ != nullptr && CharHelper(cord->left_, count, index) != '\0') {
    return CharHelper(cord->left_, count, index);
  }
  if (cord->right_ != nullptr) {
    return CharHelper(cord->right_, count + cord->left_->length_, index);
  }
  return '\0';
}
// std::string Cord::CharHelper(const std::shared_ptr<Cord>& cord,
//                              size_t count,
//                              size_t index) const {
//   std::string line;
//   if (cord->left_ == nullptr && cord->right_ == nullptr) {
//     count += cord->length_;
//     if (count <= index) {
//       line += cord->data_;
//     }
//   }
//   if (cord->left_ != nullptr) {
//     return CharHelper(cord->left_, count, index);
//   }
//   if (cord->right_ != nullptr) {
//     return CharHelper(cord->right_, count, index);
//   }
//   return line;
// }

bool Cord::IsValidCord() const {
  // std::cout << "Length Left: " << CorrectLengths(left_) << std::endl;
    // std::cout << "Length Right: " << CorrectLengths(right_) << std::endl;
    // std::cout << "Data Left: " << CorrectData(left_) << std::endl;
    // std::cout << "Data Right: " << CorrectData(right_) << std::endl;
  // internal node w/ two children
  if (left_ != nullptr && right_ != nullptr) {
    if (length_ != (left_->length_ + right_->length_)) {
      return false;
    }
    if (!(data_.empty())) {
      return false;
    }
    return left_ -> IsValidCord() && right_->IsValidCord();
  }
  // internal node, only left
  if (left_ != nullptr) {
    if (length_ != (left_->length_)) {
      return false;
    }
    if (!(data_.empty())) {
      return false;
    }
    return left_ -> IsValidCord();
  }
  // internal node, only right
  if (right_ != nullptr) {
     if (length_ != (right_->length_)) {
      return false;
    }
    if (!(data_.empty())) {
      return false;
    }
    return right_ -> IsValidCord();
  }
  return data_.size() == length_;
}

// bool Cord::CorrectLengths(const std::shared_ptr<Cord>& cord) const {
//   if (cord->left_ != nullptr && cord->right_ != nullptr) {
//     if (cord->length_ != (cord->left_->length_ + cord->right_->length_)) {
//       return false;
//     }
//     return (CorrectLengths(cord->left_) && CorrectLengths(cord->right_));
//   }
//   if (cord->left_ != nullptr) {
//     if (cord->length_ != cord->left_->length_) {
//       return false;
//     }
//     return CorrectLengths(cord->left_);
//   }
//   if (cord->right_ != nullptr) {
//     if (cord->length_ != cord->right_->length_) {
//       return false;
//     }
//     return CorrectLengths(cord->right_);
//   }
//   return cord->data_.size() == cord->length_;
// }
// bool Cord::CorrectData(const std::shared_ptr<Cord>& cord) const {
//   bool not_empty = !(cord->data_.empty());
//   if (cord->left_ != nullptr && cord->right_ != nullptr) {
//     if (not_empty) {
//       return false;
//     }
//     return (CorrectData(cord->left_) && CorrectData(cord->right_));
//   }
//   if (cord->left_ != nullptr) {
//     if (not_empty) {
//       return false;
//     }
//     return CorrectData(cord->left_);
//   }
//   if (cord->right_ != nullptr) {
//     if (not_empty) {
//       return false;
//     }
//     return CorrectData(cord->right_);
//   }
//   return true;
// }

// void Cord::Print(const std::shared_ptr<Cord>& cord) const {
//   std::cout << cord->data_ << std::endl;
//   if (cord->left_ != nullptr) {
//     std::cout << "Left" << std::endl;
//     Print(cord->left_);
//   }
//   if (cord->right_ != nullptr) {
//     std::cout << "Right" << std::endl;
//     Print(cord->right_);
//   }
//}
