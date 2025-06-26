#include "conf.h"
#include <math.h>
#include <stdlib.h>

int screenWidth = 800;
int screenHeight = 800;
int agentCount = 100000;

int senseDistance = 32;
int senseRadius = 1;
float senseAngle = PI/6;

float maxTurnStrength = PI/12;
bool randomTurnStrength = true;
int randomDirectionChance = 100000;
bool randomDirection = true;
float randomAngleChange = PI/64;

float speed = 1;

void spawnAgents(Agent** agents) {
	for (int i = 0; i < agentCount; i++) {
		float dist = (float)rand()/(float)RAND_MAX * 300;
		float angle = (float)rand()/(float)RAND_MAX * 2 * PI;
		agents[i] = initAgent((Vector2) {400 + dist*cos(angle), 400 + dist*sin(angle)}, PI + angle);
	}
}
