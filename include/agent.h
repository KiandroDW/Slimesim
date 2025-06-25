#ifndef AGENT
#define AGENT

#include <raylib.h>

typedef struct {
	Vector2 position;
	float angle;
} Agent;

Agent* initAgent(Vector2 pos, float angle);
void freeAgent(Agent* agent);
void updateAgent(Agent* agent);

#endif
