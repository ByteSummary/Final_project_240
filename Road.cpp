#ifndef __ROAD_CPP__
#define __ROAD_CPP__

#include "TrafficLight.h"
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

Road::Road(Direction direction, float spawn_new_vehicle_rate, TrafficLight& stoplight)
    : roadDirection(direction),
      trafficLight(stoplight),
      prob_new_vehicle(spawn_new_vehicle_rate),
      newVehicle(nullptr),
      endVehicle(nullptr)
    {
    roadBound = std::vector<VehicleBase*>(sections_before_intersection * 2 + 2, nullptr);
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
            if (vehicle_pointer_counter == sections_before_intersection - 1)
            {
                /*
                1. Get the light color from the intersection
                2. If color is red, and we can turn right, check if we can turn right then turn right
                3. If color is red, and we cannot turn right, stop.
                4. If color is yellow, check time remaining on yellow and make sure it is greater than the length of vehicle at intersection
                5. If time < length, dont continue, else continue
                6. If color is green, vehicle can continue forward
                7. If color is green and vehicle is going to turn right, turn right.
                */
                // move forward at intersection or turn right
                VehicleBase* vehicle_at_intersection = roadBound[vehicle_pointer_counter];
                vehicle_at_intersection->turnRight(randnum);
                int length_of_vehicle = vehicle_at_intersection->getVehicleLength();
                bool right_turn = vehicle_at_intersection->getWillTurnRight();

                // check light
                int& time_remaining = trafficLight.getTimeChange();
                LightColor& trafficLightColor = trafficLight.getLightColor();
                bool go = true;
                
        

                if (trafficLightColor == LightColor::red)
                {
                    go = false;
                }
                
                // turn right
                else if (right_turn == true)
                {
                    // can turn right
                    if (length_of_vehicle <= time_remaining && go)
                    {
                        vehicle_at_intersection->setIsTurningRight(true);
                        roadBound[vehicle_pointer_counter + 1] = roadBound[vehicle_pointer_counter];
                        roadBound[vehicle_pointer_counter] = nullptr;
                    }
                }
                //go straight
                else if (right_turn == false)
                {
                    // can move straight
                    if (length_of_vehicle <= time_remaining && go)
                    {
                        roadBound[vehicle_pointer_counter + 1] = roadBound[vehicle_pointer_counter];
                        roadBound[vehicle_pointer_counter] = nullptr;
                    }
                }
            }
            // at end of the road
            else if (vehicle_pointer_counter == (sections_before_intersection * 2 + 2) - 1)
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
                if (roadBound[vehicle_pointer_counter + 1] == nullptr)
                {
                    roadBound[vehicle_pointer_counter + 1] = roadBound[vehicle_pointer_counter];
                    roadBound[vehicle_pointer_counter] = nullptr;
                }
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
            float randnumRightTurn = 0.0;
            VehicleType new_vehicle_type = highest_vehicle;
            if (randnum < lowest_proportion)
            {
                new_vehicle_type = lowest_vehicle;
            }
            else if (randnum < lowest_proportion + middle_proportion)
            {
                new_vehicle_type = middle_vehicle;
            }
            newVehicle = new VehicleBase(new_vehicle_type, roadDirection, randnumRightTurn);
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

void Road::changeRoadBound(Road& right_road_bound){
    // move forward at intersection or turn right
    VehicleBase* vehicle_in_intersection = roadBound[sections_before_intersection];
    if (vehicle_in_intersection != nullptr)
    {
        bool is_turning_right = vehicle_in_intersection->getIsTurningRight();
        if (is_turning_right) 
        {
            std::vector<VehicleBase*>& right_road_bound_vector = right_road_bound.getVehicleBaseVector();
            right_road_bound_vector[sections_before_intersection + 1] = vehicle_in_intersection;
            roadBound[sections_before_intersection] = nullptr;
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
