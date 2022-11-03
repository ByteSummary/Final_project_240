#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "VehicleBase.h"

class TrafficLight {

    private:
        LightColor lightcolor;
        int timeGreen;
        int timeYellow;
        int timeRed;

    public:
        TrafficLight(const TrafficLight &other);
        TrafficLight& operator=(const TrafficLight& other);
        TrafficLight::TrafficLight(TrafficLight&& other)noexcept;
        TrafficLight& TrafficLight::operator=(TrafficLight&&)noexcept;
};

#endif