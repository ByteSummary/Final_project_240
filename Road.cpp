#ifndef __ROAD_CPP__
#define __ROAD_CPP__

#include "Road.h"
#include "VehicleBase.h"
#include <vector>
#include <iostream>

int Road::sections_before_intersection = 0;

VehicleType Road::lowest_vehicle = VehicleType::car;
float Road::lowest_proportion = 0.0;
VehicleType Road::middle_vehicle = VehicleType::car;
float Road::middle_proportion = 0.0;
VehicleType Road::highest_vehicle = VehicleType::car;

// Road::Road(){
//     std::vector<VehicleBase*> roadBound;
//     Direction roadDirection;
//     VehicleBase* newVehicle;
//     bool finishedNewVehicle;
// }

Road::Road(Direction direction, float spawn_new_vehicle_rate){
    roadBound = std::vector<VehicleBase*>(sections_before_intersection * 2 + 2, nullptr);
    roadDirection = direction;
    prob_new_vehicle = spawn_new_vehicle_rate;
    newVehicle = nullptr;
    endVehicle = nullptr;
}

// Road::Road(const Road& other){}
// Road& Road::operator=(const Road& other){}
// Road::Road(Road&& other)noexcept{}
// Road& Road::operator=(Road&&)noexcept{}
Road::~Road(){
    if (newVehicle != nullptr) {
        delete newVehicle;
    }
}

void Road::moveVehicles(float randnum){
    // move vehicles forward
    for (int vehicle_pointer_counter = (sections_before_intersection * 2 + 2) - 1; vehicle_pointer_counter >= 0; vehicle_pointer_counter--)
    {
        // checking if pointing to nullptr
        if (roadBound[vehicle_pointer_counter] != nullptr)
        {

            // at intersection
            if (vehicle_pointer_counter + 1 == sections_before_intersection - 1)
            {
                // // move forward at intersection or turn right
                // VehicleType vehicleIntersection = roadBound[vehicle_pointer_counter]->getVehicleType();

                // // turn right
                // if (randnum <= prob_right_turn_for_vehicle)
                // {

                // }
                // // go straight
                // else
                // {

                // }
            }
            // at end of the road
            if (vehicle_pointer_counter == (sections_before_intersection * 2 + 2) - 1)
            {
                if(endVehicle == nullptr)
                {
                    endVehicle = roadBound[vehicle_pointer_counter];
                    roadBound[vehicle_pointer_counter] = nullptr;
                    endVehicle->decrementVehicleLengthCount();
                } 
                else
                {
                    roadBound[vehicle_pointer_counter] = nullptr;
                    endVehicle->decrementVehicleLengthCount();
                    if (endVehicle->getVehicleLengthCount() == 0)
                    {
                        delete endVehicle;
                        endVehicle = nullptr;
                    }
                }
            }
            // not at end of road
            else
            {
                roadBound[vehicle_pointer_counter + 1] = roadBound[vehicle_pointer_counter];
                roadBound[vehicle_pointer_counter] = nullptr;
            }
        }
    }
}

void Road::spawnNewVehicle(float randnum){
    // call function to add vehicles in each road
    if (newVehicle == nullptr)
    {
        // if first section of road is open and randnum is inside probability
        // needs to complete vehicle during creation
        if (roadBound[0] == nullptr && randnum <= prob_new_vehicle)
        {
            // VehicleType new_vehicle_type = VehicleType::car;
            if (randnum <= lowest_proportion)
            {
                // new_vehicle_type = lowest_vehicle;
                newVehicle = new VehicleBase(lowest_vehicle, roadDirection);
            }
            else if (randnum <= lowest_proportion + middle_proportion)
            {
                // new_vehicle_type = middle_vehicle;
                newVehicle = new VehicleBase(middle_vehicle, roadDirection);
            }
            else
            {
                // new_vehicle_type = highest_vehicle;
                newVehicle = new VehicleBase(highest_vehicle, roadDirection);
            }
            // newVehicle = new VehicleBase(new_vehicle_type, roadDirection);
            roadBound[0] = newVehicle;
            newVehicle->incrementVehicleLengthCount();
        }
    }
    else
    {
        roadBound[0] = newVehicle;
        newVehicle->incrementVehicleLengthCount();
        if (newVehicle->getVehicleLengthCount() == newVehicle->getVehicleLength())
        {
            newVehicle = nullptr;
        }
    }
}

void Road::settingVehicleProportions(float proportion_of_cars, float proportion_of_SUVs, float proportion_of_trucks) {
    if (proportion_of_cars < proportion_of_SUVs)
    {
        // cars < suvs
        if (proportion_of_cars < proportion_of_trucks)
        {
            // cars < trucks and suvs
            lowest_proportion = proportion_of_cars;
            lowest_vehicle = VehicleType::car;
            if (proportion_of_trucks < proportion_of_SUVs)
            {
                // cars < trucks < suvs
                middle_proportion = proportion_of_trucks;
                middle_vehicle = VehicleType::truck;
                highest_vehicle = VehicleType::suv;
                std::cout << "cars < trucks < suvs" << std::endl;
            }
            else
            {
                // cars < suvs < trucks
                middle_proportion = proportion_of_SUVs;
                middle_vehicle = VehicleType::suv;
                highest_vehicle = VehicleType::truck;
                std::cout << "cars < suvs < trucks" << std::endl;
            }
        }
        else
        {
            // trucks < car < suvs
            lowest_proportion = proportion_of_trucks;
            lowest_vehicle = VehicleType::truck;
            middle_proportion = proportion_of_cars;
            middle_vehicle = VehicleType::car;
            highest_vehicle = VehicleType::suv;
            std::cout << "trucks < car < suvs" << std::endl;
        }
    }
    else
    {
        // suvs < cars
        if (proportion_of_SUVs < proportion_of_trucks)
        {
            // suvs < trucks and cars
            lowest_proportion = proportion_of_SUVs;
            lowest_vehicle = VehicleType::suv;
            if (proportion_of_trucks < proportion_of_cars)
            {
                // suvs < trucks < cars
                middle_proportion = proportion_of_trucks;
                middle_vehicle = VehicleType::truck;
                highest_vehicle = VehicleType::car;
                std::cout << "suvs < trucks < cars" << std::endl;
            }
            else
            {
                // suvs < cars < trucks
                middle_proportion = proportion_of_cars;
                middle_vehicle = VehicleType::car;
                highest_vehicle = VehicleType::truck;
                std::cout << "suvs < cars < trucks" << std::endl;
            }
        }
        else
        {
            // trucks < suvs < cars
            lowest_proportion = proportion_of_trucks;
            lowest_vehicle = VehicleType::truck;
            middle_proportion = proportion_of_SUVs;
            middle_vehicle = VehicleType::suv;
            highest_vehicle = VehicleType::car;
            std::cout << "trucks < suvs < cars" << std::endl;
        }
    }
}

#endif
