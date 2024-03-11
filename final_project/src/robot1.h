#ifndef __ROBOT1_AGENT__H
#define __ROBOT1_AGENT__H

#include "enviro.h"

using namespace enviro;

class robot1Controller : public Process, public AgentInterface
{
public:
    robot1Controller() : Process(), AgentInterface() {}

    void init();
    void start() {}
    void update();
    void stop() {}

private:
    // Add any private member variables or methods here
};

class robot1 : public Agent
{
public:
    robot1(json spec, World &world) : Agent(spec, world)
    {
        add_process(c);
    }

private:
    robot1Controller c;
};

DECLARE_INTERFACE(robot1)

#endif