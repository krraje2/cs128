#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>

class Room {
public:
Room() = default;
Room(std::string room_name);
std::string GetName() const;
virtual void AddPerson(std::string name);
virtual void RemovePerson(std::string name);
const std::vector<std::string>& GetPeople() const;

private:
std::string name_;
protected:
std::vector<std::string> people_;
virtual bool CanAddPerson() const = 0;
};

#endif  // ROOM_HPP