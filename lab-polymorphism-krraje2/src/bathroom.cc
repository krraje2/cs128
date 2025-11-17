#include "bathroom.hpp"

Bathroom::Bathroom(): Room("bathroom") {}

bool Bathroom::CanAddPerson() const {
    if (people_.empty()) {
        return true;
    }
    return false;
}
