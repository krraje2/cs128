#include <cassert>
#include <iostream>

#include "cord-utilities.hpp"
#include "cord.hpp"
#include "cs128referencelist.hpp"

int main() {
  std::shared_ptr<Cord> l1 = std::make_shared<Cord>("8 is awe");
  std::shared_ptr<Cord> l4 = std::make_shared<Cord>("Yeah ");
  std::shared_ptr<Cord> l2 = std::make_shared<Cord>("some");
  std::shared_ptr<Cord> l3 = std::make_shared<Cord>("CS12");
  std::shared_ptr<Cord> l5 = std::make_shared<Cord>("");
  std::shared_ptr<Cord> cord2 = std::make_shared<Cord>(l4, l3);
  std::shared_ptr<Cord> cord4 = std::make_shared<Cord>(l1, l2);
  std::shared_ptr<Cord> cord5 = std::make_shared<Cord>(l1, l2);
  std::shared_ptr<Cord> cord1 = std::make_shared<Cord>(cord2, cord4);
  std::shared_ptr<Cord> cord6 = std::make_shared<Cord>(l3, cord5);
  // ////At testing
  // // std::cout << "Length is " << cord1->Length() << std::endl;
  // std::cout << cord1->ToString() << std::endl;
  // std::cout << cord2->ToString() << std::endl;
  // std::cout << cord4->ToString() << std::endl;
  // std::cout << cord5->ToString() << std::endl;
  // std::cout << cord6->ToString() << std::endl;
  // std::cout << l1->ToString() << std::endl;
  // std::cout << l2->ToString() << std::endl;
  // std::cout << l3->ToString() << std::endl;
  // std::cout << l5->ToString() << std::endl;
  // //::cout << cord1 ->At(20) << cord1->Length() << std::endl;
  // std::cout << cord5->At(0) << std::endl;
  // std::cout << cord5->At(4) << std::endl;
  // std::cout << cord5->At(7) << std::endl;
  // std::cout << cord5->At(8) << std::endl;
  // std::cout << cord5->At(11) << std::endl;
  // std::cout << "Separate /// " << std::endl;
  // std::cout << cord6->At(0) << std::endl;
  // std::cout << cord6->At(4) << std::endl;
  // std::cout << cord6->At(7) << std::endl;
  // std::cout << cord6->At(8) << std::endl;
  // std::cout << cord6->At(11) << std::endl;

  // std::cout << "Length is " << cord1->Length() << std::endl;
  // std::cout << cord1->At(0) << std::endl;
  // std::cout << cord1->At(7) << std::endl;
  // std::cout << cord1->At(11) << std::endl;
  // std::cout << cord1->At(14) << std::endl;
  // std::cout << cord1->At(17) << std::endl;
  // std::cout << cord1->At(20) << std::endl;
  // std::cout << "Separate /// " << std::endl;
  // std::cout << l1->At(0) << std::endl;
  // std::cout << l1->At(3) << std::endl;
  // std::cout << l1->At(7) << std::endl;

  // Correct lengths testing
  // std::cout << "Lengths /// " << std::endl;
  // std::cout << cord1->CorrectLengths(cord1) << std::endl;
  // std::cout << cord2->CorrectLengths(cord2) << std::endl;
  // std::cout << cord4->CorrectLengths(cord4) << std::endl;
  // std::cout << cord5->CorrectLengths(cord5) << std::endl;

  // std::cout << l3->CorrectLengths(l3) << std::endl;
  // std::cout << l5->CorrectLengths(l5) << std::endl;
  // l4->length_ = 17;
  // std::cout << l4->CorrectLengths(l4) << std::endl;
  // cord6->length_ = 30;
  // std::cout << cord6->CorrectLengths(cord6) << std::endl;
  // Correct Data testing
  // std::cout << "Data /// " << std::endl;
  // std::cout << cord1->CorrectData(cord1) << std::endl;
  // std::cout << cord2->CorrectData(cord2) << std::endl;
  // std::cout << cord4->CorrectData(cord4) << std::endl;
  // std::cout << cord5->CorrectData(cord5) << std::endl;
  // std::cout << cord6->CorrectData(cord6) << std::endl;
  // std::cout << l3->CorrectData(l3) << std::endl;
  // std::cout << l5->CorrectData(l5) << std::endl;
  l4->length_ = 17;
  // std::cout << l4->CorrectData(l4) << std::endl;
  cord6->data_ = "Howdy";
  // std::cout << cord6->CorrectData(cord6) << std::endl;
  // IsValid testing
  std::cout << "Is Valid /// " << std::endl;
  std::cout << cord1->IsValidCord() << std::endl;
  std::cout << cord2->IsValidCord() << std::endl;
  std::cout << cord4->IsValidCord() << std::endl;
  std::cout << cord5->IsValidCord() << std::endl;
  std::cout << l3->IsValidCord() << std::endl;
  std::cout << l5->IsValidCord() << std::endl;
  std::cout << l4->IsValidCord() << std::endl;
  std::cout << cord6->IsValidCord() << std::endl;
  // // Reduce testing
  // std::shared_ptr<Cord> l1 = std::make_shared<Cord>("pre");
  // std::shared_ptr<Cord> l2 = std::make_shared<Cord>("po");
  // std::shared_ptr<Cord> l3 = std::make_shared<Cord>("sse");
  // std::shared_ptr<Cord> l4 = std::make_shared<Cord>("ssion");
  // std::shared_ptr<Cord> l5 = std::make_shared<Cord>("nonpo");
  // std::shared_ptr<Cord> l6 = std::make_shared<Cord>("ssession");
  // std::shared_ptr<Cord> l7 = std::make_shared<Cord>("possession");
  // std::shared_ptr<Cord> l8 = std::make_shared<Cord>("pro");
  // std::shared_ptr<Cord> l9 = std::make_shared<Cord>("fe");
  // std::shared_ptr<Cord> l10 = std::make_shared<Cord>("ssion");
  // //
  // std::shared_ptr<Cord> cord1 = std::make_shared<Cord>(l3, l4);
  // std::shared_ptr<Cord> cord2 = std::make_shared<Cord>(l2, cord1);
  // std::shared_ptr<Cord> cord3 = std::make_shared<Cord>(l1, cord2);

  // std::shared_ptr<Cord> cord4 = std::make_shared<Cord>(l5, l6);
  // std::shared_ptr<Cord> cord5 = std::make_shared<Cord>("possession");
  // //
  // std::shared_ptr<Cord> cord6 = std::make_shared<Cord>(l9, l10);
  // std::shared_ptr<Cord> cord7 = std::make_shared<Cord>(l8, cord6);
  // cs128::ReferenceList<std::shared_ptr<Cord>> cords = {
  //     cord3, cord4, cord5, cord7};
  // ReduceCords(cords);
  // cord3->Print(cord3);
  // cord4->Print(cord4);
  // cord5->Print(cord5);
  // cord7->Print(cord7);

  // // Substring testing
  // std::cout << "Substring Testing"<< std::endl;
  // std::shared_ptr<Cord> sub1 = cord3->SubString(3, 8);
  // std::shared_ptr<Cord> sub2 = cord3->SubString(0, 13);
  // std::shared_ptr<Cord> sub3 = cord3->SubString(1, 4);
  // sub1->Print(sub1);
  // sub2->Print(sub2);
  // sub3->Print(sub3);
}