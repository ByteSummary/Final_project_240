#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <map>
#include <tuple>
#include "Animator.h"
#include "VehicleBase.h"



int main(int argc, char *argv[])
{
    std::map<std::string, float> compositionFile;
    std::map<std::string, float>::iterator itr;
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

    float maximum_simulated_time = compositionFile.find("maximum_simulated_time")->second;
    float number_of_sections_before_intersection = compositionFile.find("number_of_sections_before_intersection")->second;
    float green_north_south = compositionFile.find("green_north_south")->second;
    float yellow_north_south = compositionFile.find("yellow_north_south")->second;
    float green_east_west = compositionFile.find("green_east_west")->second;
    float yellow_east_west = compositionFile.find("yellow_east_west")->second;
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

    VehicleType addNewVehicleType(std::vector<VehicleBase *> roadBound, float prob_new_vehicle);
    void fixVehicleProprotions();
    int getVehicleLength(VehicleBase vehicle);


    float proportion_of_trucks = 1 - (proportion_of_cars + proportion_of_SUVs);

    float randnum = 0.1; // need to fix this

    // organizing proportions
    VehicleType lowest_vehicle;
    float lowest_proportion = 0;
    VehicleType middle_vehicle;
    float middle_proportion = 0;
    VehicleType highest_vehicle;
    // VehicleBase newWestVehicle;
    int newVehicleWestCount = 0;
    int newVehicleWestLength;
    char dummy;

    number_of_sections_before_intersection = 8; // number of sections before intersection

    Animator anim(number_of_sections_before_intersection);

    anim.setLightNorthSouth(LightColor::red);
    anim.setLightEastWest(LightColor::green);

    int count_north_south = 0;
    int count_east_west = 0;
    bool east_west_go = true;

    //construct vectors of VehicleBase* of appropriate size, init to nullptr
    std::vector<VehicleBase *> westbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase *> eastbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase *> southbound(number_of_sections_before_intersection * 2 + 2, nullptr);
    std::vector<VehicleBase *> northbound(number_of_sections_before_intersection * 2 + 2, nullptr);

    bool finished_created_vehicle_west = true;

    

        fixVehicleProportions();

        for (int time = 0; time < maximum_simulated_time; time++)
        {

            // change stop/go lights
            if (east_west_go)
            {
                // east west light is green/yellow
                if (count_east_west == green_east_west)
                {
                    anim.setLightEastWest(LightColor::yellow);
                }
                else if (count_east_west == green_east_west + yellow_east_west)
                {
                    anim.setLightEastWest(LightColor::red);
                    anim.setLightNorthSouth(LightColor::green);
                    count_east_west = 0;
                    east_west_go = false;
                }
                count_east_west++;
            }
            else
            {
                // north south light is green/yellow
                if (count_east_west == green_north_south)
                {
                    anim.setLightNorthSouth(LightColor::yellow);
                }
                else if (count_east_west == green_north_south + yellow_north_south)
                {
                    anim.setLightEastWest(LightColor::green);
                    anim.setLightNorthSouth(LightColor::red);
                    count_north_south = 0;
                    east_west_go = true;
                }
                count_north_south++;
            }

            // move vehicles forward
            for (int vehicle_pointer_counter = (number_of_sections_before_intersection * 2 + 2) - 1; vehicle_pointer_counter >= 0; vehicle_pointer_counter--)
            {
                // checking if pointing to nullptr
                if (westbound[vehicle_pointer_counter] != nullptr)
                {

                    // at intersection
                    if (vehicle_pointer_counter + 1 == number_of_sections_before_intersection - 1)
                    {
                        // move forward at intersection or turn right
                    }
                    // not at end of road
                    if (vehicle_pointer_counter + 1 < number_of_sections_before_intersection * 2 + 2)
                    {
                        VehicleBase *currentVehicleWest = westbound[vehicle_pointer_counter];
                        westbound[vehicle_pointer_counter + 1] = currentVehicleWest;
                    }

                    westbound[vehicle_pointer_counter] = nullptr;
                }
            }

            // call function to add vehicles in each road
            if (finished_created_vehicle_west)
            {
                VehicleType newWestVehicleType = addNewVehicle(westbound, prob_new_vehicle_westbound);
                newWestVehicle = (newWestVehicleType, Direction::west); // need copy or move assginment
                westbound[0] = &newWestVehicle;
                // if (newWestVehicle != nullptr) {
                //     finished_created_vehicle_west = false;
                //     newVehicleWestLength = getVehicleLength(newWestVehicle);
                // }
            }
            else
            {
                if (newVehicleWestCount == newVehicleWestLength)
                {
                    finished_created_vehicle_west = true;
                    newVehicleWestCount = 0;
                }
                else
                {
                    westbound[0] = &newWestVehicle;
                    newVehicleWestCount++;
                }
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

    VehicleType addNewVehicleType(std::vector<VehicleBase *> roadBound, float prob_new_vehicle)
    {
        // if first section of road is open and randnum is inside probability
        // needs to complete vehicle during creation
        if (roadBound[0] == nullptr && randnum <= prob_new_vehicle)
        {
            VehicleType new_vehicle_type;
            if (randnum <= lowest_proportion)
            {
                new_vehicle_type = lowest_vehicle;
            }
            else if (randnum <= lowest_proportion + middle_proportion)
            {
                new_vehicle_type = middle_vehicle;
            }
            else
            {
                new_vehicle_type = highest_vehicle;
            }
            return newVehicleType;
        }
        else
        {
            return;
        }
    }

    int getVehicleLength(VehicleBase *vehicle)
    {
        if (*vehicle.getVehicleType() == VehicleType::car)
        {
            return 2;
        }
        else if (*vehicle.getVehicleType() == VehicleType::suv)
        {
            return 3;
        }
        else
        {
            return 4;
        }
    }

    void fixVehicleProportions()
    {
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