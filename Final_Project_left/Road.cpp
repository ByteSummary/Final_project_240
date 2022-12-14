#ifndef __ROAD_CPP__
#define __ROAD_CPP__

#include "TrafficLight.h"
#include "Road.h"
#include "VehicleBase.h"
#include <vector>
#include <queue>

//Create nulltypes for constructors
Direction NULLROADDIRECTION;
TrafficLight NULLTRAFFICLIGHT;

int Road::sections_before_intersection = 0;

VehicleType Road::lowest_vehicle = VehicleType::car;
float Road::lowest_proportion = 0.0;
VehicleType Road::middle_vehicle = VehicleType::car;
float Road::middle_proportion = 0.0;
VehicleType Road::highest_vehicle = VehicleType::car;

bool Road::left_turn_happening = false;
int Road::left_turn_count = 0;

Road::Road(Direction direction, float spawn_new_vehicle_rate, TrafficLight& stop_light)
    : road_direction(direction),
      traffic_light(stop_light),
      prob_new_vehicle(spawn_new_vehicle_rate),
      new_vehicle(nullptr),
      end_vehicle(nullptr)
{
    road_bound = std::vector<VehicleBase*>(sections_before_intersection * 2 + 2, nullptr);
}

//Copy constructor
Road::Road(const Road& other):
    road_direction(other.road_direction),
    traffic_light(other.traffic_light),
    prob_new_vehicle(other.prob_new_vehicle),
    new_vehicle(other.new_vehicle),
    end_vehicle(other.end_vehicle)
{}

//Copy assignment operator
Road& Road::operator=(const Road& other){
    if(this == &other) {
        return *this;
    }
    road_direction = other.road_direction;
    traffic_light = other.traffic_light;
    prob_new_vehicle = other.prob_new_vehicle;
    new_vehicle = other.new_vehicle;
    end_vehicle = other.end_vehicle;

    return *this;
}

//Move constructor
Road::Road(Road&& other)noexcept:
    road_direction(other.road_direction),
    traffic_light(other.traffic_light),
    prob_new_vehicle(other.prob_new_vehicle),
    new_vehicle(other.new_vehicle),
    end_vehicle(other.end_vehicle) {
        other.road_direction = NULLROADDIRECTION;
        other.traffic_light = NULLTRAFFICLIGHT;
        other.prob_new_vehicle = 0;
        other.new_vehicle = nullptr;
        other.end_vehicle = nullptr;
    }

//Move assignment operator
Road& Road::operator=(Road&& other)noexcept{
    if (this == &other) {
        return *this;
    }
    road_direction = other.road_direction;
    traffic_light = other.traffic_light;
    prob_new_vehicle = other.prob_new_vehicle;
    new_vehicle = other.new_vehicle;
    end_vehicle = other.end_vehicle;
    other.road_direction = NULLROADDIRECTION;
    other.traffic_light = NULLTRAFFICLIGHT;
    other.prob_new_vehicle = 0;
    other.new_vehicle = nullptr;
    other.end_vehicle = nullptr;
    
    return *this;
    }

//Destructor
Road::~Road(){
    // gets vehicle at start of road if any
    VehicleBase* vehicle_pointer = road_bound[0];

    // loops through all sections of a road
    for (int pointer_counter = 1; pointer_counter < (sections_before_intersection * 2 + 2); pointer_counter++)
    {
        // gets vehicle at section of road at pointer counter
        VehicleBase* next_vehicle_pointer = road_bound[pointer_counter];

        // checks if pointer counter is at end of the road
        if (pointer_counter == (sections_before_intersection * 2 + 2) - 1)
        {
            // checks if pointer counter is pointing to null pointer
            if (next_vehicle_pointer != nullptr)
            {
                // deletes vehicle
                delete next_vehicle_pointer;
            }
            break;
        } 
        // checkes if vehicle pointer and next vehicle pointer are pointing to the same thing
        else if (vehicle_pointer != next_vehicle_pointer)
        {
            // checks if vehicle counter is pointing to null pointer
            if (vehicle_pointer != nullptr)
            {
                // deletes vehicle
                delete vehicle_pointer;
            }

            // vehicle pointer points to what next vehicle pointer is pointing to 
            vehicle_pointer = next_vehicle_pointer;
        }
    }
}

