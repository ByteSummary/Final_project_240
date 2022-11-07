#ifndef __TRAFFIC_LIGHT_CPP__
#define __TRAFFIC_LIGHT_CPP__

#include <iostream>
#include "VehicleBase.h"
#include "TrafficLight.h"

LightColor NULLCOLOR;

TrafficLight::TrafficLight() {
    lightcolor = NULLCOLOR;
    timeGreen = 0;
    timeYellow = 0;
    timeRed = 0;
    timeChange = 0;
}

TrafficLight::TrafficLight(LightColor color, int green, int yellow) {
    lightcolor = color;
    timeGreen = green;
    timeYellow = yellow;
    timeRed = green + yellow;

    if (color == LightColor::red) {
        timeChange = 0;
    }
    else if (color == LightColor::yellow) {
        timeChange = yellow;
    }
    else if (color == LightColor::green) {
        timeChange = green + yellow;
    }

}

TrafficLight::TrafficLight(const TrafficLight& other):
    lightcolor(other.lightcolor),
    timeGreen(other.timeGreen),
    timeYellow(other.timeYellow),
    timeRed(other.timeRed),
    timeChange(other.timeChange)
    {}


TrafficLight& TrafficLight::operator=(const TrafficLight& other) {
    if (this == &other) {
        return *this;
    }
    lightcolor = other.lightcolor;
    timeGreen = other.timeGreen;
    timeYellow = other.timeYellow;
    timeRed = other.timeRed;
    timeChange = other.timeChange;

    return *this;
}

TrafficLight::TrafficLight(TrafficLight&& other)noexcept:
    lightcolor(other.lightcolor),
    timeGreen(other.timeGreen),
    timeYellow(other.timeYellow),
    timeRed(other.timeRed),
    timeChange(other.timeChange) {
        other.lightcolor = NULLCOLOR;
        other.timeYellow = 0;
        other.timeRed = 0;
        other.timeGreen = 0;
        other.timeChange = 0;
    }

TrafficLight& TrafficLight::operator=(TrafficLight&& other)noexcept {
    if (this == &other) {
        return *this;
    }
    lightcolor = other.lightcolor;
    timeGreen = other.timeGreen;
    timeYellow = other.timeYellow;
    timeRed = other.timeRed;
    timeChange = other.timeChange;
    other.lightcolor = NULLCOLOR;
    other.timeYellow = 0;
    other.timeRed = 0;
    other.timeGreen = 0;
    other.timeChange = 0;
}

int TrafficLight::getTimeChange(){
    return timeChange;
}

void TrafficLight::timeLightChange(){
    if (timeChange == timeYellow)
    {
        setLightColor(LightColor::yellow);
        timeChange = timeChange - 1;
    }
    else if (timeChange == 0)
    {
        setLightColor(LightColor::red);
        timeChange = timeGreen + timeYellow;
    }
    else 
    {
        timeChange = timeChange - 1;
    }
}

LightColor TrafficLight::getLightColor() {
    return lightcolor;
}

void TrafficLight::setLightColor(LightColor newColor) {
    lightcolor = newColor;
}

void TrafficLight::setGreen(){
    setLightColor(LightColor::green);
    timeChange = timeGreen + timeYellow;
}

#endif