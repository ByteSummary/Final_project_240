#ifndef __VEHICLE_BASE_H__
#define __VEHICLE_BASE_H__

// enum: see http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#S-enum
enum class Direction   {north, south, east, west};
enum class VehicleType {car, suv, truck};
enum class LightColor  {green, yellow, red};

class VehicleBase
{
   public:
      static int vehicleCount;
      static float carRightTurnProb;
      static float suvRightTurnProb;
      static float truckRightTurnProb;

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;
      int         vehicleLength;
      int         vehicleLengthCount;
      bool        willTurnRight;
      bool        isTurningRight;
      bool        isMovingForward;

   public:
      VehicleBase(VehicleType type, Direction originalDirection, float randnum);
      VehicleBase(const VehicleBase& other);
      VehicleBase& operator=(const VehicleBase& other);
      VehicleBase(VehicleBase&& other)noexcept;
      VehicleBase& operator=(VehicleBase&&)noexcept;
      ~VehicleBase();

      void incrementVehicleLengthCount();
      void decrementVehicleLengthCount();
      void resetVehicleLengthCount();
      void turnRight(float randnum);
      void setIsTurningRight(bool value);
      void setIsMovingForward(bool value);

      inline int getVehicleID() const { return this->vehicleID; }

      inline VehicleType getVehicleType() const { return this->vehicleType; }
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }
      inline int getVehicleLength() const { return this->vehicleLength; }
      inline int getVehicleLengthCount() const { return this->vehicleLengthCount; }
      inline bool getWillTurnRight() const{ return this->willTurnRight; }
      inline bool getIsTurningRight() const{ return this->isTurningRight; }
      inline bool getIsMovingForward() const{ return this->isMovingForward; }

      static void settingRightTurnProb(float proportion_right_turn_cars, float proportion_right_turn_SUVs, float proportion_right_turn_trucks);
};

#endif
