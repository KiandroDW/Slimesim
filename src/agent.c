#include "agent.h"
#include "consts.h"
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

void updateAgent(Agent* agent) {
	agent->position.x += cos(agent->angle);
	agent->position.y += sin(agent->angle);
	if (agent->position.x >= WIDTH) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI + PI / 2;
	} else if (agent->position.x <= 0) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI - PI / 2;
	}
	if (agent->position.y >= HEIGHT) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI + PI;
	} else if (agent->position.y <= 0) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI;
	}
}

int sense(Agent* agent, float direction, Color* pixels) {
	int centerX = agent->position.x + 5*cos(agent->angle + direction);
	int centerY = agent->position.y + 5*sin(agent->angle + direction);
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!(centerY+j >= HEIGHT || centerY+j<0 || centerX+i >= WIDTH || centerX+i < 0)) {
				Color sensed = pixels[(centerY + j) * WIDTH + centerX + i];
			}
		}
	}
	return 0;
}
