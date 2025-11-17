#ifndef LIVING_ROOM_HPP
#define LIVING_ROOM_HPP

#include "room.hpp"
class LivingRoom : public Room {
public:
LivingRoom();
void RemovePerson(std::string name);
/* Can hold an unlimited number of people, but when removing one person with “name”, one other arbitrary person is removed as well. If no person with “name” exists, then no additional person is removed. You can assume that there are at least two people in LivingRoom when RemovePerson is called.*/
protected:
bool CanAddPerson() const;
};



#endif  // LIVING_ROOM_HPP
