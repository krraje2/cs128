#ifndef BATHROOM_HPP
#define BATHROOM_HPP

#include "room.hpp"
class Bathroom : public Room {
public:
  Bathroom();
  //  can only hold one person at a time
  protected:
  bool CanAddPerson() const;
};

#endif