#include <iostream>

#include "dna_strand.hpp"

int main() {
  // char pattern1[] = "ctc";
  DNAstrand splice;
  DNAstrand splice2;
  // first
  splice.PushBack('a');
  splice.PushBack('t');
  splice.PushBack('t');
  splice.PushBack('a');
  splice.PushBack('t');
  splice.PushBack('t');
  splice.PushBack('c');
  splice.PushBack('a');
  splice.PushBack('t');
  splice.PushBack('c');
  // second
  splice2.PushBack('a');
  splice2.PushBack('c');
  splice2.PushBack('g');
  splice2.PushBack('c');
  // splice.SpliceIn(pattern1, splice2);
  // splice.Print();
  std::cout << "Length: " << splice.Length() << std::endl;
  splice.EraseAt(3);
  splice.Print();
  std::cout << "Length: " << splice.Length() << std::endl;
  splice.EraseAt(3);
  splice.EraseAt(3);
  splice.Print();
  std::cout << "Length: " << splice.Length() << std::endl;
  size_t index = 3;
  splice.Adder(index, splice2);
  splice.Print();
  std::cout << "Length: " << splice.Length() << std::endl;
}
