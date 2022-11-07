#ifndef __TRAFFIC_LIGHT_H__
#define __TRAFFIC_LIGHT_H__

#include "VehicleBase.h"

class TrafficLight {

    private:
        LightColor lightcolor;
        int timeGreen;
        int timeYellow;
        int timeRed;
        int timeChange; // 0 means on red

    public:
        TrafficLight();
        TrafficLight(LightColor color, int green, int yellow);
        TrafficLight(const TrafficLight& other);
        TrafficLight& operator=(const TrafficLight& other);
        TrafficLight(TrafficLight&& other)noexcept;
        TrafficLight& operator=(TrafficLight&&)noexcept;

        // int getTimeGreen();
        // int getTimeYellow();
        // int getTimeRed();
        int getTimeChange();
        void timeLightChange();
        // int getTimeBeforeChange();
        LightColor getLightColor();
        void setLightColor(LightColor newColor);
        void setGreen();

};

#endif