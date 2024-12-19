#include "TrafficLight.h"
#include "pedestrians_and_traffic.h"
#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <memory>

void *operator new(size_t size)
{
    std::cout << "allocating " << size << " bytes \n";

    return malloc(size);
}

void operator delete(void *memory, size_t size)
{
    std::cout << "freeing " << size << " bytes \n";

    free(memory);
}

TrafficLight::TrafficLight(int id, std::string name, int greenTime)
    : id(id), name(name), greenTime(greenTime), currentLightState(Red)
{
    pedestrian = new Pedestrian(); // Initialize the Pedestrian object dynamically
}
/*
TrafficLight::~TrafficLight()
{
    delete pedestrian;
} */

int TrafficLight::getId() const
{
    return id;
}
std::string TrafficLight::getName() const
{
    return name;
}
int TrafficLight::getGreenTime() const
{
    return greenTime;
}
LightState TrafficLight::getLightState() const
{
    return currentLightState;
}
std::string TrafficLight::getLightStateString() const
{
    switch (currentLightState)
    {
    case Green:
        return "*GREEN *";
    case Yellow:
        return "*YELLOW*";
    case Red:
        return "**RED **";
    default:
        return "UNKNOWN";
    }
}
Pedestrian *TrafficLight::getPedestrian() const
{
    return pedestrian;
}

void TrafficLight::setState(LightState state)
{
    currentLightState = state;
    // printState();
}

void TrafficLight::printState() const
{
    std::string stateString;
    switch (currentLightState)
    {
    case Green:
        stateString = "*GREEN *";
        break;
    case Yellow:
        stateString = "*Yellow*";
        break;
    case Red:
        stateString = "**RED **";
        break;
    }
    std::cout << "Traffic light " << name << ": " << stateString << std::endl;
}

bool TrafficLight::checkPedestrianStatus()
{
    if (pedestrian)
    {
        return true;
    }
    return false;
}
void TrafficLight::handleLightWithPedestrian()
{
    if (checkPedestrianStatus())
    { /*
        setState(Green); // should we really be doing this?
        std::cout << "traffic light" << name << "has turned green with envy" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(greenTime));
        pedestrian.reset();
        setState(Red);
    }
    else {
        setState(Red); */
    }
}