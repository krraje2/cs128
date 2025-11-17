#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include "room.hpp"
class Kitchen : public Room {
public:
  Kitchen();
  //  can add unlimited number of ppl
  protected:
  bool CanAddPerson() const;
};

#endif  // KITCHEN_HPP