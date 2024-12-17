#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <condition_variable>
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

    Lightstate trafficController(Lightstate currentState, int number) // STATEMACHINE, Is controlling the state of enum class.
    {
        std::cout << number << std::endl;
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
    Lightstate light3 = Lightstate::RED;
    Lightstate light4 = Lightstate::RED;
    TrafficLight trafficLight1(light1); // begins as red
    TrafficLight trafficLight2(light2); // begins as red
    TrafficLight trafficLight3(light3); // begins as green
    TrafficLight trafficLight4(light4); // begins as green
    bool turn1 = false;
    while(true)
    {
        if(trafficLight1.getCurrentState() == Lightstate::RED && trafficLight2.getCurrentState() == Lightstate::RED && turn1 == false)
        {
            std::thread t1([&trafficLight1]() { // wtf is a capture list
            std::cout << "Hello from the lambda thread!" << std::endl;
            trafficLight1.setCurrentState(trafficLight1.trafficController(trafficLight1.getCurrentState(), 1));
             });
            std::thread t2([&trafficLight2]() { // wtf is a capture list
            std::cout << "Hello from the lambda thread!" << std::endl;
            trafficLight2.setCurrentState(trafficLight2.trafficController(trafficLight2.getCurrentState(), 2));
            });
            t1.join();
            t2.join();
            turn1 = true;
            //trafficLight1.setCurrentState(trafficLight1.trafficController(trafficLight1.getCurrentState(), 1));
            //trafficLight2.setCurrentState(trafficLight2.trafficController(trafficLight2.getCurrentState(), 2));
            //if(trafficLight1.getCurrentState() == Lightstate::GREEN && trafficLight2.getCurrentState() == Lightstate::GREEN);
        }
        if(trafficLight3.getCurrentState() == Lightstate::RED && trafficLight4.getCurrentState() == Lightstate::RED && turn1 == true)
        {   
            std::thread t1([&trafficLight3]() { // wtf is a capture list
            std::cout << "Hello from the lambda thread!" << std::endl;
            trafficLight3.setCurrentState(trafficLight3.trafficController(trafficLight3.getCurrentState(), 3));
            });
            //trafficLight3.trafficController(trafficLight3.getCurrentState(), 3);
            std::thread t2([&trafficLight4]() { // wtf is a capture list
            std::cout << "Hello from the lambda thread!" << std::endl;
            trafficLight4.setCurrentState(trafficLight4.trafficController(trafficLight4.getCurrentState(), 4));
            });
            turn1 = false;
        }
    }
}

int main()
{ 
    trafficSyncing();
    // std::thread trafficController1(trafficController);

    //trafficController1.join();
}
