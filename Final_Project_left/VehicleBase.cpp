#ifndef __VEHICLE_BASE_CPP__
#define __VEHICLE_BASE_CPP__

#include "VehicleBase.h"

int VehicleBase::vehicleCount = 0;
float VehicleBase::carRightTurnProb = 0.0;
float VehicleBase::suvRightTurnProb = 0.0;
float VehicleBase::truckRightTurnProb = 0.0;
float VehicleBase::carLeftTurnProb = 0.0;
float VehicleBase::suvLeftTurnProb = 0.0;
float VehicleBase::truckLeftTurnProb = 0.0;


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

  setTurn(randnum);
  isCrossingIntersection = false;
  hasSwitchedBoundsLeft = false;
}

// copy constructor
VehicleBase::VehicleBase(const VehicleBase& other):
      vehicleID(other.vehicleID),
      vehicleType(other.vehicleType),
      vehicleDirection(other.vehicleDirection),
      vehicleLength(other.vehicleLength),
      vehicleLengthCount(other.vehicleLengthCount),
      willTurnRight(other.willTurnRight),
      willTurnLeft(other.willTurnLeft),
      hasSwitchedBoundsLeft(other.hasSwitchedBoundsLeft),
      isCrossingIntersection(other.isCrossingIntersection)
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
  willTurnRight = other.willTurnRight;
  willTurnLeft = other.willTurnLeft;
  hasSwitchedBoundsLeft = other.hasSwitchedBoundsLeft;
  isCrossingIntersection = other.isCrossingIntersection;

  return *this;
}

// move constructor
VehicleBase::VehicleBase(VehicleBase&& other)noexcept:
  vehicleID(other.vehicleID),
  vehicleType(other.vehicleType),
  vehicleDirection(other.vehicleDirection),
  vehicleLength(other.vehicleLength),
  vehicleLengthCount(other.vehicleLengthCount),
  willTurnRight(other.willTurnRight),
  willTurnLeft(other.willTurnLeft),
  hasSwitchedBoundsLeft(other.hasSwitchedBoundsLeft),
  isCrossingIntersection(other.isCrossingIntersection) {
    other.vehicleID = 0;
    other.vehicleType = NULLTYPE;
    other.vehicleDirection = NULLDIRECTION;
    other.vehicleLength = 0;
    other.vehicleLengthCount = 0;
    other.willTurnRight = false;
    other.willTurnLeft = false;
    other.hasSwitchedBoundsLeft = false;
    other.isCrossingIntersection = false;
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
  willTurnRight = other.willTurnRight;
  willTurnLeft = other.willTurnLeft;
  hasSwitchedBoundsLeft = other.hasSwitchedBoundsLeft;
  isCrossingIntersection = other.isCrossingIntersection;
  other.vehicleID = 0;
  other.vehicleType = NULLTYPE;
  other.vehicleDirection = NULLDIRECTION;
  other.vehicleLength = 0;
  other.vehicleLengthCount = 0;
  other.willTurnRight = false;
  other.willTurnLeft = false;
  other.hasSwitchedBoundsLeft = false;
  other.isCrossingIntersection = false;
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

// resets vehicle length count to vehicle length
void VehicleBase::resetVehicleLengthCount(){
  vehicleLengthCount = vehicleLength;
}

// determines if vehicle will turn right, left or straight
void VehicleBase::setTurn(float randnum){
  float rightTurnProb = 0.0;
  float leftTurnProb = 0.0;
  if (vehicleType == VehicleType::car){
    rightTurnProb = carRightTurnProb;
    leftTurnProb = carLeftTurnProb;
  } else if (vehicleType == VehicleType::suv){
    rightTurnProb = suvRightTurnProb;
    leftTurnProb = suvLeftTurnProb;
  } else {
    rightTurnProb = truckRightTurnProb;
    leftTurnProb = truckLeftTurnProb;
  }

  float straightTurnProb = 1 - (rightTurnProb + leftTurnProb);

  if (rightTurnProb < leftTurnProb)
  {
    // right < left
    if (rightTurnProb < straightTurnProb)
    {
      // right < left and straight
      if (randnum < rightTurnProb)
      {
        willTurnRight = true;
        willTurnLeft = false;
      } 
      else 
      {
        if (leftTurnProb < straightTurnProb)
        {
          // right < left < straight
          if (randnum < (leftTurnProb + rightTurnProb))
          {
            willTurnLeft = true;
            willTurnRight = false;
          }
          else
          {
            willTurnLeft = false;
            willTurnRight = false;
          } 
        }
        else
        {
          // right < straight < left
          if (randnum < (straightTurnProb + rightTurnProb))
          {
            willTurnLeft = false;
            willTurnRight = false;
          }
          else
          {
            willTurnLeft = true;
            willTurnRight = false;
          } 
        }
      }
    }
    else
    {
      // straight < right < left
      if (randnum < straightTurnProb)
      {
        willTurnRight = false;
        willTurnLeft = false;
      }
      else
      {
        if (randnum < (straightTurnProb + rightTurnProb))
        {
          willTurnLeft = false;
          willTurnRight = true;
        }
        else
        {
          willTurnLeft = true;
          willTurnRight = false;
        } 
      } 
    }
  }
  else
  {
    // left < right
    if (leftTurnProb < straightTurnProb)
    {
      // left < straight and right
      if (randnum < leftTurnProb)
      {
        willTurnRight = false;
        willTurnLeft = true;
      } 
      else 
      {
        if (rightTurnProb < straightTurnProb)
        {
          // left < right < straight
          if (randnum < (leftTurnProb + rightTurnProb))
          {
            willTurnLeft = false;
            willTurnRight = true;
          }
          else
          {
            willTurnLeft = false;
            willTurnRight = false;
          } 
        }
        else
        {
          // left < straight < right
          if (randnum < (straightTurnProb + leftTurnProb))
          {
            willTurnLeft = false;
            willTurnRight = false;
          }
          else
          {
            willTurnLeft = false;
            willTurnRight = true;
          } 
        }
      }
    }
    else
    {
      //straight < left < right
      if (randnum < straightTurnProb)
      {
        willTurnRight = false;
        willTurnLeft = false;
      }
      else
      {
        if (randnum < (straightTurnProb + leftTurnProb))
        {
          willTurnLeft = true;
          willTurnRight = false;
        }
        else
        {
          willTurnLeft = false;
          willTurnRight = true;
        } 
      } 
    }
  }
}

// sets is crossing intersection to value
void VehicleBase::setIsCrossingIntersection(bool value){
  isCrossingIntersection = value;
}

// sets has switched bounds left to value
void VehicleBase::setHasSwitchedBoundsLeft(bool value){
  hasSwitchedBoundsLeft = value;
}

// sets static variables for proportion right turn of vehicles
void VehicleBase::settingRightTurnProb(float proportion_right_turn_cars, float proportion_right_turn_SUVs, float proportion_right_turn_trucks){
  carRightTurnProb = proportion_right_turn_cars;
  suvRightTurnProb = proportion_right_turn_SUVs;
  truckRightTurnProb = proportion_right_turn_trucks;
}

// sets static variables for proportion left turn of vehicles
void VehicleBase::settingLeftTurnProb(float proportion_left_turn_cars, float proportion_left_turn_SUVs, float proportion_left_turn_trucks){
  carLeftTurnProb = proportion_left_turn_cars;
  suvLeftTurnProb = proportion_left_turn_SUVs;
  truckLeftTurnProb = proportion_left_turn_trucks;
}

#endif
