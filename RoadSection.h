#include "VehicleBase.h"

class RoadSection {

    private:
        bool sectionEmpty;
        RoadSection* next;
        RoadSection* previous;

    public:
        RoadSection* getNext();
        RoadSection* getPrevious();
        bool isEmpty();

        RoadSection();
        ~RoadSection();

        void setNext(RoadSection* section);
        void setPrevious(RoadSection* section);
        void setEmpty();
        void setUnempty();

};