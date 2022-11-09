#ifndef __ROAD_H__
#define __ROAD_H__

#include "VehicleBase.h"
#include "TrafficLight.h"
#include <vector>
#include <map>
#include <string>

/*
This class defines behavior that will occur on the pathway of the vehicles. From moving the vehicles to making the car turn right, the road class
implements all of these functionalities. 
*/

class Road {

    public:
        static int sections_before_intersection;

        static VehicleType lowest_vehicle;
        static float lowest_proportion;
        static VehicleType middle_vehicle;
        static float middle_proportion;
        static VehicleType highest_vehicle;
    
    private:
        std::vector<VehicleBase*> road_bound;
        Direction road_direction;
        float prob_new_vehicle;
        VehicleBase* new_vehicle;
        VehicleBase* end_vehicle;
        TrafficLight& traffic_light;

    public: 
        Road(Direction direction, float spawn_new_vehicle_rate, TrafficLight& stop_light);
        Road(const Road& other);
        Road& operator=(const Road& other);
        Road(Road&& other)noexcept;
        Road& operator=(Road&& other)noexcept;
        ~Road();

        void moveVehicles();
        void spawnNewVehicle(float rand_num_spawn, float rand_num_right_turn);
        void changeRoadBound(Road& right_road_bound);

        inline std::vector<VehicleBase*>& getVehicleBaseVector() {return this->road_bound;}

        inline static void initRoadSections(int number_of_sections_before_interseciton) {sections_before_intersection = number_of_sections_before_interseciton;}
        static void settingVehicleProportions(float proportion_of_cars, float proportion_of_SUVs, float proportion_of_trucks);

};

#endif
