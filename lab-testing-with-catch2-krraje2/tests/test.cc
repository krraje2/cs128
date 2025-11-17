#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "sandwich.hpp"

using std::string;
using std::vector;

// A helper method for you to visualize what the contents of a vector are. You
// are welcome to modify this method or create additional helper methods.
//
// Example usage:
//  vector<string> my_vec;
//  my_vec.push_back("hello");
//  my_vec.push_back("world"):
//  PrintVector(my_vec);
// Prints:
//  [hello, world]
void PrintVector(const vector<string>& vec) {
  std::cout << "[";
  bool first = true;
  for (const auto& it : vec) {
    if (!first) {
      std::cout << ", ";
    } else {
      first = false;
    }

    std::cout << it;
  }

  std::cout << "]" << std::endl;
}

Sandwich ob = Sandwich();
TEST_CASE("Sandwich::AddTopping test", "[AddTopping]") {
  REQUIRE(ob.Sandwich::AddTopping("cheese"));
  REQUIRE_FALSE(ob.Sandwich::AddTopping("cheese"));
  REQUIRE(ob.Sandwich::AddTopping("tomato"));
  REQUIRE(ob.Sandwich::AddTopping("tomato"));
  REQUIRE(ob.Sandwich::AddTopping("lettuce"));
}

TEST_CASE("Sandwich::RemoveTopping test", "[RemoveTopping]") {
  REQUIRE_FALSE(ob.Sandwich::RemoveTopping("onions"));
  REQUIRE_FALSE(ob.Sandwich::RemoveTopping("pickles"));
  REQUIRE(ob.Sandwich::RemoveTopping("tomato"));
  REQUIRE(ob.Sandwich::RemoveTopping("lettuce"));
  REQUIRE(ob.Sandwich::RemoveTopping("tomato"));
  REQUIRE(ob.Sandwich::RemoveTopping("cheese"));
}

TEST_CASE("Sandwich::AddDressing test", "[AddDressing]") {
  REQUIRE_FALSE(ob.Sandwich::AddDressing("mayo"));
  REQUIRE(ob.Sandwich::AddTopping("tomato"));
  REQUIRE(ob.Sandwich::AddDressing("mayo"));
  REQUIRE(ob.Sandwich::AddDressing("mustard"));
  REQUIRE_FALSE(ob.Sandwich::AddDressing("mayo"));
  REQUIRE_FALSE(ob.Sandwich::AddDressing("mustard"));
  REQUIRE(ob.Sandwich::AddDressing("vinegar"));
}
