#ifndef __ROAD_CPP__
#define __ROAD_CPP__

#include "TrafficLight.h"
#include "Road.h"
#include "VehicleBase.h"
#include <vector>
#include <iostream>

//Create nulltypes for constructors
VehicleType NULLTYPE;
Direction NULLDIRECTION;
TrafficLight NULLTRAFFICLIGHT;

int Road::sections_before_intersection = 0;

VehicleType Road::lowest_vehicle = VehicleType::car;
float Road::lowest_proportion = 0.0;
VehicleType Road::middle_vehicle = VehicleType::car;
float Road::middle_proportion = 0.0;
VehicleType Road::highest_vehicle = VehicleType::car;

Road::Road(Direction direction, float spawn_new_vehicle_rate, TrafficLight& stop_light)
    : road_Direction(direction),
      traffic_Light(stop_light),
      prob_new_vehicle(spawn_new_vehicle_rate),
      new_Vehicle(nullptr),
      end_Vehicle(nullptr)
    {
    road_Bound = std::vector<VehicleBase*>(sections_before_intersection * 2 + 2, nullptr);
}

//Copy constructor
Road::Road(const Road& other):
    road_Direction(other.road_Direction),
    traffic_Light(other.traffic_Light),
    prob_new_vehicle(other.prob_new_vehicle),
    new_Vehicle(other.new_Vehicle),
    end_Vehicle(other.end_Vehicle)
{}

//Copy assignment operator
Road& Road::operator=(const Road& other){
    if(this == &other) {
        return *this;
    }
    road_Direction = other.road_Direction;
    traffic_Light = other.traffic_Light;
    prob_new_vehicle = other.prob_new_vehicle;
    new_Vehicle = other.new_Vehicle;
    end_Vehicle = other.end_Vehicle;

    return *this;
}

//Move constructor
Road::Road(Road&& other)noexcept:
    road_Direction(other.road_Direction),
    traffic_Light(other.traffic_Light),
    prob_new_vehicle(other.prob_new_vehicle),
    new_Vehicle(other.new_Vehicle),
    end_Vehicle(other.end_Vehicle) {
        other.road_Direction = NULLDIRECTION;
        other.traffic_Light = NULLTRAFFICLIGHT;
        other.prob_new_vehicle = 0;
        other.new_Vehicle = nullptr;
        other.end_Vehicle = nullptr;
    }
//Move assignment operator
Road& Road::operator=(Road&& other)noexcept{
    if (this == &other) {
        return *this;
    }
    road_Direction = other.road_Direction;
    traffic_Light = other.traffic_Light;
    prob_new_vehicle = other.prob_new_vehicle;
    new_Vehicle = other.new_Vehicle;
    end_Vehicle = other.end_Vehicle;
    other.road_Direction = NULLDIRECTION;
    other.traffic_Light = NULLTRAFFICLIGHT;
    other.prob_new_vehicle = 0;
    other.new_Vehicle = nullptr;
    other.end_Vehicle = nullptr;
    
    return *this;
    }

//Destructor
Road::~Road(){
    VehicleBase* vehicle_pointer = road_Bound[0];

    for (int pointer_counter = 1; pointer_counter < (sections_before_intersection * 2 + 2); pointer_counter++)
    {
        VehicleBase* next_vehicle_pointer = road_Bound[pointer_counter];
        if (pointer_counter == (sections_before_intersection * 2 + 2) - 1)
        {
            delete next_vehicle_pointer;
            break;
        } else if (vehicle_pointer != next_vehicle_pointer)
        {
            delete vehicle_pointer;
            vehicle_pointer = next_vehicle_pointer;
        }
    }
}

