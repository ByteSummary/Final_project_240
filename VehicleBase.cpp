#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;
float VehicleBase::carRightTurnProb = 0.0;
float VehicleBase::suvRightTurnProb = 0.0;
float VehicleBase::truckRightTurnProb = 0.0;


// common use constructor
VehicleBase::VehicleBase(VehicleType type, Direction direction, float randnum)
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

  turnRight(randnum);
  isCrossingIntersection = false;
}

// copy constructor
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
  vehicleDirection(other.vehicleDirection),
  vehicleLength(other.vehicleLength),
  vehicleLengthCount(other.vehicleLengthCount) {
    other.vehicleID = 0;
    other.vehicleType = NULLTYPE;
    other.vehicleDirection = NULLDIRECTION;
    other.vehicleLength = 0;
    other.vehicleLengthCount = 0;
  }

// move assignment operator constructor
VehicleBase& VehicleBase::operator=(VehicleBase&& other)noexcept {
  if (this == &other) {
    return *this;
  }
  vehicleID = other.vehicleID;
  vehicleType = other.vehicleType;
  vehicleDirection = other.vehicleDirection;
  vehicleLength = other.vehicleLength;
  vehicleLengthCount = other.vehicleLengthCount;
  other.vehicleID = 0;
  other.vehicleType = NULLTYPE;
  other.vehicleDirection = NULLDIRECTION;
  other.vehicleLength = 0;
  other.vehicleLengthCount = 0;
  return *this;
}

// destructor
VehicleBase::~VehicleBase() {}

// increases vehicle length count by 1
void VehicleBase::incrementVehicleLengthCount(){
  vehicleLengthCount = vehicleLengthCount + 1;
}

// decreases vehicle length count by 1
void VehicleBase::decrementVehicleLengthCount(){
  vehicleLengthCount = vehicleLengthCount - 1;
}

// determines if vehicle will turn right or not
void VehicleBase::turnRight(float randnum){
  float rightTurnProb = 0.0;
  if (vehicleType == VehicleType::car){
    rightTurnProb = carRightTurnProb;
  } else if (vehicleType == VehicleType::suv){
    rightTurnProb = suvRightTurnProb;
  } else {
    rightTurnProb = truckRightTurnProb;
  }

  if (randnum < rightTurnProb){
    willTurnRight = true;
  } else {
    willTurnRight = false;
  }
}

// sets is crossing intersection to value
void VehicleBase::setIsCrossingIntersection(bool value){
  isCrossingIntersection = value;
}

// sets static variables for proportion right turn of vehicles
void VehicleBase::settingRightTurnProb(float proportion_right_turn_cars, float proportion_right_turn_SUVs, float proportion_right_turn_trucks){
  carRightTurnProb = proportion_right_turn_cars;
  suvRightTurnProb = proportion_right_turn_SUVs;
  truckRightTurnProb = proportion_right_turn_trucks;
}

#endif
