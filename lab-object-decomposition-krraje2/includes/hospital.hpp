#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include <set>
#include <string>
#include <vector>

#include "appointment.hpp"
#include "doctor.hpp"
#include "timeslot.hpp"

class Hospital {
public:
  Hospital() = default;
  void AddDoctor(Doctor& d);
  Doctor* GetAvailableDoctor(TimeSlot time);
  void AddAppointment(TimeSlot time, std::string patient);
  void RemoveAppointment(TimeSlot time, std::string patient);

private:
  std::vector<Appointment> appointments_;
  std::vector<Doctor*> doctors_;
};

#endif