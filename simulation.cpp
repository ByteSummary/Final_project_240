#include <iostream>
#include <fstream>
#include <random> 
#include <string>
#include <iterator>
#include <stdlib.h>
#include <map>
#include <tuple>
#include "Animator.h"
#include "VehicleBase.h"
#include "TrafficLight.h"
#include "Road.h"

int main(int argc, char *argv[])
{
    std::map<std::string, float> compositionFile;
    std::map<std::string, float>::iterator itr;
    std::mt19937 rng; // construct an instance of mt19937 
    std::uniform_real_distribution<double> rand_double(0.0, 1.0); // rand_double will use rng to generate uniform(0,1) variates 
    std::string category;
    float value = 0;

    std::ifstream infile(argv[1]);

    if (!infile)
    {
        std::cerr << "Error: could not open file: " << argv[1] << std::endl;
        exit(1);
    }

    // variables from input file
    while (infile >> category >> value)
    {
        if (category == "maximum_simulated_time:")
        {
            compositionFile["maximum_simulated_time"] = value;
        }
        else if (category == "number_of_sections_before_intersection:")
        {
            compositionFile["number_of_sections_before_intersection"] = value;
        }
        else if (category == "green_north_south:")
        {
            compositionFile["green_north_south"] = value;
        }
        else if (category == "yellow_north_south:")
        {
            compositionFile["yellow_north_south"] = value;
        }
        else if (category == "green_east_west:")
        {
            compositionFile["green_east_west"] = value;
        }
        else if (category == "yellow_east_west:")
        {
            compositionFile["yellow_east_west"] = value;
        }
        else if (category == "prob_new_vehicle_northbound:")
        {
            compositionFile["prob_new_vehicle_northbound"] = value;
        }
        else if (category == "prob_new_vehicle_southbound:")
        {
            compositionFile["prob_new_vehicle_southbound:"] = value;
        }
        else if (category == "prob_new_vehicle_eastbound:")
        {
            compositionFile["prob_new_vehicle_eastbound"] = value;
        }
        else if (category == "prob_new_vehicle_westbound:")
        {
            compositionFile["prob_new_vehicle_westbound"] = value;
        }
        else if (category == "proportion_of_cars:")
        {
            compositionFile["proportion_of_cars"] = value;
        }
        else if (category == "proportion_of_SUVs:")
        {
            compositionFile["proportion_of_SUVs"] = value;
        }
        else if (category == "proportion_right_turn_cars:")
        {
            compositionFile["proportion_right_turn_cars"] = value;
        }
        else if (category == "proportion_left_turn_cars:")
        {
            compositionFile["proportion_left_turn_cars"] = value;
        }
        else if (category == "proportion_right_turn_SUVs:")
        {
            compositionFile["proportion_right_turn_SUVs"] = value;
        }
        else if (category == "proportion_left_turn_SUVs:")
        {
            compositionFile["proportion_left_turn_SUVs"] = value;
        }
        else if (category == "proportion_right_turn_trucks:")
        {
            compositionFile["proportion_right_turn_trucks"] = value;
        }
        else if (category == "proportion_left_turn_trucks:")
        {
            compositionFile["proportion_left_turn_trucks"] = value;
        }
    }
    infile.close();

    int maximum_simulated_time = (int)compositionFile.find("maximum_simulated_time")->second;
    int number_of_sections_before_intersection = (int)compositionFile.find("number_of_sections_before_intersection")->second;
    int green_north_south = (int)compositionFile.find("green_north_south")->second;
    int yellow_north_south = (int)compositionFile.find("yellow_north_south")->second;
    int green_east_west = (int)compositionFile.find("green_east_west")->second;
    int yellow_east_west = (int)compositionFile.find("yellow_east_west")->second;
    float prob_new_vehicle_northbound = compositionFile.find("prob_new_vehicle_northbound")->second;
    float prob_new_vehicle_southbound = compositionFile.find("prob_new_vehicle_southbound")->second;
    float prob_new_vehicle_eastbound = compositionFile.find("prob_new_vehicle_eastbound")->second;
    float prob_new_vehicle_westbound = compositionFile.find("prob_new_vehicle_westbound")->second;
    float proportion_of_cars = compositionFile.find("proportion_of_cars")->second;
    float proportion_of_SUVs = compositionFile.find("proportion_of_SUVs")->second;
    float proportion_right_turn_cars = compositionFile.find("proportion_right_turn_cars")->second;
    float proportion_left_turn_cars = compositionFile.find("proportion_left_turn_cars")->second;
    float proportion_right_turn_SUVs = compositionFile.find("proportion_right_turn_SUVs")->second;
    float proportion_left_turn_SUVs = compositionFile.find("proportion_left_turn_SUVs")->second;
    float proportion_right_turn_trucks = compositionFile.find("proportion_right_turn_trucks")->second;
    float proportion_left_turn_trucks = compositionFile.find("proportion_left_turn_trucks")->second;
    float proportion_of_trucks = 1 - (proportion_of_cars + proportion_of_SUVs);

    // int maximum_simulated_time = 1000;
    // int number_of_sections_before_intersection = 8;
    // int green_north_south = 12;
    // int yellow_north_south = 3;
    // int green_east_west = 10;
    // int yellow_east_west = 3;
    // float prob_new_vehicle_northbound = 0.25;
    // float prob_new_vehicle_southbound = 0.1;
    // float prob_new_vehicle_eastbound = 0.15;
    // float prob_new_vehicle_westbound = 0.15;
    // float proportion_of_cars = 0.6;
    // float proportion_of_SUVs = 0.3;
    // // float proportion_of_trucks = 1 - (proportion_of_cars + proportion_of_SUVs);
    // float proportion_of_trucks = 0.1;
    // int red_east_west = green_north_south + yellow_north_south;
    // int red_north_south = green_east_west + yellow_east_west;

    // float proportion_right_turn_cars = 0.25;
    // float proportion_right_turn_SUVs = 0.1;
    // float proportion_right_turn_trucks = 0.15;

    int initialSeed = 8675309; 
    // int initialSeed = stoi(argv[1]);
    rng.seed(initialSeed); // set the initial seed of the rng 

    float randnum = 0.5; // need to fix this

    char dummy;

    Road::initRoadSections(number_of_sections_before_intersection);
    Road::settingVehicleProportions(proportion_of_cars, proportion_of_SUVs, proportion_of_trucks);

    VehicleBase::settingRightTurnProb(proportion_right_turn_cars, proportion_right_turn_SUVs, proportion_right_turn_trucks);

    Animator anim(number_of_sections_before_intersection);

    TrafficLight eastWestLight(LightColor::green, green_east_west, yellow_east_west);
    TrafficLight northSouthLight(LightColor::red, green_north_south, yellow_north_south);
    TrafficLight* go = &eastWestLight;

    anim.setLightEastWest(eastWestLight.getLightColor());
    anim.setLightNorthSouth(northSouthLight.getLightColor());

    // int count_north_south = 0;
    // int count_east_west = 0;
    bool east_west_go = true;

    Road westbound(Direction::west, prob_new_vehicle_westbound, eastWestLight);
    Road northbound(Direction::north, prob_new_vehicle_northbound, northSouthLight);
    Road southbound(Direction::south, prob_new_vehicle_southbound, northSouthLight);
    Road eastbound(Direction::east, prob_new_vehicle_eastbound, eastWestLight);

    anim.setVehiclesNorthbound(northbound.getVehicleBaseVector());
    anim.setVehiclesWestbound(westbound.getVehicleBaseVector());
    anim.setVehiclesSouthbound(southbound.getVehicleBaseVector());
    anim.setVehiclesEastbound(eastbound.getVehicleBaseVector());
    anim.draw(0);
    std::cin.get(dummy);

    for (int time = 1; time <= maximum_simulated_time; time++)
    {
        // for trafficLight go, check count then change color or decrement count
        go->timeLightChange();

        if (east_west_go) 
        {
            anim.setLightEastWest(go->getLightColor());
        }
        else 
        {
            anim.setLightNorthSouth(go->getLightColor());
        }

        if (go->getLightColor() == LightColor::red)
        {
            if (east_west_go) 
            {
                go = &northSouthLight;
                go->setGreen();
                anim.setLightNorthSouth(go->getLightColor());
                east_west_go = false;
            }
            else 
            {
                go = &eastWestLight;
                go->setGreen();
                anim.setLightEastWest(go->getLightColor());
                east_west_go = true;
            }
        }
        
        westbound.moveVehicles();
        northbound.moveVehicles();
        eastbound.moveVehicles();
        southbound.moveVehicles();
        westbound.spawnNewVehicle(rand_double(rng), rand_double(rng));
        northbound.spawnNewVehicle(rand_double(rng), rand_double(rng));
        eastbound.spawnNewVehicle(rand_double(rng), rand_double(rng));
        southbound.spawnNewVehicle(rand_double(rng), rand_double(rng));
        westbound.changeRoadBound(northbound);
        northbound.changeRoadBound(eastbound);
        eastbound.changeRoadBound(southbound);
        southbound.changeRoadBound(westbound);

        anim.setVehiclesNorthbound(northbound.getVehicleBaseVector());
        anim.setVehiclesWestbound(westbound.getVehicleBaseVector());
        anim.setVehiclesSouthbound(southbound.getVehicleBaseVector());
        anim.setVehiclesEastbound(eastbound.getVehicleBaseVector());
        anim.draw(time);
        std::cin.get(dummy);

        // if (time % 2 == 0 || time % 3 == 0) 
        // {
        //     randnum = 1;
        // }
        // else
        // {
        //     randnum = 0.1;
        // }
    }
}