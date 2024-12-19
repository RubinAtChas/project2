#ifndef PEDESTRIAN_AND_TRAFFIC_H
#define PEDESTRIAN_AND_TRAFFIC_H

// Class for Pedestrian
class Pedestrian {
public:
    bool isWaiting;

    Pedestrian(); // Constructor
    bool randomSpawn(bool status); // Function to simulate random spawn
    void reset();
};

// Class for Traffic
class Traffic {
public:
    Traffic(); // Constructor
    bool randomSpawn(bool status); // Function to simulate random spawn
};

#endif // PEDESTRIAN_AND_TRAFFIC_H
