#include "RoadIntersection.h"
#include "VehicleBase.h"


RoadSection *RoadSection::getNext() {
    switch(getVehicleOriginalDirection()) {
        case Direction::north:
            return north;
            break;
        case Direction::east:
            return east;
            break;
        case Direction::south:
            return south;
            break;
        case Direction::west:
            return west;
            break;
    }
}
RoadSection *RoadSection::getPrevious() {
    switch(getVehicleOriginalDirection()) {
        case Direction::north:
            return south;
            break;
        case Direction::east:
            return west;
            break;
        case Direction::south:
            return north;
            break;
        case Direction::west:
            return east;
            break;
    }
}

RoadIntersection *RoadIntersection::getRightTurn();
RoadIntersection *RoadIntersection::getNorth() {
    return north;
}
RoadIntersection *RoadIntersection::getEast() {
    return east;
}
RoadIntersection *RoadIntersection::getSouth() {
    return south;
}
RoadIntersection *RoadIntersection::getWest() {
    return west;
}

void RoadIntersection::setNorth(RoadIntersection *section) {
    north = secion;
}
void RoadIntersection::setEast(RoadIntersection *section) {
    east = section;
}
void RoadIntersection::setSouth(RoadIntersection *section) {
    south = section;
}
void RoadIntersection::setWest(RoadIntersection *section) {
    west = section;
}