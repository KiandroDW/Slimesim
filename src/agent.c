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

int sense(Agent* agent, float direction, Color* pixels) {
	int centerX = agent->position.x + 16*cos(agent->angle + direction);
	int centerY = agent->position.y + 16*sin(agent->angle + direction);
	int sum = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!(centerY+j >= HEIGHT || centerY+j<0 || centerX+i >= WIDTH || centerX+i < 0)) {
				Color sensed = pixels[(HEIGHT - 1 - (centerY + j)) * WIDTH + centerX + i];
				sum += sensed.r + sensed.g + sensed.b;
			}
		}
	}
	return sum;
}

void updateAgent(Agent* agent, Color* pixels) {
	agent->position.x += cos(agent->angle);
	agent->position.y += sin(agent->angle);
	if (agent->position.x >= WIDTH) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI + PI / 2;
		agent->position.x = WIDTH - 1;
	} else if (agent->position.x < 0) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI - PI / 2;
		agent->position.x = 0;
	}
	if (agent->position.y >= HEIGHT) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI + PI;
		agent->position.y = HEIGHT-1;
	} else if (agent->position.y < 0) {
		agent->angle = (float)rand()/(float)RAND_MAX * PI;
		agent->position.y = 0;
	}

	int left = sense(agent, -PI/6, pixels);
	int mid = sense(agent, 0, pixels);
	int right = sense(agent, PI/6, pixels);

	if ((left > mid && left > right && left > 20)) {
		agent->angle -= PI/16;
	} else if ((right > mid && right > left && right > 20)) {
		agent->angle += PI/16;
	}

	float randomness = ((float)rand()/(float)RAND_MAX - 0.5) * PI/54;
	agent->angle += randomness;

	if (rand() % 10000 == 0) { // 1 in 10000 chance for random direction
		agent->angle = (float)rand()/(float)RAND_MAX * 2 * PI;
	}
}

