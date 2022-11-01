#include "vehicleBase.h"

class car : public Vehicle {

    public:
        car(VehicleType type, Direction originalDirection);
        car(const VehicleBase& other);
        ~car();
};