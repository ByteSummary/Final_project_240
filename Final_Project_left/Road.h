#ifndef __ROAD_H__
#define __ROAD_H__

#include "VehicleBase.h"
#include "TrafficLight.h"
#include <vector>
#include <string>
#include <queue>

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
        static bool left_turn_happening;
        static int left_turn_count;
    
    private:
        std::vector<VehicleBase*> road_bound;
        Direction road_direction;
        float prob_new_vehicle;
        VehicleBase* new_vehicle;
        VehicleBase* end_vehicle;
        TrafficLight& traffic_light;

        void startLeftTurn(Road& same_road_go, std::queue<VehicleBase*>* vehicle_left_queue);
        void changeRoadBoundLeft(Road& left_road_bound);

    public: 
        Road(Direction direction, float spawn_new_vehicle_rate, TrafficLight& stop_light);
        Road(const Road& other);
        Road& operator=(const Road& other);
        Road(Road&& other)noexcept;
        Road& operator=(Road&& other)noexcept;
        ~Road();

        void moveVehicles(int vehicle_pointer_counter, Road& left_road_bound, Road& same_road_go, std::queue<VehicleBase*>* vehicle_left_queue);
        void spawnNewVehicle(float rand_num_spawn, float rand_num_right_turn);
        void changeRoadBoundRight(Road& right_road_bound);
        void moveVehicleAtIntersection();
        void setSwitchedBoundsLeftFalse();
        void addToLeftQueue(std::queue<VehicleBase*>* vehicle_left_queue);

        inline std::vector<VehicleBase*>& getVehicleBaseVector() {return this->road_bound;}

        inline static void initRoadSections(int number_of_sections_before_interseciton) {sections_before_intersection = number_of_sections_before_interseciton;}
        static void settingVehicleProportions(float proportion_of_cars, float proportion_of_SUVs, float proportion_of_trucks);
        // inline static void initLeftTurnHappening() { left_turn_happening = false; }

};

#endif
