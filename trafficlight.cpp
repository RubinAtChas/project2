#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
std::mutex mtx;

enum class Lightstate
{
    RED,
    YELLOW,
    GREEN
}; // CREATNG AN ENUM TO MANIPULATE THE STATE OF THE TRAFICLIGHTS, BETWEEN RED, GREEN AND YELLOW.
void stateToString(Lightstate state)
{
    switch (state)
    {
    case Lightstate::RED:
        std::cout << "RED\n";
        break;
    case Lightstate::YELLOW:
        std::cout << "YELLOW\n";
        break;
    case Lightstate::GREEN:
        std::cout << "GREED\n";
        break;
    }
}

void trafficController() // STATEMACHINE, Is controlling the state of enum class.
{
    std::cout << "ÄR INNE I TRAFFICCONTROLLER\n";
    Lightstate currentState = Lightstate::RED;
    // mtx.lock();
    switch (currentState)
    {
    case Lightstate::RED:
        std::this_thread::sleep_for(std::chrono::seconds(3));
        currentState = Lightstate::YELLOW;
        std::cout << "ÄR INNE I CASE RED\n";
        stateToString(currentState);
        break;
    case Lightstate::YELLOW:
        std::this_thread::sleep_for(std::chrono::seconds(3));
        currentState = Lightstate::RED;
        std::cout << "ÄR INNE I CASE GUL\n";
        stateToString(currentState);
        break;
    case Lightstate::GREEN:
        std::this_thread::sleep_for(std::chrono::seconds(3));
        currentState = Lightstate::RED;
        std::cout << "ÄR INNE I CASE GRÖN\n";
        stateToString(currentState);
        break;

    default:
        break;
    }

    // mtx.unlock();
}

bool activatesPedastrianMenu() // Input for Pedastrain cross walk, if TRUE await green for pedastrians, if false continues to be red
{
    
    switch (expression)
    {
    case /* constant-expression */:
        /* code */
        break;
    
    default:
        break;
    }
}
int main()
{
    std::thread trafficController1(trafficController);

    trafficController1.join();
}
