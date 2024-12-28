#ifndef VERLET_H
#define VERLET_H

#include "common.h"

typedef struct {
    Vec2 pos;
    Vec2 pos_old;
    // Vec2 accel;
} VerletObject;

void update_verlet(VerletObject* vo, float dt, Vec2 accel);

#endif