//Function that will move vehicles and changes functionality if vechile is about to go into an intersection
void Road::moveVehicles(){
    // move vehicles forward
    for (int vehicle_pointer_counter = (sections_before_intersection * 2 + 2) - 1; vehicle_pointer_counter >= 0; vehicle_pointer_counter--)
    {
        // checking if pointing to nullptr
        if (road_Bound[vehicle_pointer_counter] != nullptr)
        {
            // at intersection
            if (vehicle_pointer_counter == sections_before_intersection - 1)
            {
                // getting vehicle and its details
                VehicleBase* vehicle_at_intersection = road_Bound[vehicle_pointer_counter];
                int length_of_vehicle = vehicle_at_intersection->getVehicleLength();
                bool right_turn = vehicle_at_intersection->getWillTurnRight();
                bool is_crossing_intersection = vehicle_at_intersection->getIsCrossingIntersection();

                // checking traffic light: how much time is left and what color it is
                int time_remaining = traffic_Light.getTimeChange();
                LightColor trafficLightColor = traffic_Light.getLightColor();

                // go is true when light is not red 
                bool go = true;
                if (trafficLightColor == LightColor::red)
                {
                    go = false;
                }
                
                // turn right and has not started
                if (right_turn == true && is_crossing_intersection == false)
                {
                    // takes length + 1 to leave intersection when turning right
                    int length_of_vehicle_right = length_of_vehicle + 1;

                    // can turn right
                    if (length_of_vehicle_right <= time_remaining && go)
                    {
                        // is starting to move
                        vehicle_at_intersection->setIsCrossingIntersection(true);

                        // advance vehicle one square forward
                        road_Bound[vehicle_pointer_counter + 1] = road_Bound[vehicle_pointer_counter];
                        road_Bound[vehicle_pointer_counter] = nullptr;
                    }
                }
                // turn right and has started
                else if (right_turn == true && is_crossing_intersection == true)
                {
                    // advance vehicle one square forward
                    road_Bound[vehicle_pointer_counter + 1] = road_Bound[vehicle_pointer_counter];
                    road_Bound[vehicle_pointer_counter] = nullptr;
                }
                //go straight and has not started
                else if (right_turn == false && is_crossing_intersection == false)
                {
                    // takes length + 2 to leave intersection when going straight
                    int length_of_vehicle_straight = length_of_vehicle + 2;

                    // can move straight
                    if (length_of_vehicle_straight <= time_remaining && go)
                    {
                        // is starting to move
                        vehicle_at_intersection->setIsCrossingIntersection(true);
                        
                        // advance vehicle one square forward
                        road_Bound[vehicle_pointer_counter + 1] = road_Bound[vehicle_pointer_counter];
                        road_Bound[vehicle_pointer_counter] = nullptr;
                    }
                }
                else
                {
                    // advance vehicle one square forward
                    road_Bound[vehicle_pointer_counter + 1] = road_Bound[vehicle_pointer_counter];
                    road_Bound[vehicle_pointer_counter] = nullptr;
                }
            }
            // at end of the road
            else if (vehicle_pointer_counter == (sections_before_intersection * 2 + 2) - 1)
            {
                // checks if there is a vehicle currently leaving road
                if(end_Vehicle == nullptr)
                {
                    // sets end vehicle to vehicle at end of road
                    end_Vehicle = road_Bound[vehicle_pointer_counter];

                    // makes vehicle disappear from road
                    road_Bound[vehicle_pointer_counter] = nullptr;

                    // decrement vehicle length count to know how much vehicle is still on road
                    end_Vehicle->decrementVehicleLengthCount();
                } 
                else
                {
                    // makes vehicle disappear from road
                    road_Bound[vehicle_pointer_counter] = nullptr;

                    // decrement vehicle length count to know how much vehicle is still on road
                    end_Vehicle->decrementVehicleLengthCount();

                    // checks if all of vehicle is off the road
                    if (end_Vehicle->getVehicleLengthCount() == 0)
                    {
                        // deletes the vehicle
                        delete end_Vehicle;

                        // sets end vehicle to nullptr
                        end_Vehicle = nullptr;
                    }
                }
            }
            // not at end of road
            else
            {
                // checks if space ahead is empty
                if (road_Bound[vehicle_pointer_counter + 1] == nullptr)
                {
                    // advance vehicle one square forward
                    road_Bound[vehicle_pointer_counter + 1] = road_Bound[vehicle_pointer_counter];
                    road_Bound[vehicle_pointer_counter] = nullptr;
                }
            }
        }
    }
}

void Road::spawnNewVehicle(float randnumSpawn, float randnumRightTurn){
    // call function to add vehicles in each road
    // checks if vehicle is already being added and if first section of road is open
    if (new_Vehicle == nullptr && road_Bound[0] == nullptr)
    {
        // checks if randnum is inside probability
        if (randnumSpawn < prob_new_vehicle)
        {
            // determines type of vehicle to be made based on randnum and proportions
            VehicleType new_vehicle_type = highest_vehicle;
            if (randnumSpawn < lowest_proportion)
            {
                new_vehicle_type = lowest_vehicle;
            }
            else if (randnumSpawn < lowest_proportion + middle_proportion)
            {
                new_vehicle_type = middle_vehicle;
            }
            new_Vehicle = new VehicleBase(new_vehicle_type, road_Direction, randnumRightTurn);
            road_Bound[0] = new_Vehicle;
            new_Vehicle->incrementVehicleLengthCount();
        }
    }
    else
    {
        road_Bound[0] = new_Vehicle;
        new_Vehicle->incrementVehicleLengthCount();
        if (new_Vehicle->getVehicleLengthCount() == new_Vehicle->getVehicleLength())
        {
            new_Vehicle = nullptr;
        }
    }
}

//This function will change direction of the vehicle
void Road::changeRoadBound(Road& right_road_bound){
    // move forward at intersection or turn right
    VehicleBase* vehicle_in_intersection = road_Bound[sections_before_intersection];
    if (vehicle_in_intersection != nullptr)
    {
        bool is_crossing_intersection = vehicle_in_intersection->getIsCrossingIntersection();
        if (is_crossing_intersection) 
        {
            std::vector<VehicleBase*>& right_road_bound_vector = right_road_bound.getVehicleBaseVector();
            right_road_bound_vector[sections_before_intersection + 1] = vehicle_in_intersection;
            road_Bound[sections_before_intersection] = nullptr;
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
