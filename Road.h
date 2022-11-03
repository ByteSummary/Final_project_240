#ifndef __ROAD_H__
#define __ROAD_H__

#include "VehicleBase.h"
#include <vector>

class Road {

    public:
        static int sections_before_intersection;

        static float proportion_of_cars;
        static float proportion_of_SUVs;
        static float proportion_of_trucks;

        static VehicleType lowest_vehicle;
        static float lowest_proportion;
        static VehicleType middle_vehicle;
        static float middle_proportion;
        static VehicleType highest_vehicle;
    
    private:
        std::vector<VehicleBase*> roadBound;
        Direction roadDirection;
        float prob_new_vehicle;
        VehicleBase* newVehicle;
        bool finishedNewVehicle;
        int newVehicleCount;
        VehicleBase* endVehicle;
        bool finishedEndVehicle;
        int endVehicleCount;

        static void organizingVehicleProportions();

    public: 
        // Road();
        Road(Direction direction, float spawn_new_vehicle_rate);
        // Road(const Road& other);
        // Road& Road::operator=(const Road& other);
        // Road::Road(Road&& other)noexcept;
        // Road& Road::operator=(Road&&)noexcept;
        ~Road();

        void moveVehicles(float randnum);
        void spawnNewVehicle(float randnum);

        inline std::vector<VehicleBase*> getVehicleBaseVector() {return this->roadBound;}

        inline static void initRoadSections(int number_of_sections_before_interseciton) {sections_before_intersection = number_of_sections_before_interseciton;}
        static void settingVehicleProportions(float car_prop, float suv_prop, float truck_prop);

};

#endif
