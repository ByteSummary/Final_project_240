#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__

#include "VehicleBase.h"

class TrafficLight {

    private:
        LightColor lightcolor;
        int time_green;
        int time_yellow;
        int time_red;
        int time_change;

    public:
        TrafficLight();
        TrafficLight(LightColor color, int green, int yellow);
        TrafficLight(const TrafficLight& other);
        TrafficLight& operator=(const TrafficLight& other);
        TrafficLight(TrafficLight&& other)noexcept;
        TrafficLight& operator=(TrafficLight&&)noexcept;

        int getTimeChange();
        void timeLightChange();
        LightColor getLightColor();
        void setLightColor(LightColor newColor);
        void setGreen();

};

#endif