void Road::startLeftTurn(Road& same_road_go, std::queue<VehicleBase*>* vehicle_left_queue){
    // checking traffic light: how much time is left and what color it is
    int time_remaining = traffic_light.getTimeChange();
    LightColor trafficLightColor = traffic_light.getLightColor();

    // go is true when light is not red 
    bool go = true;
    if (trafficLightColor == LightColor::red)
    {
        go = false;
    }

    // checks if queue is empty and if there is a left turn already happening
    if (!vehicle_left_queue->empty() && left_turn_happening == false)
    {
        // gets vehicle at front of the queue and its direction
        VehicleBase* vehicle_planned_left_turn = vehicle_left_queue->front();
        Direction vehicle_planned_left_turn_direction = vehicle_planned_left_turn->getVehicleOriginalDirection();

        // checks if direction of vehicle at front of queue is the same as direction of road
        if (vehicle_planned_left_turn_direction == road_direction)
        {
            // getting length of vehicle
            int length_of_vehicle = vehicle_planned_left_turn->getVehicleLength();

            // takes length + 2 to leave intersection when turning left
            int length_of_vehicle_left = length_of_vehicle + 2;

            // initializing value to determine if vehicle can make left turn
            bool no_vehicles_in_other_road = true;

            // getting vector of the other road that goes on green (west/east, north/south)
            std::vector<VehicleBase*>& other_road_bound_vector = same_road_go.getVehicleBaseVector();

            // checks if vehicle size is greater than 1
            // if queue is greater than 1 then it means that both vehicles on the two roads want to turn left
            if (vehicle_left_queue->size() > 1)
            {
                // can turn left
                if (length_of_vehicle_left <= time_remaining && go)
                {
                    // is starting to move
                    road_bound[sections_before_intersection - 1]->setIsCrossingIntersection(true);

                    // popping queue to indicate that vehicle is starting to turn and is no longer waiting
                    vehicle_left_queue->pop();

                    // declaring that left turn is occurring
                    left_turn_happening = true;

                    // advance vehicle one square forward
                    road_bound[sections_before_intersection] = vehicle_planned_left_turn;
                    road_bound[sections_before_intersection - 1] = nullptr;
                }
            }
            else
            {
                // checking if there are enough sections free on the other side of the road
                for (int vehicle_pointer_counter = sections_before_intersection; vehicle_pointer_counter >= (sections_before_intersection - length_of_vehicle_left); vehicle_pointer_counter--)
                {
                    if (other_road_bound_vector[vehicle_pointer_counter] != nullptr)
                    {
                        no_vehicles_in_other_road = false;
                        break;
                    }
                }

                // checking if it is safe for vehicle to make turn
                if (no_vehicles_in_other_road == true)
                {
                    // can turn left
                    if (length_of_vehicle_left <= time_remaining && go)
                    {
                        // is starting to move
                        road_bound[sections_before_intersection - 1]->setIsCrossingIntersection(true);
                        
                        // popping queue to indicate that vehicle is starting to turn and is no longer waiting
                        vehicle_left_queue->pop();

                        // declaring that left turn is occurring
                        left_turn_happening = true;

                        // advance vehicle one square forward
                        road_bound[sections_before_intersection] = vehicle_planned_left_turn;
                        road_bound[sections_before_intersection - 1] = nullptr;
                    }
                }
            }
        }
    }
}

