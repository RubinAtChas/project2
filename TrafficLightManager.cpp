#include "TrafficLightManager.h"

// Function for adding a new traffic light to the vector. Not necessarily important to use a vector
// when we know how many lights we got, but why not.
void TrafficLightManager::addTrafficLight(TrafficLight light)
{
    trafficLights.push_back(light);
}
// A forever-loop that will run the different traffic lights one by one.
void TrafficLightManager::run()
{
    while (true)
    {
        //Makes sure to lock the thread so no other lights might turn green at the same time.
        std::unique_lock<std::mutex> lock(mtx);

        // Turn all lights red to be sure there will be no disasters
        for (auto& light : trafficLights)
        {
            light.setState(Red);
        }

        // Wait for three seconds to make sure all "late runners" are out of the way before turning green
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // The traffic light for the current Index will turn green.
        TrafficLight& greenLight = trafficLights[currentGreenLightIndex];
        greenLight.setState(Green);

        // Wait for the amount of time filled in as "greenTime" in the TrafficLight class
        cv.wait_for(lock, std::chrono::seconds(greenLight.getGreenTime()));

        // Switch to yellow, hard coded (3 seconds) for every light
        greenLight.setState(Yellow);
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Advance the Index for handeling traffic lights. I just learnt this way to use the modulus. 
        // When the Index hit the amount of traffic lights it is dividable and return to 0
        currentGreenLightIndex = (currentGreenLightIndex + 1) % trafficLights.size();

        // Notify all threads to let them know they are allowed to use the function(?)
        cv.notify_all();
    }
}


void TrafficLightManager::graphicsDisplay()
{
    // Clear the console at every update
    system("CLS");

    // We need to be able to print each individual Char from the string to be able to print then letter by letter in the vertical rows
    std::string verticalString1 = trafficLights[2].getLightStateString();
    std::string verticalString2 = trafficLights[3].getLightStateString();

    // Really sexy ASCII-graphics. Won't even tell you how long it took to get it right. I know the syntax is not right. but I'm already breaking most if not all
    // of the Geneva Conventions of programming as it is, so why stop there?
    std::cout << "                  |                      |                      ||                      |                      |\n"
              << "                  |                      |                      ||                      |                      |\n"
              << "                  |                      |                      ||                      |                      |\n"
              << "                  |                      |                      ||                      |                      |\n"
              << "                  |   #   #  ||   #   #  |   #   #  ||   #   #  ||   #   #   #   #   #  |   #   #   #   #   #  |\n"
              << "                  |   #   <==||   #   #  |   #   #  ||   #   #  ||   #   #   #   #   #  |   #   #   #   #   #  |\n"
              << "                  |   #   #  ||   #   #  |   #   #  ||   #   #  ||   #   #   #   #   #  |   #   #   #   #   #  |\n"
              << "                  |   #   #  \\/   #   #  |   #   #  |L==>#   #  ||   #   #   #   #   #  |   #   #   #   #   #  |\n"
              << "                  |                      |                      ||                      |                      |\n"
              << "------------------|-------" << trafficLights[1].getLightStateString() << "-------|-------" << trafficLights[0].getLightStateString() << "-------||----------------------|----------------------|------------------\n"
              << "                  |                                                                                            " << verticalString2[0] << "                  \n"
              << "     ##########   |                                                                                            " << verticalString2[1] << "   ##########     \n"
              << "                  |                                                                                            " << verticalString2[2] << "      ^           \n"
              << "     ##########   |                                                                                            " << verticalString2[3] << "   ###|######                "; trafficLights[0].printState();
    std::cout << "                  |                                                                                            " << verticalString2[4] << "   <=======       \n"
              << "     ##########   |                                                                                            " << verticalString2[5] << "   ##########                "; trafficLights[1].printState();
    std::cout << "                  |                                                                                            " << verticalString2[6] << "                  \n"
              << "     ##########   |                                                                                            " << verticalString2[7] << "   ##########     \n"
              << "------------------|                                                                                            |------------------\n"
              << "     ##########   |                                                                                            " << verticalString1[0] << "   ##########                "; trafficLights[2].printState();
    std::cout << "                  |                                                                                            " << verticalString1[1] << "                  \n"
              << "     ##########   |                                                                                            " << verticalString1[2] << "   ##########                "; trafficLights[3].printState();
    std::cout << "                  |                                                                                            " << verticalString1[3] << "      /====       \n"
              << "     ##########   |                                                                                            " << verticalString1[4] << "   ##||######     \n"
              << "                  |                                                                                            " << verticalString1[5] << "     \\/           \n"
              << "     ##########   |                                                                                            " << verticalString1[6] << "   ##########     \n"
              << "                  |                                                                                            " << verticalString1[7] << "                  \n"
              << "==================|                                                                                            |==================\n"
              << "                  " << verticalString1[0] << "                                                                                            |                  \n"
              << "     ##########   " << verticalString1[1] << "                                                                                            |   ##########     \n"
              << "           /\\     " << verticalString1[2] << "                                                                                            |                  \n"
              << "     ######||##   " << verticalString1[3] << "                                                                                            |   ##########     \n"
              << "       ====/      " << verticalString1[4] << "                                                                                            |                  \n"
              << "     ##########   " << verticalString1[5] << "                                                                                            |   ##########     \n"
              << "                  " << verticalString1[6] << "                                                                                            |                  \n"
              << "     ##########   " << verticalString1[7] << "                                                                                            |   ##########     \n"
              << "------------------|                                                                                            |------------------\n"
              << "     ##########   " << verticalString2[0] << "                                                                                            |   ##########     \n"
              << "                  " << verticalString2[1] << "                                                                                            |                  \n"
              << "     ##########   " << verticalString2[2] << "                                                                                            |   ##########     \n"
              << "       =======>   " << verticalString2[3] << "                                                                                            |                  \n"
              << "     ######|###   " << verticalString2[4] << "                                                                                            |   ##########     \n"
              << "           v      " << verticalString2[5] << "                                                                                            |                  \n"
              << "     ##########   " << verticalString2[6] << "                                                                                            |   ##########     \n"
              << "                  " << verticalString2[7] << "                                                                                            |                  \n"
              << "------------------|----------------------|----------------------||-------" << trafficLights[0].getLightStateString() << "-------|-------" << trafficLights[1].getLightStateString() << "-------|------------------\n"
              << "                  |                      |                      ||                      |                      |\n"
              << "                  |   #   #   #   #   #  |   #   #   #   #   #  ||   #   <==\\\\  #   #   |   #   #  /\\   #   #  |\n"
              << "                  |   #   #   #   #   #  |   #   #   #   #   #  ||   #   #  ||  #   #   |   #   #  ||   #   #  |\n"
              << "                  |   #   #   #   #   #  |   #   #   #   #   #  ||   #   #  ||  #   #   |   #   #  ||==>#   #  |\n"
              << "                  |   #   #   #   #   #  |   #   #   #   #   #  ||   #   #  ||  #   #   |   #   #  ||   #   #  |\n"
              << "                  |                      |                      ||                      |                      |\n"
              << "                  |                      |                      ||                      |                      |\n";

    // Update the graphics every halv second
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}