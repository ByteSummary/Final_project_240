#ifndef TRAFFIC_LIGHT_CPP
#define TRAFFIC_LIGHT_CPP

#include <iostream>
#include "VehicleBase.h"
#include "TrafficLight.h"


TrafficLight::TrafficLight(LightColor color, int green, int yellow, int red) {
    lightcolor = color;
    timeGreen = green;
    timeYellow = yellow;
    timeRed = red;

    if (color == LightColor::red) {
        timeRed = red;
    }
    else if (color == LightColor::yellow) {
        timeYellow = yellow;
    }
    else if (color == LightColor::green) {
        timeGreen = green;
    }

}

LightColor TrafficLight::getLightColor() {
        return lightcolor;
    }

LightColor TrafficLight::setLightColor(LightColor c) {
    lightcolor = c;
}

// TrafficLight::TrafficLight(const TrafficLight& other):
//     timeGreen(other.timeGreen),
//     timeYellow(other.timeYellow),
//     timeRed(other.timeRed),
//     timeChange(other.timeGreen)
//     {}


// TrafficLight& TrafficLight::operator=(const TrafficLight& other) {
//     if (this == &other) {
//         return *this;
//     }

//     timeGreen = other.timeGreen;
//     timeYellow = other.timeYellow;
//     timeRed = other.timeRed;
//     timeChange = other.timeChange;

//     return *this;
// }

// TrafficLight::TrafficLight(TrafficLight&& other)noexcept:
//     timeGreen(other.timeGreen),
//     timeYellow(other.timeYellow),
//     timeRed(other.timeRed),
//     timeChange(other.timeGreen) {
//         other.timeGreen = 0;
//         other.timeYellow = 0;
//         other.timeRed = 0;
//         other.timeGreen = 0;
//     }

// TrafficLight& TrafficLight::operator=(TrafficLight&& other)noexcept {
//     if (this == &other) {
//         return *this;
//     }
//     timeGreen = other.timeGreen;
//     timeYellow = other.timeYellow;
//     timeRed = other.timeRed;
//     timeChange = other.timeGreen;
//     other.timeGreen = 0;
//     other.timeYellow = 0;
//     other.timeRed = 0;
//     other.timeGreen = 0;
// }
















#endif