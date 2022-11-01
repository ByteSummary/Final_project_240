#include <iostream> 
#include "RoadSection.h"
 
//Default Constructor
RoadSection::RoadSection() {
    sectionEmpty = true;
    setNext(nullptr);
    setPrevious(nullptr);
}
//Destructor
RoadSection::~RoadSection() {
}
//Returns a pointer to the next road section
RoadSection *RoadSection::getNext() {
    return next;
}
// Returns a pointer to the previous road section
RoadSection *RoadSection::getPrevious() {
    return previous;
}

// Returns the boolean value which is true if the section is empty; false if it is not empty
bool RoadSection::isEmpty() {
    return sectionEmpty;
}

// Set pointer to next section
void RoadSection::setNext(RoadSection *section) {
    next = section;
}

// Set pointer to previous section
void RoadSection::setPrevious(RoadSection *section) {
    previous = section;
}

// Mark the section as empty
void RoadSection::setEmpty() {
    sectionEmpty = true;
}

// Mark the section as unempty
void RoadSection::setUnempty() {
    sectionEmpty = false;
}