//Function that will move vehicles and changes functionality if vehicle is about to go into an intersection
void Road::moveVehicles(int vehicle_pointer_counter, Road& left_road_bound, Road& same_road_go, std::queue<VehicleBase*>* vehicle_left_queue){
    // move vehicles forward
    // checking if pointing to nullptr
    if (road_bound[vehicle_pointer_counter] != nullptr)
    {
        // at point before intersection
        if (vehicle_pointer_counter == sections_before_intersection - 1)
        {
            // getting vehicle and its details
            VehicleBase* vehicle_at_intersection = road_bound[vehicle_pointer_counter];
            int length_of_vehicle = vehicle_at_intersection->getVehicleLength();
            bool right_turn = vehicle_at_intersection->getWillTurnRight();
            bool left_turn = vehicle_at_intersection->getWillTurnLeft();
            bool is_crossing_intersection = vehicle_at_intersection->getIsCrossingIntersection();

            // checking traffic light: how much time is left and what color it is
            int time_remaining = traffic_light.getTimeChange();
            LightColor trafficLightColor = traffic_light.getLightColor();

            // go is true when light is not red 
            bool go = true;
            if (trafficLightColor == LightColor::red)
            {
                go = false;
            }
            
            // turn right and has not started
            if (right_turn == true && left_turn == false && is_crossing_intersection == false)
            {
                // takes length + 1 to leave intersection when turning right
                int length_of_vehicle_right = length_of_vehicle + 1;

                // can turn right
                if (length_of_vehicle_right <= time_remaining && go)
                {
                    // is starting to move
                    vehicle_at_intersection->setIsCrossingIntersection(true);

                    // advance vehicle one square forward
                    road_bound[vehicle_pointer_counter + 1] = road_bound[vehicle_pointer_counter];
                    road_bound[vehicle_pointer_counter] = nullptr;
                }
            }
            // turn left and has not started
            else if (right_turn == false && left_turn == true && is_crossing_intersection == false)
            {
                // start left turn if possible
                startLeftTurn(same_road_go, vehicle_left_queue);
            }
            //go straight and has not started
            else if (right_turn == false && left_turn == false && is_crossing_intersection == false)
            {
                // takes length + 2 to leave intersection when going straight
                int length_of_vehicle_straight = length_of_vehicle + 2;

                // can move straight
                if (length_of_vehicle_straight <= time_remaining && go)
                {
                    // is starting to move
                    vehicle_at_intersection->setIsCrossingIntersection(true);
                    
                    // advance vehicle one square forward
                    road_bound[vehicle_pointer_counter + 1] = road_bound[vehicle_pointer_counter];
                    road_bound[vehicle_pointer_counter] = nullptr;
                }
            }
            // has started turning right, left or straight
            else
            {
                // advance vehicle one square forward
                road_bound[vehicle_pointer_counter + 1] = road_bound[vehicle_pointer_counter];
                road_bound[vehicle_pointer_counter] = nullptr;
            }
        }
        // at start of intersection
        else if (vehicle_pointer_counter == sections_before_intersection)
        {
            // getting vehicle and its details
            VehicleBase* vehicle_at_intersection = road_bound[vehicle_pointer_counter];
            bool left_turn = vehicle_at_intersection->getWillTurnLeft();

            // checking if vehicle is making a left turn
            if (left_turn == false)
            {
                // checks if space ahead is empty
                if (road_bound[vehicle_pointer_counter + 1] == nullptr)
                {
                    // advance vehicle one square forward
                    road_bound[vehicle_pointer_counter + 1] = vehicle_at_intersection;
                    road_bound[vehicle_pointer_counter] = nullptr;
                }
            }
            else
            {
                // will change road bounds and change section vehicle is in
                changeRoadBoundLeft(left_road_bound);
            }
        }
        // at end of intersection
        else if (vehicle_pointer_counter == sections_before_intersection + 1)
        {
            // getting vehicle and its details
            VehicleBase* vehicle_at_intersection = road_bound[vehicle_pointer_counter];
            bool left_turn = vehicle_at_intersection->getWillTurnLeft();
            bool left_switched_bounds = vehicle_at_intersection->getHasSwitchedBoundsLeft();

            // checking if vehicle is making left turn and if it has switched bounds if it is
            if (left_turn == false || (left_turn == true && left_switched_bounds == false))
            {
                // checks if space ahead is empty
                if (road_bound[vehicle_pointer_counter + 1] == nullptr)
                {
                    // advance vehicle one square forward
                    road_bound[vehicle_pointer_counter + 1] = vehicle_at_intersection;
                    road_bound[vehicle_pointer_counter] = nullptr;

                    // checking if vehicle is making left turn
                    if (left_turn == true)
                    {
                        // increase left turn count by 1
                        left_turn_count++;

                        // checking if left turn count is equal to length of vehicle
                        if (left_turn_count == vehicle_at_intersection->getVehicleLength())
                        {
                            // left turn is finished
                            left_turn_happening = false;

                            // reset left turn count to 0
                            left_turn_count = 0;
                        }
                    }
                }
            }  
        }
        // at end of the road
        else if (vehicle_pointer_counter == (sections_before_intersection * 2 + 2) - 1)
        {
            // checks if there is a vehicle currently leaving road
            if(end_vehicle == nullptr)
            {
                // sets end vehicle to vehicle at end of road
                end_vehicle = road_bound[vehicle_pointer_counter];

                // makes vehicle disappear from road
                road_bound[vehicle_pointer_counter] = nullptr;

                // decrement vehicle length count to know how much vehicle is still on road
                end_vehicle->decrementVehicleLengthCount();
            } 
            else
            {
                // makes vehicle disappear from road
                road_bound[vehicle_pointer_counter] = nullptr;

                // decrement vehicle length count to know how much vehicle is still on road
                end_vehicle->decrementVehicleLengthCount();

                // checks if all of vehicle is off the road
                if (end_vehicle->getVehicleLengthCount() == 0)
                {
                    // deletes the vehicle
                    delete end_vehicle;

                    // sets end vehicle to nullptr
                    end_vehicle = nullptr;
                }
            }
        }
        // not at section before intersection, at intersection or end of the road
        else
        {
            // checks if space ahead is empty
            if (road_bound[vehicle_pointer_counter + 1] == nullptr)
            {
                // advance vehicle one square forward
                road_bound[vehicle_pointer_counter + 1] = road_bound[vehicle_pointer_counter];
                road_bound[vehicle_pointer_counter] = nullptr;
            }
        }
    }
}

