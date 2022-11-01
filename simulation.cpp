#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <tuple> 
#include "Animator.h"
#include "VehicleBase.h"

void simulation() { //std::string fileName
    // variables from input file
    int maximum_simulated_time = 1000;
    int number_of_sections_before_intersection = 10;
    int green_north_south = 12;
    int yellow_north_south = 3;
    int green_east_west = 10;
    int yellow_east_west = 3;
    float prob_new_vehicle_northbound = 0.25;
    float prob_new_vehicle_southbound = 0.1;
    float prob_new_vehicle_eastbound = 0.15;
    float prob_new_vehicle_westbound = 0.5;
    float proportion_of_cars = 0.6;
    float proportion_of_SUVs = 0.3;
    float proportion_right_turn_cars = 0.4;
    float proportion_left_turn_cars = 0.1;
    float proportion_right_turn_SUVs = 0.3;
    float proportion_left_turn_SUVs = 0.05;
    float proportion_right_turn_trucks = 0.2;
    float proportion_left_turn_trucks = 0.02;
    char dummy;

    float randnum = 0.1; // need to fix this

    // std::ifstream infile(fileName);

    // if(!infile) {
    //     std::cerr << "Error: could not open file: " << fileName << std::endl;
    //     exit(1);
    // }

    number_of_sections_before_intersection = 8;  // number of sections before intersection

    Animator anim(number_of_sections_before_intersection);

    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);

    int count_north_south = 0;
    int count_east_west = 0;
    bool east_west_go = true;

    // construct vectors of VehicleBase* of appropriate size, init to nullptr
    std::vector<VehicleBase*> westbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase*> eastbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase*> southbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase*> northbound(number_of_sections_before_intersection * 2 + 2, nullptr);

    // std::map<std::string, int> compositionFile;
    // std::string category;
    // int value = 0;

    // while (infile.good()) {
    //     infile >> category >> value;
    //     if (category == "maximum_simulated_time") {
    //         compositionFile.insert(pair<std::string, int>("maximum_simulated_time", value));
    //     }
    //     else if (category == "number_of_sections_before_intersection") {
    //         compositionFile.insert(pair<std::string, int>("number_of_sections_before_intersection", value));
    //     }
    //     else if (category == "green_north_south") {
    //         compositionFile.insert(pair<std::string, int>("green_north_south", value));
    //     }
    //     else if (category == "yellow_north_south") {
    //         compositionFile.insert(pair<std::string, int>("yellow_north_south", value));
    //     }
    //     else if (category == "yellow_east_west") {
    //         compositionFile.insert(pair<std::string, int>("yellow_east_west", value));
    //     }
    //     else if (category == "prob_new_vehicle_northbound") {
    //         compositionFile.insert(pair<std::string, int>("prob_new_vehicle_northbound", value));
    //     }
    //     else if (category == "prob_new_vehicle_southbound") {
    //         compositionFile.insert(pair<std::string, int>("prob_new_vehicle_southbound", value));
    //     }
    //     else if (category == "prob_new_vehicle_eastbound") {
            
    //     }
    //     else if (category == "prob_new_vehicle_westbound") {
            
    //     }
    //     else if (category == "proportion_of_cars") {
            
    //     }
    //     else if (category == "proportion_of_SUVs") {

    //     }
    //     else if (category == "proportion_right_turn_cars") {
            
    //     }
    //     else if (category == "proportion_left_turn_cars") {
            
    //     }
    //     else if (category == "proportion_right_turn_SUVs") {
            
    //     }
    //     else if (category == "proportion_left_turn_SUVs") {
            
    //     }
    //     else if (category == "proportion_right_turn_trucks") {
            
    //     }
    //     else if (category == "proportion_left_turn_trucks") {

    //     }
    // }

    float proportion_of_trucks = 1 - (proportion_of_cars + proportion_of_SUVs);

    // organizing proportions
    VehicleType lowest_vehicle;
    float lowest_proportion = 0;
    VehicleType middle_vehicle;
    float middle_proportion = 0;
    VehicleType highest_vehicle;

    if (proportion_of_cars < proportion_of_SUVs) {
        // cars < suvs
        if (proportion_of_cars < proportion_of_trucks) {
            // cars < trucks and suvs
            lowest_proportion = proportion_of_cars;
            lowest_vehicle = VehicleType::car;
            if (proportion_of_trucks < proportion_of_SUVs) {
                // cars < trucks < suvs
                middle_proportion = proportion_of_trucks;
                middle_vehicle = VehicleType::truck;
                highest_vehicle = VehicleType::suv;
            } else {
                // cars < suvs < trucks
                middle_proportion = proportion_of_SUVs;
                middle_vehicle = VehicleType::suv;
                highest_vehicle = VehicleType::truck;
            }
        } else {
            // trucks < car < suvs
            lowest_proportion = proportion_of_trucks;
            lowest_vehicle = VehicleType::truck;
            middle_proportion = proportion_of_cars;
            middle_vehicle = VehicleType::car;
            highest_vehicle = VehicleType::suv;
        }
    } else {
        // suvs < cars
        if (proportion_of_SUVs < proportion_of_trucks) {
            // suvs < trucks and cars
            lowest_proportion = proportion_of_SUVs;
            lowest_vehicle = VehicleType::suv;
            if (proportion_of_trucks < proportion_of_cars) {
                // suvs < trucks < cars
                middle_proportion = proportion_of_trucks;
                middle_vehicle = VehicleType::truck;
                highest_vehicle = VehicleType::car;
            } else {
                // suvs < cars < trucks
                middle_proportion = proportion_of_cars;
                middle_vehicle = VehicleType::car;
                highest_vehicle = VehicleType::truck;
            }
        } else {
            // trucks < suvs < cars
            lowest_proportion = proportion_of_trucks;
            lowest_vehicle = VehicleType::truck;
            middle_proportion = proportion_of_SUVs;
            middle_vehicle = VehicleType::suv;
            highest_vehicle = VehicleType::car;
        }
    }

    for (int time = 0; time < maximum_simulated_time; time++){

        // change stop/go lights
        if (east_west_go) {
            // east west light is green/yellow
            if (count_east_west == green_east_west){
                anim.setLightEastWest(LightColor::yellow);
            } else if (count_east_west == green_east_west + yellow_east_west) {
                anim.setLightEastWest(LightColor::red);
                anim.setLightNorthSouth(LightColor::green);
                count_east_west = 0;
                east_west_go = false;
            }
            count_east_west++;
        } else {
            // north south light is green/yellow
            if (count_east_west == green_north_south){
                anim.setLightNorthSouth(LightColor::yellow);
            } else if (count_east_west == green_north_south + yellow_north_south) {
                anim.setLightEastWest(LightColor::green);
                anim.setLightNorthSouth(LightColor::red);
                count_north_south = 0;
                east_west_go = true;
            }
            count_north_south++;
        }

        // move vehicles forward
        for (int vehicle_pointer_counter = (number_of_sections_before_intersection * 2 + 2) - 1; vehicle_pointer_counter >= 0; vehicle_pointer_counter--){
            // checking if pointing to nullptr
            if (westbound[vehicle_pointer_counter] != nullptr) {

                // at intersection
                if (vehicle_pointer_counter + 1 == number_of_sections_before_intersection - 1){
                    //move forward at intersection or turn right

                }
                // not at end of road
                if (vehicle_pointer_counter + 1 < number_of_sections_before_intersection * 2 + 2){
                    VehicleBase* currentVehicleWest = westbound[vehicle_pointer_counter];
                    westbound[vehicle_pointer_counter + 1] = currentVehicleWest;
                }
                
                westbound[vehicle_pointer_counter] = nullptr;
            }
        }

        // if first section of road is open and randnum is inside probability
        // needs to complete vehicle during creation
        if (westbound[0] == nullptr && randnum <= prob_new_vehicle_westbound){
            VehicleType new_vehicle_type;
            if (randnum <= lowest_proportion) {
                new_vehicle_type = lowest_vehicle;
            } else if (randnum <= lowest_proportion + middle_proportion) {
                new_vehicle_type = middle_vehicle;
            } else {
                new_vehicle_type = highest_vehicle;
            }
            VehicleBase newVehicleWest(new_vehicle_type, Direction::west);

            westbound[0] = &newVehicleWest;
        }

        anim.setVehiclesNorthbound(northbound);
        anim.setVehiclesWestbound(westbound);
        anim.setVehiclesSouthbound(southbound);
        anim.setVehiclesEastbound(eastbound);
        anim.draw(time);
        std::cin.get(dummy);

    }
    
}
 

int main()
{
    simulation();
    return 0;
}