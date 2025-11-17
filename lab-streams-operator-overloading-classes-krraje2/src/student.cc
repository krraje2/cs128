#include "student.hpp"

#include <iostream>

#include "course.hpp"

Student::Student(std::string name, std::string uin, std::string net_id):
    name_(name),
    uin_(uin),
    net_id_(net_id),
    major_("Undeclared"),
    graduated_(false) {}
Student::Student(std::string name,
                 std::string uin,
                 std::string net_id,
                 std::string major,
                 std::vector<Course> courses,
                 bool graduated):
    name_(name),
    uin_(uin),
    net_id_(net_id),
    major_(major),
    graduated_(graduated),
    courses_(courses) {}
std::string Student::GetName() const { return name_; }
std::string Student::GetUIN() const { return uin_; }
std::string Student::GetNetId() const { return net_id_; }
std::string Student::GetMajor() const { return major_; }
bool Student::HasGraduated() const { return graduated_; }
const std::vector<Course>& Student::GetCourses() const { return courses_; }
void Student::SetName(std::string name) { name_ = name; }
void Student::SetMajor(std::string major) { major_ = major; }
bool Student::AddCourse(Course c) {
  int count = 0;
  for (Course course : courses_) {
    if (course.name == c.name) {
      count++;
    }
  }
  if (count == 0) {
    courses_.push_back(c);
    return true;
  }
  return false;
}
void Student::Graduate() {
  int totalcredits = 0;
  for (Course& c : courses_) {
    totalcredits += c.credits;
  }
  if (totalcredits >= min_credits_grad_) {
    graduated_ = true;
  } else {
    graduated_ = false;
  }
}

std::ostream& operator<<(std::ostream& os, const Student& s) {
  os << "Name: " << s.GetName() << '\n';
  os << "UIN: " << s.GetUIN() << '\n';
  os << "Net Id: " << s.GetNetId() << '\n';
  os << "Major: " << s.GetMajor() << '\n';
  int totalcredits = 0;
  for (Course c : s.GetCourses()) {
    totalcredits += c.credits;
  }
  os << "Credits: " << totalcredits << '\n';
  os << "Courses: ";
  for (size_t i = 0; i < s.GetCourses().size(); i++) {
    os << s.GetCourses().at(i).name;
    if (i != s.GetCourses().size() - 1) {
      os << ", ";
    } else {
      os << "\n";
    }
  }

  if (s.HasGraduated()) {
    os << "Graduated: True";
  } else {
    os << "Graduated: False";
  }

  return os;
}