void Road::spawnNewVehicle(float randnumSpawn, float randnumRightTurn){
    // call function to add vehicles in each road
    // checks if vehicle is already being added and if first section of road is open
    if (new_vehicle == nullptr)
    {
        // checks if randnum is inside probability
        if (road_bound[0] == nullptr && randnumSpawn < prob_new_vehicle)
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
            // creates new vehicle and places it at start of road
            new_vehicle = new VehicleBase(new_vehicle_type, road_direction, randnumRightTurn);
            road_bound[0] = new_vehicle;
            new_vehicle->incrementVehicleLengthCount();
        }
    }
    else
    {
        // checks if new part of vehicle can be placed
        if (road_bound[0] == nullptr)
        {
            // add new part of vehicle at start of road
            road_bound[0] = new_vehicle;
            new_vehicle->incrementVehicleLengthCount();

            // stops adding part of vehicle when length is appropriate
            if (new_vehicle->getVehicleLengthCount() == new_vehicle->getVehicleLength())
            {
                new_vehicle = nullptr;
            }
        }
    }
}

//This function will change direction of the vehicle when turning right
void Road::changeRoadBoundRight(Road& right_road_bound){
    // changing road of vehicle
    VehicleBase* vehicle_in_intersection = road_bound[sections_before_intersection];

    // checks if there is a vehicle at start of intersection
    if (vehicle_in_intersection != nullptr)
    {
        // gets details of vehicle
        bool right_turn = vehicle_in_intersection->getWillTurnRight();
        bool left_turn = vehicle_in_intersection->getWillTurnLeft();
        bool is_crossing_intersection = vehicle_in_intersection->getIsCrossingIntersection();

        // checks if vehicle is making right turn and has started
        if (right_turn == true && left_turn == false && is_crossing_intersection == true) 
        {
            // add vehicle to other road vector it is turning to
            std::vector<VehicleBase*>& right_road_bound_vector = right_road_bound.getVehicleBaseVector();
            right_road_bound_vector[sections_before_intersection + 1] = vehicle_in_intersection;

            // remove from current road vector
            road_bound[sections_before_intersection] = nullptr;
        }
    }
}

