#include "verlet.h"

void update_verlet(VerletObject* vo, float dt, Vec2 accel) {
    const Vec2 velocity = {
        .x = vo->pos.x - vo->pos_old.x,
        .y = vo->pos.y - vo->pos_old.y
    };
    vo->pos_old = vo->pos;

    vo->pos.x += velocity.x + accel.x * dt * dt;
    vo->pos.y += velocity.y + accel.y * dt * dt;
}

