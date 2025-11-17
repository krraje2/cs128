#include <iostream>

#include "circular-linked-list.hpp"

int main() {
CircularLinkedList<char> list;
list.SwitchOrder();
list.InsertInOrder('a');
list.InsertInOrder('b');
list.InsertInOrder('b');
list.InsertInOrder('a');
list.InsertInOrder('c');
list.Print();
std::cout << "Number of nodes: " << list.Length() << std::endl;
std::cout << list.CircleCheck() << std::endl;
std::cout << '\n' << std::endl;

list.Reverse();
list.Print();
std::cout << list.CircleCheck() << std::endl;
std::cout << '\n' << std::endl;

CircularLinkedList<char> list2;
list2.InsertInOrder('d');
list2.InsertInOrder('j');
list2.Print();
std::cout << '\n' << std::endl;

list2 = list;
list2.Print();
std::cout << list2.CircleCheck() << std::endl; 
std::cout << '\n' << std::endl;
list2.~CircularLinkedList();
list2.Print();

}
