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

   private:
      int         vehicleID;
      VehicleType vehicleType;
      Direction   vehicleDirection;
      int         vehicleLength;
      int         vehicleLengthCount;

   public:
      VehicleBase(VehicleType type, Direction originalDirection);
      VehicleBase(const VehicleBase& other);
      VehicleBase& operator=(const VehicleBase& other);
      // VehicleBase::VehicleBase(VehicleBase&& other)noexcept;
      // VehicleBase& VehicleBase::operator=(VehicleBase&&)noexcept;
      ~VehicleBase();

      void incrementVehicleLengthCount();
      void decrementVehicleLengthCount();

      inline int getVehicleID() const { return this->vehicleID; }

      inline VehicleType getVehicleType() const { return this->vehicleType; }
      inline Direction   getVehicleOriginalDirection() const { return this->vehicleDirection; }
      inline int getVehicleLength() const { return this->vehicleLength; }
      inline int getVehicleLengthCount() const { return this->vehicleLengthCount; }
};

#endif
