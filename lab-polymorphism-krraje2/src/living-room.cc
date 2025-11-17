#include "living-room.hpp"

LivingRoom::LivingRoom() : Room("living room"){}
void LivingRoom::RemovePerson(std::string name) {
    for (size_t i = 0; i < people_.size(); ++i) {
    if (people_.at(i) == name) {
      people_.erase(people_.begin() + i);
      people_.erase(people_.begin() + i);
      }
      return;
    }
}
/* Can hold an unlimited number of people, but when removing one person with “name”, 
one other arbitrary person is removed as well. If no person with “name” exists, 
then no additional person is removed. You can assume that there are at least two people in 
LivingRoom when RemovePerson is called.*/
bool LivingRoom::CanAddPerson() const { return true; }
