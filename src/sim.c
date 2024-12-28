#include "sim.h"
#include <math.h>

// Constants
const Vec2 gravity = {0.0f, 0.5f};
const float obj_radius = 10.0f;
const float radius = 400.0f;
const float radius2 = radius * radius;

VerletObject objects[MAX_OBJECTS];
int object_count;

void push(VerletObject vo) {
    objects[object_count++] = vo;
}

void update(float dt) {
    for (int i = 0; i < object_count; i++) {
        update_verlet(&objects[i], dt, gravity);

    }
    apply_constraint();
    solve_collisions();
}

void apply_constraint() {
    const Vec2 position = {.x = 800.0f, 450.0f};

    for (int i = 0; i < object_count; i++) {
        const float distx = (objects[i].pos.x - position.x);
        const float disty = (objects[i].pos.y - position.y);
        const float dist2 = distx * distx + disty * disty;

        if (dist2 > radius2) {
            objects[i].pos.x = position.x + distx * (radius2 / dist2);
            objects[i].pos.y = position.y + disty * (radius2 / dist2);
        }
    }
}

void solve_collisions() {
    for (int i = 0; i < object_count; i++) {
        for (int j = 0; j < object_count; j++) {
            if (i == j) continue;
            const float distx = objects[i].pos.x - objects[j].pos.x;
            const float disty = objects[i].pos.y - objects[j].pos.y;
            const float dist = sqrt(distx * distx + disty * disty);

            if (dist < 2 * obj_radius) {
                const float delta = 2 * obj_radius - dist;
                objects[i].pos.x += 0.5f * delta * (distx / dist);
                objects[i].pos.y += 0.5f * delta * (disty / dist);
                objects[j].pos.x -= 0.5f * delta * (distx / dist);
                objects[j].pos.y -= 0.5f * delta * (disty / dist);
            }
        }
    }
}
