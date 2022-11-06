#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;
VehicleType NULLTYPE;
Direction NULLDIRECTION;


// VehicleBase::VehicleBase(VehicleType type, Direction direction) {
//       vehicleID = 0;
//       vehicleType = type;
//       vehicleDirection = direction;

//       if (type == VehicleType::car){
//         vehicleLength = 2;
//       } else if (type == VehicleType::suv){
//         vehicleLength = 3;
//       } else {
//         vehicleLength = 4;
//       }
// }

// common use constructor
VehicleBase::VehicleBase(VehicleType type, Direction direction)
    : vehicleID(VehicleBase::vehicleCount++), 
      vehicleType(type),
      vehicleDirection(direction)
{
  if (vehicleType == VehicleType::car){
      vehicleLength = 2;
    } else if (vehicleType == VehicleType::suv){
      vehicleLength = 3;
    } else {
      vehicleLength = 4;
    }
  vehicleLengthCount = 0;
}

// Copy constructor
VehicleBase::VehicleBase(const VehicleBase& other):
      vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
      vehicleLength(other.vehicleLength),
      vehicleLengthCount(other.vehicleLengthCount)
{}

// copy assignment operator
VehicleBase& VehicleBase::operator=(const VehicleBase& other) {
  if (this == &other) {
    return *this;
  }
  vehicleID = other.vehicleID;
  vehicleType = other.vehicleType;
  vehicleDirection = other.vehicleDirection;
  vehicleLength = other.vehicleLength;
  vehicleLengthCount = other.vehicleLengthCount;

  return *this;
}

// move constructor
VehicleBase::VehicleBase(VehicleBase&& other)noexcept:
  vehicleID(other.vehicleID),
  vehicleType(other.vehicleType),
  vehicleDirection(other.vehicleDirection) {
    other.vehicleID = 0;
    other.vehicleType = NULLTYPE;
    other.vehicleDirection = NULLDIRECTION;
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
  other.vehicleType = NULLTYPE;
  other.vehicleDirection = NULLDIRECTION;
  return *this;
}

// destructor
VehicleBase::~VehicleBase() {}

void VehicleBase::incrementVehicleLengthCount(){
  vehicleLengthCount = vehicleLengthCount + 1;
}

void VehicleBase::decrementVehicleLengthCount(){
  vehicleLengthCount = vehicleLengthCount - 1;
}

#endif
