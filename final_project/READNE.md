# Maze Explorer Robot

## Overview
The goal of this project is to create a simulated robot that can explore a maze and find the finish block. The robot randomly selects directions and navigates through the maze until it reaches the green finish block, at which point it displays a "Maze completed!" message.

## Key Challenges and Solutions
- **Random Direction Selection**: The robot uses a random number generator to randomly choose between turning left or right when encountering an obstacle. This helps the robot explore the maze more effectively and avoid getting stuck in certain configurations.
- **Obstacle Detection and Avoidance**: The robot utilizes range sensors to detect obstacles in front of it. When an obstacle is detected, it initiates a random turn and continues turning until there is enough clearance in front of it.
- **Finish Block Detection**: The robot checks its position against the coordinates of the finish block. When it reaches the finish block, it stops moving and displays the "Maze completed!" message.

## Installation and Usage

### Prerequisites
- Docker installed on your system

### Running the Project
1. Clone this repository to your local machine.
2. Navigate to the project directory.
3. Run the following command to start the ENVIRO container:
4. docker run -p80:80 -p8765:8765 -v ${PWD}:/source -it klavins/enviro:v1.6 bash
    Inside the container, navigate to the project directory (`/source`).
5. Build the project by running `make`.
6. Start the ENVIRO server by running `enviro`.
7. Open your web browser and visit `http://localhost:8765` to see the simulation.

## Acknowledgments
This project was developed using the [ENVIRO](https://github.com/keyboard/enviro) multi-agent simulator, which is based on the [elma](https://github.com/keyboard/elma) Event Loop MAnager library. The documentation for these libraries was instrumental in creating this project.


