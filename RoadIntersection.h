#include "RoadSection.h"

class RoadIntersection: public RoadSection {

    private:
        RoadIntersection* north;
        RoadIntersection* east;
        RoadIntersection* south;
        RoadIntersection* west;

    public:
        //set virtual ???
        RoadSection* getNext();
        RoadSection* getPrevious();
        //set virtual ???
    
        RoadIntersection* getRightTurn();
        RoadIntersection* getNorth();
        RoadIntersection* getEast();
        RoadIntersection* getSouth();
        RoadIntersection* getWest();

        void setNorth(RoadIntersection* section);
        void setEast(RoadIntersection* section);
        void setSouth(RoadIntersection* section);
        void setWest(RoadIntersection* section);
};