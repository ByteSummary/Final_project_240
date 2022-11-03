#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <map>
#include <tuple>
#include "Animator.h"
#include "VehicleBase.h"
#include "Road.h"

int main(int argc, char *argv[])
{
    std::map<std::string, float> compositionFile;
    std::map<std::string, float>::iterator itr;
    std::string category;
    float value = 0;

    // std::ifstream infile(argv[1]);

    // if (!infile)
    // {
    //     std::cerr << "Error: could not open file: " << argv[1] << std::endl;
    //     exit(1);
    // }

    // // variables from input file
    // while (infile >> category >> value)
    // {
    //     if (category == "maximum_simulated_time:")
    //     {
    //         compositionFile["maximum_simulated_time"] = value;
    //     }
    //     else if (category == "number_of_sections_before_intersection:")
    //     {
    //         compositionFile["number_of_sections_before_intersection"] = value;
    //     }
    //     else if (category == "green_north_south:")
    //     {
    //         compositionFile["green_north_south"] = value;
    //     }
    //     else if (category == "yellow_north_south:")
    //     {
    //         compositionFile["yellow_north_south"] = value;
    //     }
    //     else if (category == "green_east_west:")
    //     {
    //         compositionFile["green_east_west"] = value;
    //     }
    //     else if (category == "yellow_east_west:")
    //     {
    //         compositionFile["yellow_east_west"] = value;
    //     }
    //     else if (category == "prob_new_vehicle_northbound:")
    //     {
    //         compositionFile["prob_new_vehicle_northbound"] = value;
    //     }
    //     else if (category == "prob_new_vehicle_southbound:")
    //     {
    //         compositionFile["prob_new_vehicle_southbound:"] = value;
    //     }
    //     else if (category == "prob_new_vehicle_eastbound:")
    //     {
    //         compositionFile["prob_new_vehicle_eastbound"] = value;
    //     }
    //     else if (category == "prob_new_vehicle_westbound:")
    //     {
    //         compositionFile["prob_new_vehicle_westbound"] = value;
    //     }
    //     else if (category == "proportion_of_cars:")
    //     {
    //         compositionFile["proportion_of_cars"] = value;
    //     }
    //     else if (category == "proportion_of_SUVs:")
    //     {
    //         compositionFile["proportion_of_SUVs"] = value;
    //     }
    //     else if (category == "proportion_right_turn_cars:")
    //     {
    //         compositionFile["proportion_right_turn_cars"] = value;
    //     }
    //     else if (category == "proportion_left_turn_cars:")
    //     {
    //         compositionFile["proportion_left_turn_cars"] = value;
    //     }
    //     else if (category == "proportion_right_turn_SUVs:")
    //     {
    //         compositionFile["proportion_right_turn_SUVs"] = value;
    //     }
    //     else if (category == "proportion_left_turn_SUVs:")
    //     {
    //         compositionFile["proportion_left_turn_SUVs"] = value;
    //     }
    //     else if (category == "proportion_right_turn_trucks:")
    //     {
    //         compositionFile["proportion_right_turn_trucks"] = value;
    //     }
    //     else if (category == "proportion_left_turn_trucks:")
    //     {
    //         compositionFile["proportion_left_turn_trucks"] = value;
    //     }
    // }
    // infile.close();

    // int maximum_simulated_time = (int)compositionFile.find("maximum_simulated_time")->second;
    // int number_of_sections_before_intersection = (int)compositionFile.find("number_of_sections_before_intersection")->second;
    // int green_north_south = (int)compositionFile.find("green_north_south")->second;
    // int yellow_north_south = (int)compositionFile.find("yellow_north_south")->second;
    // int green_east_west = (int)compositionFile.find("green_east_west")->second;
    // int yellow_east_west = (int)compositionFile.find("yellow_east_west")->second;
    // float prob_new_vehicle_northbound = compositionFile.find("prob_new_vehicle_northbound")->second;
    // float prob_new_vehicle_southbound = compositionFile.find("prob_new_vehicle_southbound")->second;
    // float prob_new_vehicle_eastbound = compositionFile.find("prob_new_vehicle_eastbound")->second;
    // float prob_new_vehicle_westbound = compositionFile.find("prob_new_vehicle_westbound")->second;
    // float proportion_of_cars = compositionFile.find("proportion_of_cars")->second;
    // float proportion_of_SUVs = compositionFile.find("proportion_of_SUVs")->second;
    // float proportion_right_turn_cars = compositionFile.find("proportion_right_turn_cars")->second;
    // float proportion_left_turn_cars = compositionFile.find("proportion_left_turn_cars")->second;
    // float proportion_right_turn_SUVs = compositionFile.find("proportion_right_turn_SUVs")->second;
    // float proportion_left_turn_SUVs = compositionFile.find("proportion_left_turn_SUVs")->second;
    // float proportion_right_turn_trucks = compositionFile.find("proportion_right_turn_trucks")->second;
    // float proportion_left_turn_trucks = compositionFile.find("proportion_left_turn_trucks")->second;

    int maximum_simulated_time = 1000;
    int number_of_sections_before_intersection = 8;
    int green_north_south = 12;
    int yellow_north_south = 3;
    int green_east_west = 10;
    int yellow_east_west = 3;
    float prob_new_vehicle_northbound = 0.25;
    float prob_new_vehicle_southbound = 0.1;
    float prob_new_vehicle_eastbound = 0.15;
    float prob_new_vehicle_westbound = 0.15;
    float proportion_of_cars = 0.3;
    float proportion_of_SUVs = 0.8;
    // float proportion_of_trucks = 1 - (proportion_of_cars + proportion_of_SUVs);
    float proportion_of_trucks = 1.1;

    float randnum = 0.1; // need to fix this

    char dummy;

    Road::initRoadSections(number_of_sections_before_intersection);
    Road::settingVehicleProportions(proportion_of_cars, proportion_of_SUVs, proportion_of_trucks);

    Animator anim(number_of_sections_before_intersection);

    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);

    int count_north_south = 0;
    int count_east_west = 0;
    bool east_west_go = true;

    Road westbound(Direction::west, prob_new_vehicle_westbound);
    Road northbound(Direction::north, prob_new_vehicle_westbound);
    Road southbound(Direction::south, prob_new_vehicle_westbound);
    Road eastbound(Direction::east, prob_new_vehicle_westbound);

    anim.setVehiclesNorthbound(northbound.getVehicleBaseVector());
    anim.setVehiclesWestbound(westbound.getVehicleBaseVector());
    anim.setVehiclesSouthbound(southbound.getVehicleBaseVector());
    anim.setVehiclesEastbound(eastbound.getVehicleBaseVector());
    anim.draw(0);
    std::cin.get(dummy);

    for (int time = 1; time <= maximum_simulated_time; time++)
    {

        // change stop/go lights
        if (east_west_go)
        {
            // east west light is green/yellow
            if (count_east_west == green_east_west)
            {
                anim.setLightEastWest(LightColor::yellow);
                count_east_west++;
            }
            else if (count_east_west == green_east_west + yellow_east_west)
            {
                anim.setLightEastWest(LightColor::red);
                anim.setLightNorthSouth(LightColor::green);
                count_east_west = 0;
                east_west_go = false;
            }
            else
            {
                count_east_west++;
            }
        }
        else
        {
            // north south light is green/yellow
            if (count_north_south == green_north_south)
            {
                anim.setLightNorthSouth(LightColor::yellow);
                count_north_south++;
            }
            else if (count_north_south == green_north_south + yellow_north_south)
            {
                anim.setLightEastWest(LightColor::green);
                anim.setLightNorthSouth(LightColor::red);
                count_north_south = 0;
                east_west_go = true;
            }
            else
            {
                count_north_south++;
            }
        }

        westbound.moveVehicles(randnum);
        westbound.spawnNewVehicle(randnum);

        anim.setVehiclesNorthbound(northbound.getVehicleBaseVector());
        anim.setVehiclesWestbound(westbound.getVehicleBaseVector());
        anim.setVehiclesSouthbound(southbound.getVehicleBaseVector());
        anim.setVehiclesEastbound(eastbound.getVehicleBaseVector());
        anim.draw(time);
        std::cin.get(dummy);

        if (time % 2 == 0 || time % 3 == 0) 
        {
            randnum = 1;
        }
        else
        {
            randnum = 0.1;
        }
    }
}