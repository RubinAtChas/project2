#include "TrafficLight.h"

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
std::string TrafficLight::getLightStateString() const {
    switch (currentLightState) {
        case Green: return "*GREEN *";
        case Yellow: return "*YELLOW*";
        case Red: return "**RED **";
        default: return "UNKNOWN";
    }
}


void TrafficLight::setState(LightState state)
{
    currentLightState = state;
    //printState();
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