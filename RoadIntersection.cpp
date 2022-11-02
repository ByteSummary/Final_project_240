#include <iostream>
#include "RoadIntersection.h"
#include "VehicleBase.h"

RoadSection *RoadSection::getNext()
{
    switch (getVehicleOriginalDirection())
    {
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
RoadSection *RoadSection::getPrevious()
{
    switch (getVehicleOriginalDirection())
    {
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
RoadIntersection *RoadIntersection::getNorth()
{
    return this->north;
}
RoadIntersection *RoadIntersection::getEast()
{
    return this->east;
}
RoadIntersection *RoadIntersection::getSouth()
{
    return this->south;
}
RoadIntersection *RoadIntersection::getWest()
{
    return this->west;
}

void RoadIntersection::setNorth(RoadIntersection *north)
{
    this->north = north;
}
void RoadIntersection::setEast(RoadIntersection *east)
{
    this->east = east;
}
void RoadIntersection::setSouth(RoadIntersection *south)
{
    this->south = south;
}
void RoadIntersection::setWest(RoadIntersection *west)
{
    this->west = west;
}