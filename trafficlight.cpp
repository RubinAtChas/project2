#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <string>
#include <condition_variable>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <atomic>

std::mutex mtx;
std::condition_variable cv;
bool pedastrianState = false;
bool roadState = false;
bool pedastrianReady = false;
std::atomic<bool> pedestrianButtonPressed(false);
enum class Lightstate
{
    RED,
    YELLOW,
    GREEN
};

class TrafficLight
{
private:
    Lightstate currentState = Lightstate::RED;

public:
    // TrafficLight(Lightstate currentState) : currentState(currentState) {}

    Lightstate getCurrentState() { return currentState; }

    void setCurrentState(Lightstate input) { currentState = input; }

    void printRoadState()
    {
        switch (currentState)
        {
        case Lightstate::RED:
            logState("Car traffic light: RED\n");
            break;
        case Lightstate::YELLOW:
            logState( "Car traffic light: YELLOW\n");
            break;
        case Lightstate::GREEN:
            logState("Car traffic light: GREEN\n");
            break;
        }
    }
   void logState(const std::string &event)
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "[" << std::put_time(localtime(&now_c), "%T") << "] " << event << std::endl;
} 
};


void controlTrafficLights(TrafficLight &carLight)
{
    while (true)
    {
        {
            std::unique_lock<std::mutex> lock(mtx);
            carLight.setCurrentState(Lightstate::RED);
            roadState = true;
            pedastrianReady = true;
            carLight.printRoadState();
            cv.notify_all();
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
        {
            std::unique_lock<std::mutex> lock(mtx);
            roadState = false;
            pedastrianReady = false;
            cv.wait(lock, []
                    { return !pedastrianState; });
            carLight.setCurrentState(Lightstate::YELLOW);
            carLight.printRoadState();
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
        {
            std::unique_lock<std::mutex> lock(mtx);

            carLight.setCurrentState(Lightstate::GREEN);
            carLight.printRoadState();
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
        if (pedestrianButtonPressed.load())
        {
    
        {
            std::unique_lock<std::mutex> lock(mtx);
            roadState = false;
            pedastrianReady = false;
            cv.wait(lock, []
                    { return !pedastrianState; });
            carLight.setCurrentState(Lightstate::YELLOW);
            carLight.printRoadState();
        }
        }
        
        pedestrianButtonPressed.store(false);
         std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

void pedestrianLight()
{
    TrafficLight pedastrianInstance;
    while (true)
    {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, []
                { return roadState && pedastrianReady; });
        pedastrianState = true;
        pedastrianInstance.logState("Pedastrian Light: GREEN\n");
        lock.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(5));
        lock.lock();
        pedastrianState = false;
        pedastrianInstance.logState("Pedastrian Light: RED\n");
        cv.notify_all();
    }
}
void pedestrianButton()
{
    while (true)
    {
        std::cout << "Press 'p' to simulate pedestrian button press: ";
        char input;
        std::cin >> input;
        if (input == 'p')
        {
            pedestrianButtonPressed.store(true); // Simulera knapptryckning
            std::cout << "Pedestrian button pressed!\n";
        }
    }
}

int main()
{
    TrafficLight carLight;

    std::thread carTraffic(controlTrafficLights, std::ref(carLight));
    std::thread pedestrianTraffic(pedestrianLight);
    std::thread buttomPress(pedestrianButton);

    carTraffic.join();
    pedestrianTraffic.join();
    buttomPress.join();
    return 0;
}

/*
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
    while (true)
    {
        if (trafficLight1.getCurrentState() == Lightstate::RED && trafficLight2.getCurrentState() == Lightstate::RED && turn1 == false)
        {
            std::thread t1([&trafficLight1]() { // wtf is a capture list
                std::cout << "Hello from the lambda thread 1!" << std::endl;
                trafficLight1.setCurrentState(trafficLight1.trafficController(trafficLight1.getCurrentState(), 1));
            });
            std::thread t2([&trafficLight2]() { // wtf is a capture list
                std::cout << "Hello from the lambda thread 2!" << std::endl;
                trafficLight2.setCurrentState(trafficLight2.trafficController(trafficLight2.getCurrentState(), 2));
            });
            t1.join();
            t2.join();
            turn1 = true;
            // trafficLight1.setCurrentState(trafficLight1.trafficController(trafficLight1.getCurrentState(), 1));
            // trafficLight2.setCurrentState(trafficLight2.trafficController(trafficLight2.getCurrentState(), 2));
            // if(trafficLight1.getCurrentState() == Lightstate::GREEN && trafficLight2.getCurrentState() == Lightstate::GREEN);
        }
        if (trafficLight3.getCurrentState() == Lightstate::RED && trafficLight4.getCurrentState() == Lightstate::RED && turn1 == true)
        {
            std::thread t1([&trafficLight3]() { // wtf is a capture list
                std::cout << "Hello from the lambda thread 3!" << std::endl;
                trafficLight3.setCurrentState(trafficLight3.trafficController(trafficLight3.getCurrentState(), 3));
            });
            // trafficLight3.trafficController(trafficLight3.getCurrentState(), 3);
            std::thread t2([&trafficLight4]() { // wtf is a capture list
                std::cout << "Hello from the lambda thread 4!" << std::endl;
                trafficLight4.setCurrentState(trafficLight4.trafficController(trafficLight4.getCurrentState(), 4));
            });
            t1.join();
            t2.join();
            turn1 = false;
        }
    }
}*/

// trafficSyncing();
// std::thread trafficController1(trafficController);

// trafficController1.join();
