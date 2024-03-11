
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "robot1.h"
#include <random>

using namespace enviro;

void robot1Controller::init()
{
    // Seed the random number generator
    srand(static_cast<unsigned int>(time(0)));
}

void robot1Controller::update()
{
    double front_sensor = sensor_value(0);

    // Random number generator
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis(0, 1);

    // Check if the robot is currently turning
    static bool is_turning = false;
    static double turn_speed = 0.0;

    // Check if the robot has reached the end of the maze
    if (x() > 250 && y() > -170)
    {
        // Robot has reached the end, stop
        track_velocity(0, 0);
        std::cout << "Maze completed!" << std::endl;
    }
    else if (!is_turning)
    {
        // Move forward if there's enough clearance in front
        if (front_sensor > 30)
        {
            track_velocity(20, 0);
        }
        // If there's an obstacle in front
        else
        {
            // Initiate a random left or right turn
            if (dis(gen) == 0)
            {
                turn_speed = 5.0; // Turn left
            }
            else
            {
                turn_speed = -5.0; // Turn right
            }
            is_turning = true;
        }
    }
    else
    {
        // Keep turning until there's enough clearance in front
        track_velocity(0, turn_speed);
        if (front_sensor > 100)
        {
            is_turning = false;
            turn_speed = 0.0;
        }
    }
}
