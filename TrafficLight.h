#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <iostream>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

// Enum to control the status of the traffic light. Written outside of the class to be acessable in other instanses of the program.
// This program does not include the pedestrian crossing light yet, but this enum can now be used even there
enum LightState {Green, Yellow, Red};

class TrafficLight
{
private:
    int id;
    std::string name;
    int greenTime;
    LightState currentLightState;

public:
    TrafficLight(int id, std::string name, int greenTime)
        : id(id), name(name), greenTime(greenTime), currentLightState(Red) {}

    // Getters for the different variables. We wont use the majority of them, I just made them all by default. 
    // When I think about it I don't even know we even enter an ID for the light when it's all said and done.
    int getId() const;
    std::string getName() const;
    int getGreenTime() const;
    LightState getLightState() const;

    // This one we specifically use for being able to convert the light state to a string. Vital for the graphics where we have to print the string char by char
    // to fit the graphics where it is printed vertically and every char is surrounded by other characters and/or spaces.
    std::string getLightStateString() const;

    //Setter used in our TrafficLightManager to set the state of the traffic light
    void setState(LightState state);

    //Print the specific traffic light and its current light state
    void printState() const;
};

#endif