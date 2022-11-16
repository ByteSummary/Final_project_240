#ifndef __TRAFFIC_LIGHT_CPP__
#define __TRAFFIC_LIGHT_CPP__

#include <iostream>
#include "VehicleBase.h"
#include "TrafficLight.h"

//Nulltype for LighColor object
LightColor NULLCOLOR;

// empty constructor
TrafficLight::TrafficLight() {
    lightcolor = NULLCOLOR;
    time_green = 0;
    time_yellow = 0;
    time_red = 0;
    time_change = 0;
}

// common use constructor
TrafficLight::TrafficLight(LightColor color, int green, int yellow) {
    lightcolor = color;
    time_green = green;
    time_yellow = yellow;
    time_red = green + yellow;

    if (color == LightColor::red) {
        time_change = 0;
    }
    else if (color == LightColor::yellow) {
        time_change = yellow;
    }
    else if (color == LightColor::green) {
        time_change = green + yellow;
    }

}

// copy constructor
TrafficLight::TrafficLight(const TrafficLight& other):
    lightcolor(other.lightcolor),
    time_green(other.time_green),
    time_yellow(other.time_yellow),
    time_red(other.time_red),
    time_change(other.time_change)
    {}

// copy assignment operator
TrafficLight& TrafficLight::operator=(const TrafficLight& other) {
    if (this == &other) {
        return *this;
    }
    lightcolor = other.lightcolor;
    time_green = other.time_green;
    time_yellow = other.time_yellow;
    time_red = other.time_red;
    time_change = other.time_change;

    return *this;
}

// move constructor
TrafficLight::TrafficLight(TrafficLight&& other)noexcept:
    lightcolor(other.lightcolor),
    time_green(other.time_green),
    time_yellow(other.time_yellow),
    time_red(other.time_red),
    time_change(other.time_change) {
        other.lightcolor = NULLCOLOR;
        other.time_yellow = 0;
        other.time_red = 0;
        other.time_green = 0;
        other.time_change = 0;
    }

// move assginment operator
TrafficLight& TrafficLight::operator=(TrafficLight&& other)noexcept {
    if (this == &other) {
        return *this;
    }
    lightcolor = other.lightcolor;
    time_green = other.time_green;
    time_yellow = other.time_yellow;
    time_red = other.time_red;
    time_change = other.time_change;
    other.lightcolor = NULLCOLOR;
    other.time_yellow = 0;
    other.time_red = 0;
    other.time_green = 0;
    other.time_change = 0;

    return *this;
}

// returns time change of traffic light
int TrafficLight::getTimeChange(){
    return time_change;
}

// checks time change of traffic light and changes color or decrements time change
// depending on the its value
void TrafficLight::timeLightChange(){
    if (time_change == time_yellow)
    {
        setLightColor(LightColor::yellow);
        time_change = time_change - 1;
    }
    else if (time_change == 0)
    {
        setLightColor(LightColor::red);
        time_change = time_green + time_yellow;
    }
    else 
    {
        time_change = time_change - 1;
    }
}

// return light color of traaffic light
LightColor TrafficLight::getLightColor() {
    return lightcolor;
}

// sets light color to newColor
void TrafficLight::setLightColor(LightColor newColor) {
    lightcolor = newColor;
}

// sets light color to green and sets time change to sum of
// time yellow and time green
void TrafficLight::setGreen(){
    setLightColor(LightColor::green);
    time_change = time_green + time_yellow;
}

#endif