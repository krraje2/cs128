#include <iostream>

#include "illini_book.hpp"

int main() {
  IlliniBook i("example/persons.csv", "example/relations.csv");
  // i.PrintUINS();
  // i.PrintMap();
  // i.PrintAdjList();
  // std::cout << "Reached" << std::endl;
  // std::cout << "Connected components: " << i.CountGroups() << std::endl;
  // std::cout << "Connected components: " << i.CountGroups("128") << std::endl;
  // std::cout << "Connected components: " << i.CountGroups("124") << std::endl;
  // std::cout << "Connected components: " << i.CountGroups("173") << std::endl;
  // std::cout << "Connected components: "
  //           << i.CountGroups(std::vector<std::string>{"128", "173"})
  //           << std::endl;
  // std::cout << "Connected components: "
  //           << i.CountGroups(std::vector<std::string>{"128", "124", "173"})
  //           << std::endl;

  std::vector<int> nodes = i.GetSteps(1, 1);
  for (int n : nodes) {
    std::cout << n << std::endl;
  }
}