//This function will change direction of the vehicle when turning left
void Road::changeRoadBoundLeft(Road& left_road_bound){
    // changing road of vehicle
    VehicleBase* vehicle_in_intersection = road_bound[sections_before_intersection];

    // checks if there is a vehicle at start of intersection
    if (vehicle_in_intersection != nullptr)
    {
        // gets details of vehicle
        bool right_turn = vehicle_in_intersection->getWillTurnRight();
        bool left_turn = vehicle_in_intersection->getWillTurnLeft();
        bool is_crossing_intersection = vehicle_in_intersection->getIsCrossingIntersection();

        // checks if vehicle is making left turn and has started
        if (right_turn == false && left_turn == true && is_crossing_intersection == true) 
        {
            // change value of has switched bounds
            vehicle_in_intersection->setHasSwitchedBoundsLeft(true);

            // add vehicle to other road vector it is turning to
            std::vector<VehicleBase*>& left_road_bound_vector = left_road_bound.getVehicleBaseVector();
            left_road_bound_vector[sections_before_intersection + 1] = vehicle_in_intersection;

            // remove from current vector
            road_bound[sections_before_intersection] = nullptr;
        }
    }
}

// This function will add a vehicle to the queue that are for left turning vehicles
void Road::addToLeftQueue(std::queue<VehicleBase*>* vehicle_left_queue){
    // add vehicle to queue if turning left
    VehicleBase* vehicle_in_intersection = road_bound[sections_before_intersection - 1];

    // checks if there is a vehicle at section right before start of intersection
    if (vehicle_in_intersection != nullptr)
    {
        // gets details of vehicle
        bool right_turn = vehicle_in_intersection->getWillTurnRight();
        bool left_turn = vehicle_in_intersection->getWillTurnLeft();
        bool is_crossing_intersection = vehicle_in_intersection->getIsCrossingIntersection();

        // checking if vehicle is making left turn and has not started turning
        if (right_turn == false && left_turn == true && is_crossing_intersection == false) 
        {
            // checking if queue is empty
            if (!vehicle_left_queue->empty())
            {
                // checking front and back values of queue to see if vehicle is already in queue
                // queue would only hold two vehicles maximum to represent on vehicle on each road (west/east, north/south)
                if (vehicle_in_intersection != vehicle_left_queue->front() && vehicle_in_intersection != vehicle_left_queue->back())
                {
                    // add vehicle to queue
                    vehicle_left_queue->push(vehicle_in_intersection);
                }
            }
            else
            {
                // add vehicle to queue
                vehicle_left_queue->push(vehicle_in_intersection);
            }
        }
    }
}

// This function changes the has switched bounds left to false
void Road::setSwitchedBoundsLeftFalse(){
    // change value of has switched bounds left if there is a vehicle turning left
    VehicleBase* vehicle_in_intersection = road_bound[sections_before_intersection + 1];

    // checks if there is a vehicle at end of intersection
    if (vehicle_in_intersection != nullptr)
    {
        //gets details of vehicle
        bool right_turn = vehicle_in_intersection->getWillTurnRight();
        bool left_turn = vehicle_in_intersection->getWillTurnLeft();
        bool is_crossing_intersection = vehicle_in_intersection->getIsCrossingIntersection();

        // checks if vehicle is turning left and has started
        if (right_turn == false && left_turn == true && is_crossing_intersection == true) 
        {
            // changes has switched bounds left to false
            vehicle_in_intersection->setHasSwitchedBoundsLeft(false);
        }
    }
}

// Sets the propotion of vehicles that will be spawned during the simulation.
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
            }
            else
            {
                // cars < suvs < trucks
                middle_proportion = proportion_of_SUVs;
                middle_vehicle = VehicleType::suv;
                highest_vehicle = VehicleType::truck;
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
            }
            else
            {
                // suvs < cars < trucks
                middle_proportion = proportion_of_cars;
                middle_vehicle = VehicleType::car;
                highest_vehicle = VehicleType::truck;
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
        }
    }
}
    
#endif
