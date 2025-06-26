#ifndef CONF
#define CONF

#include "agent.h"
#include <stdbool.h>

extern int screenWidth; // Width of the screen
extern int screenHeight; // Height of the screen
extern int agentCount; // Number of agents to simulate

extern int senseDistance; // Distance from the agent to look for feromones
extern int senseRadius; // The agent will sense in a 2n+1 x 2n+1 square for feromones
extern float senseAngle; // Angle between the sense directions.

extern float maxTurnStrength; // Maximum strength of turning towards feromones
extern bool randomTurnStrength; // When true, the turn strength will be [0-1]*maxTurnStrength
extern int randomDirectionChance; // Agents will have a 1/n chance to turn in a random direction
extern bool randomDirection; // When false, agents won't follow the previous chance and never change direction randomly
extern float randomAngleChange; // Random angle smaller than randomAngleChange will be aplied each frame to the agents (set to 0 if none)

extern float speed; // speed of the agents

void spawnAgents(Agent** agents); // Function to create custom spawn conditions for the agents

#endif
