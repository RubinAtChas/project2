#include <iostream>
#include "pedestrians_and_traffic.h"

// Constructor for pedestrians - Seeds random number generator
Pedestrian::Pedestrian() {
    srand(static_cast<unsigned int>(time(0)));
};

// Function for random pedestrian spawn (50% chance)
bool Pedestrian::randomSpawn(bool status){
    if (!status) return false; //If disabledm no pedestrians spawn
    std::cout << "1 Pedestrian incoming..." << std::endl;
    return rand() % 2 == 1; // 50% chance of spawning
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait for 1 second
    std::cout << "Button pressed..." << std::endl;
};

// Constructor for Traffic - Seeds random number generator
Traffic::Traffic() {
    srand(static_cast<unsigned int>(time(0)));
};


// Function for random traffic spawn (50% chance)
bool Traffic::randomSpawn(bool status) {
    if (!status) return false; 
    return rand() % 2 == 1; // Returns true if random value is 1
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait for 1 second   
    std::cout << "1 Veichle incoming..." << std::endl;
};
