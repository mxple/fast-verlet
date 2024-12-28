#ifndef SIM_H
#define SIM_H

#include "verlet.h"

#define MAX_OBJECTS 100000
#define DT 0.01

// Constants
extern const Vec2 gravity;
extern const float obj_radius;
extern const float radius;
extern const float radius2;

extern VerletObject objects[MAX_OBJECTS];
extern int object_count;

void push(VerletObject vo);

void update(float dt);

void apply_constraint();
void solve_collisions();

#endif
