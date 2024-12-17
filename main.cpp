#include "trafficLight.h"
#include "TrafficLightManager.h"
#include <cstdlib>

int main()
{
    system("CLS");
    TrafficLight trafficLightNSLeftTurn(0, "North/South-bound left turn lane", 5);
    TrafficLight trafficLightNSStraight(1, "North/South-bound straight(Right turn) lane", 10);

    TrafficLight trafficLightEWLeftTurn(2, "East/West-bound left turn lane", 5);
    TrafficLight trafficLightEWStraight(3, "East/West-bound straight(Right turn) lane", 10);

    TrafficLightManager manager;

    manager.addTrafficLight(trafficLightNSLeftTurn); //Entry 0
    manager.addTrafficLight(trafficLightNSStraight); //Entry 1
    manager.addTrafficLight(trafficLightEWLeftTurn); //Entry 2
    manager.addTrafficLight(trafficLightEWStraight); //Entry 3

    std::thread runThread([&manager]() { manager.run(); });

    while (true)
    {
        manager.graphicsDisplay();
    }
}
