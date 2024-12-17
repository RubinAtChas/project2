#ifndef TRAFFICLIGHTMANAGER_H
#define TRAFFICLIGHTMANAGER_H

#include "TrafficLight.h"
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>

// TrafficLightManager handles the logic for controlling multiple traffic lights in a synchronized manner.
// It ensures that only one traffic light is green at a time, and transitions through the lights based on their timings.
class TrafficLightManager
{
private:
    std::vector<TrafficLight> trafficLights; // Stores all traffic lights managed by this class.
    std::mutex mtx;  // The mutex thingy (I think) stops other threads from messing around with stuff at the same time.
    std::condition_variable cv; // The conditions that stear the mutex and updates the other threads of how to behave.
    int currentGreenLightIndex; // Lets threads sleep until notified, ensuring synchronization between threads.
public:
    TrafficLightManager(): currentGreenLightIndex(0) {}

    void graphicsDisplay();
    void addTrafficLight(TrafficLight light);
    void run();
};

#endif