#ifndef CORD_UTILITIES_HPP
#define CORD_UTILITIES_HPP

#include "cord.hpp"

std::shared_ptr<Cord> ConcatCords(std::shared_ptr<Cord> left_cord,
                                  std::shared_ptr<Cord> right_cord);
void ReduceCords(cs128::ReferenceList<std::shared_ptr<Cord>> cords);
void ReduceHelper(std::shared_ptr<Cord>& cord,
                  std::map<std::string, std::shared_ptr<Cord>>& visited);
#endif
