#include "agent.h"
#include "conf.h"
#include <math.h>
#include <stdlib.h>

Agent* initAgent(Vector2 pos, float angle) {
	Agent* agent = malloc(sizeof(Agent));
	agent->position = pos;
	agent->angle = angle;
	return agent;
}

void freeAgent(Agent* agent) {
	free(agent);
}

int sense(Agent* agent, float direction, Color* pixels) {
	int centerX = agent->position.x + senseDistance*cos(agent->angle + direction);
	int centerY = agent->position.y + senseDistance*sin(agent->angle + direction);
	int sum = 0;
	for (int i = -senseRadius; i <= senseRadius; i++) {
		for (int j = -senseRadius; j <= senseRadius; j++) {
			if (!(centerY+j >= screenHeight || centerY+j<0 || centerX+i >= screenWidth || centerX+i < 0)) {
				Color sensed = pixels[(screenHeight - 1 - (centerY + j)) * screenWidth + centerX + i];
				sum += sensed.r + sensed.g + sensed.b;
			}
		}
	}
	return sum;
}

void updateAgent(Agent* agent, Color* pixels) {
	agent->position.x += speed*cos(agent->angle);
	agent->position.y += speed*sin(agent->angle);
	if (agent->position.x >= screenWidth) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI + PI / 2;
		agent->position.x = screenWidth - 1;
	} else if (agent->position.x < 0) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI - PI / 2;
		agent->position.x = 0;
	}
	if (agent->position.y >= screenHeight) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI + PI;
		agent->position.y = screenHeight-1;
	} else if (agent->position.y < 0) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI;
		agent->position.y = 0;
	}

	int left = sense(agent, -senseAngle, pixels);
	int mid = sense(agent, 0, pixels);
	int right = sense(agent, senseAngle, pixels);

	if ((left > mid && left > right && left > 20)) {
		agent->angle -= randomTurnStrength ? (float)rand()/(float)RAND_MAX * maxTurnStrength : maxTurnStrength;
	} else if ((right > mid && right > left && right > 20)) {
		agent->angle += randomTurnStrength ? (float)rand()/(float)RAND_MAX * maxTurnStrength : maxTurnStrength;
	}

	float randomness = ((float)rand()/(float)RAND_MAX - 0.5) * randomAngleChange;
	agent->angle += randomness;

	if (randomDirection && rand() % randomDirectionChance == 0) {
		agent->angle = (float)rand()/(float)RAND_MAX * 2 * PI;
	}
}

