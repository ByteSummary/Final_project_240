#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;

VehicleBase::VehicleBase(VehicleType type, Direction direction) {
      vehicleID = 0;
      vehicleType = type;
      vehicleDirection = direction;
}

// common use constructor
VehicleBase::VehicleBase(VehicleType type, Direction direction)
    : vehicleID(VehicleBase::vehicleCount++), 
      vehicleType(type),
      vehicleDirection(direction)
{}

// Copy constructor
VehicleBase::VehicleBase(const VehicleBase& other):
      vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection)
{}

// copy assignment operator
VehicleBase& VehicleBase::operator=(const VehicleBase& other) {
  if (this == &other) {
    return *this;
  }
  vehicleID = other.vehicleID;
  vehicleType = other.vehicleType;
  vehicleDirection = other.vehicleDirection;
}

// move constructor
VehicleBase::VehicleBase(VehicleBase&& other)noexcept:
  vehicleID(other.vehicleID),
  vehicleType(other.vehicleType),
  vehicleDirection(other.vehicleDirection) {
    other.vehicleID = 0;
    other.vehicleType = ;
    other.vehicleDirection = ;
  }

// move assignment operator constructor
VehicleBase& VehicleBase::operator=(VehicleBase&& other)noexcept {
  if (this == &other) {
    return *this;
  }
  vehicleID = other.vehicleID;
  vehicleType = other.vehicleType;
  vehicleDirection = other.vehicleDirection;
  other.vehicleID = 0;
  other.vehicleType = ;
  other.vehicleDirection = ;

}

// destructor
VehicleBase::~VehicleBase() {}

#endif
