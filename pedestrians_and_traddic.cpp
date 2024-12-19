#include <iostream>
#include <iostream>  // For printing
#include <cstdlib>   // For rand()
#include <ctime>     // For seeding RNG
#include <thread>    // For delay
#include  <chrono>    
#include "pedestrians_and_traffic.h"


// Constructor for pedestrians - Seeds random number generator
Pedestrian::Pedestrian() {
    srand(static_cast<unsigned int>(time(0)));
    isWaiting = false;
}

// The function exists to create a Person with 50% chance
bool Pedestrian::randomSpawn(bool status){
    if (status == false) return false; //If disabledm no pedestrians spawn
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait for 1 second
    std::cout << "1 Pedestrian incoming..." << std::endl;
    isWaiting = rand() % 2 == 1;
    return isWaiting; // 50% chance of spawning
}

void Pedestrian::reset()
{
    isWaiting = false;
}

// Constructor for Traffic - Seeds random number generator
Traffic::Traffic() {
    srand(static_cast<unsigned int>(time(0)));
}


// The function exists to create a car with 50% chance
bool Traffic::randomSpawn(bool status) {
    if (status == false) return false; 
    std::this_thread::sleep_for(std::chrono::seconds(1)); //Wait for 1 second   
    std::cout << "1 Veichle incoming..." << std::endl;
    return rand() % 2 == 1; // Returns true if random value is 1
}
