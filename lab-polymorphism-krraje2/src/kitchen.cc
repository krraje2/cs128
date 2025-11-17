#include "kitchen.hpp"
Kitchen::Kitchen(): Room("kitchen") {}
//  can add unlimited number of ppl
bool Kitchen::CanAddPerson() const { return true; }
