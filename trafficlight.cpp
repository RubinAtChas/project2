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

class TrafficLight
{
private:
    Lightstate currentState = Lightstate::RED;
public:
   TrafficLight(Lightstate currentState) : currentState(currentState){std::cout << "Object Traffic Light has been constructed";}
   Lightstate getCurrentState()
   {
    return currentState;
   }
   void setCurrentState(Lightstate input)
   {
        currentState = input;
   }

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

    Lightstate trafficController(Lightstate currentState) // STATEMACHINE, Is controlling the state of enum class.
    {
        for(int i = 0; i < 3; i++)
        {
            // mtx.lock();
            switch (currentState)
            {
            case Lightstate::RED:
                std::this_thread::sleep_for(std::chrono::seconds(3));
                currentState = Lightstate::YELLOW;
                std::cout << "ÄR INNE I CASE RED\n";
                // stateToString(currentState);
                break;
            case Lightstate::YELLOW:
                std::this_thread::sleep_for(std::chrono::seconds(3));
                std::cout << "ÄR INNE I CASE GUL\n";
                currentState = Lightstate::GREEN;
                // stateToString(currentState);
                break;
            case Lightstate::GREEN:
                std::this_thread::sleep_for(std::chrono::seconds(3));
                currentState = Lightstate::RED;
                std::cout << "ÄR INNE I CASE GRÖN\n";
                // stateToString(currentState);
                break;

            default:
                break;
            }
        }
        return currentState;

        // mtx.unlock();
    } 
};

bool activatesPedastrianMenu() // Input for Pedastrain cross walk, if TRUE await green for pedastrians, if false continues to be red
{
    /*
    
    switch (expression)
    {
    case  constant-expression :
        break;
    
    default:
        break;
    } 
     */
}

void trafficSyncing()
{
    Lightstate light1 = Lightstate::RED;
    Lightstate light2 = Lightstate::RED;
    Lightstate light3 = Lightstate::GREEN;
    Lightstate light4 = Lightstate::GREEN;
    TrafficLight trafficLight1(light1); // begins as red
    TrafficLight trafficLight2(light2); // begins as red
    TrafficLight trafficLight3(light3); // begins as green
    TrafficLight trafficLight4(light4); // begins as green
    while(true)
    {
        if(trafficLight1.getCurrentState() == Lightstate::RED && trafficLight2.getCurrentState() == Lightstate::RED)
        {
            trafficLight1.setCurrentState(trafficLight1.trafficController(trafficLight1.getCurrentState()));
            trafficLight2.setCurrentState(trafficLight2.trafficController(trafficLight2.getCurrentState()));
            if(trafficLight1.getCurrentState() == Lightstate::GREEN && trafficLight2.getCurrentState() == Lightstate::GREEN);
        }
        else if(trafficLight3.getCurrentState() == Lightstate::RED && trafficLight4.getCurrentState() == Lightstate::RED)
        {
            trafficLight3.trafficController(trafficLight3.getCurrentState());
            trafficLight4.trafficController(trafficLight4.getCurrentState());
        }
    }
}

int main()
{ 
    trafficSyncing();
    // std::thread trafficController1(trafficController);

    //trafficController1.join();
}
