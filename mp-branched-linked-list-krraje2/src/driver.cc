#include <iostream>

#include "branched-linked-list.hpp"

int main() {
  /* EXAMPLE INTERACTIONS WITH BLL */
  // BLL* first = new BLL();
  // first->PushBack('h');
  // first->PushBack('i');
  // std::cout << first->ToString() << std::endl;  // hi
  // std::cout << first->Size() << std::endl;      // 2

  // // /////////////////////////////////////

  // BLL* second = new BLL();
  // second->PushBack('i');
  // second->PushBack('!');
  // second->PushBack('@');

  // std::cout << second->ToString() << std::endl;  // i!@
  // std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  // first->Join(1, second);

  // std::cout << first->ToString() << std::endl;   // hii!@
  // std::cout << first->Size() << std::endl;       // 5
  // std::cout << first->GetAt(2) << std::endl;     // i
  // std::cout << first->GetAt(3) << std::endl;     // !
  // first->SetAt(3, '$');
  // std::cout << first->GetAt(3) << std::endl;     // $
  // first->SetAt(2, 'a');
  //  std::cout << first->GetAt(2) << std::endl;     // a
  // std::cout << second->ToString() << std::endl;  // a$@
  // std::cout << second->Size() << std::endl;      // 3

  // /////////////////////////////////////

  // BLL* first_clone = new BLL();
  // *first_clone = *first;

  // std::cout << first_clone->ToString() << std::endl;  // hia$@
  // std::cout << first_clone->Size() << std::endl;      // 5

  // first_clone->Clear();
  // std::cout << first_clone->ToString() << "Nothing" << std::endl;

  // Vibe Example
  BLL* third = new BLL();
  third->PushBack('V');
  third->PushBack('I');

  BLL* fourth = new BLL();
  fourth->PushBack('B');
  BLL* fifth = new BLL();
  fifth->PushBack('E');
  fourth->Join(0, fifth);
  third->Join(1, fourth);
  std::cout << third->ToString() << std::endl;

  fifth->Join(0, fourth);

  return 0;
}
