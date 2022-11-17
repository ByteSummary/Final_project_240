#include <iostream>
#include <fstream>
#include <random> 
#include <string>
#include <iterator>
#include <stdlib.h>
#include <map>
#include <queue>
#include "Animator.h"
#include "VehicleBase.h"
#include "TrafficLight.h"
#include "Road.h"
#include "Random.h"

int main(int argc, char *argv[])
{
    std::map<std::string, float> compositionFile;
    std::map<std::string, float>::iterator itr;
    std::string category;
    float value = 0;

    if (argc == 3) {

        // gets input file from command line arguments
        std::ifstream infile(argv[1]);

        // checks if file can be opened
        if (!infile)
        {
            std::cerr << "Error: could not open file: " << argv[1] << std::endl;
            exit(1);
        }


        // getting variables from input file and placing it in map
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

        // Allows for variables to be used without having to find value in map
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

        // produces random number generator from seed provided by the user
        int initial_seed = atoi(argv[2]);
        Random random_number_generator = Random(initial_seed);

        // character used to tell when to increment time
        char dummy;

        //define the number of road sections
        Road::initRoadSections(number_of_sections_before_intersection);

        //Set proportion of vehicles that can exist
        Road::settingVehicleProportions(proportion_of_cars, proportion_of_SUVs, proportion_of_trucks);

        //Set proportion of vehicles of specific class that are allowed to turn right
        VehicleBase::settingRightTurnProb(proportion_right_turn_cars, proportion_right_turn_SUVs, proportion_right_turn_trucks);

        //Set proportion of vehicles of specific class that are allowed to turn left
        VehicleBase::settingLeftTurnProb(proportion_left_turn_cars, proportion_left_turn_SUVs, proportion_left_turn_trucks);

        //Set animator to include the number of sections before the intersection
        Animator anim(number_of_sections_before_intersection);

        //Set traffic light colors
        TrafficLight east_West_Light(LightColor::green, green_east_west, yellow_east_west);
        TrafficLight north_South_Light(LightColor::red, green_north_south, yellow_north_south);
        TrafficLight* go = &east_West_Light;

        //Use color of each traffic light for the animator
        anim.setLightEastWest(east_West_Light.getLightColor());
        anim.setLightNorthSouth(north_South_Light.getLightColor());

        // start off with east/west traffic light on go
        bool east_west_go = true;

        //construct roads from Road class
        Road westbound(Direction::west, prob_new_vehicle_westbound, east_West_Light);
        Road northbound(Direction::north, prob_new_vehicle_northbound, north_South_Light);
        Road southbound(Direction::south, prob_new_vehicle_southbound, north_South_Light);
        Road eastbound(Direction::east, prob_new_vehicle_eastbound, east_West_Light);

        // queues for east/west and north/south roads for vehicles turning left
        std::queue<VehicleBase*> west_east_queue;
        std::queue<VehicleBase*> north_south_queue;

        // Animate vehicles in each direction
        anim.setVehiclesNorthbound(northbound.getVehicleBaseVector());
        anim.setVehiclesWestbound(westbound.getVehicleBaseVector());
        anim.setVehiclesSouthbound(southbound.getVehicleBaseVector());
        anim.setVehiclesEastbound(eastbound.getVehicleBaseVector());
        anim.draw(0);
        std::cin.get(dummy);

        /*
        This for loop is the basis for the program, each cycle is paused and waits for a use input to continue. with each cycle, the vehicles
        increment forward by 1 cycle. Vehicles are both spawned and move at the start of each cycle and their behavior is determined by the probability
        that they turn right as 
        */
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

            // changes lights that are on go/green if time is up
            if (go->getLightColor() == LightColor::red)
            {
                if (east_west_go) 
                {
                    go = &north_South_Light;
                    go->setGreen();
                    anim.setLightNorthSouth(go->getLightColor());
                    east_west_go = false;
                }
                else 
                {
                    go = &east_West_Light;
                    go->setGreen();
                    anim.setLightEastWest(go->getLightColor());
                    east_west_go = true;
                }
            }
            
            // Moves the vehicles on each of the roads forward by 1
            // Loops through each section of road from end to 0
            for (int vehicle_pointer_counter = (number_of_sections_before_intersection * 2 + 2) - 1; vehicle_pointer_counter >= 0; vehicle_pointer_counter--)
            {
                westbound.moveVehicles(vehicle_pointer_counter, southbound, eastbound, &west_east_queue);
                northbound.moveVehicles(vehicle_pointer_counter, westbound, southbound, &north_south_queue);
                eastbound.moveVehicles(vehicle_pointer_counter, northbound, westbound, &west_east_queue);
                southbound.moveVehicles(vehicle_pointer_counter, eastbound, northbound, &north_south_queue);
            }

            // Spawns the vehicles on each of the roads and uses the random generator to set probabilities to a pseudo-random number
            westbound.spawnNewVehicle((float)random_number_generator.getRandomDouble(),(float)random_number_generator.getRandomDouble());
            northbound.spawnNewVehicle((float)random_number_generator.getRandomDouble(), (float)random_number_generator.getRandomDouble());
            eastbound.spawnNewVehicle((float)random_number_generator.getRandomDouble(), (float)random_number_generator.getRandomDouble());
            southbound.spawnNewVehicle((float)random_number_generator.getRandomDouble(), (float)random_number_generator.getRandomDouble());

            //Will change the road of the vehicle if turning right
            westbound.changeRoadBoundRight(northbound);
            northbound.changeRoadBoundRight(eastbound);
            eastbound.changeRoadBoundRight(southbound);
            southbound.changeRoadBoundRight(westbound);

            // Changes values of has switched bounds left to false if there is a vehicle making a left turn
            // and if part of it is at the end of the intersection
            westbound.setSwitchedBoundsLeftFalse();
            northbound.setSwitchedBoundsLeftFalse();
            eastbound.setSwitchedBoundsLeftFalse();
            southbound.setSwitchedBoundsLeftFalse();

            // Adds vehicles to queue if turning left
            westbound.addToLeftQueue(&west_east_queue);
            northbound.addToLeftQueue(&north_south_queue);
            eastbound.addToLeftQueue(&west_east_queue);
            southbound.addToLeftQueue(&north_south_queue);

            // Sets vehicles for the animator
            anim.setVehiclesNorthbound(northbound.getVehicleBaseVector());
            anim.setVehiclesWestbound(westbound.getVehicleBaseVector());
            anim.setVehiclesSouthbound(southbound.getVehicleBaseVector());
            anim.setVehiclesEastbound(eastbound.getVehicleBaseVector());
            anim.draw(time);
            std::cin.get(dummy);
        }
    }
    else {
        std::cerr << "Usage:[./simulation][input file][random seed]" << std::endl;
    }
}