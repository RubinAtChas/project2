#ifndef PEDESTRIAN_AND_TRAFFIC_H
#define PEDESTRIAN_AND_TRAFFIC_H

#include <iostream>  // For printing
#include <cstdlib>   // For rand()
#include <ctime>     // For seeding RNG
#include <thread>    // For delay
#include  <chrono>    

// Class for Pedestrian
class Pedestrian {
public:
    Pedestrian(); // Constructor
    static bool randomSpawn(bool status); // Function to simulate random spawn
};

// Class for Traffic
class Traffic {
public:
    Traffic(); // Constructor
    static bool randomSpawn(bool status); // Function to simulate random spawn
};

#endif // PEDESTRIAN_AND_TRAFFIC_H
