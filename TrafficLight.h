#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "VehicleBase.h"

class TrafficLight {

    private:
        LightColor lightcolor;
        int timeGreen;
        int timeYellow;
        int timeRed;
        int timeChange;

    public:
        TrafficLight(LightColor color, int green, int yellow, int red);
        // TrafficLight(const TrafficLight& other);
        // TrafficLight& operator=(const TrafficLight& other);
        // TrafficLight(TrafficLight&& other)noexcept;
        // TrafficLight& operator=(TrafficLight&&)noexcept;

        int getTimeGreen();
        int getTimeYellow();
        int getTimeRed();
        int getTimeBeforeChange();
        LightColor getLightColor();
        LightColor setLightColor(LightColor newColor);

};

#endif