#include "SDL3/SDL_gpu.h"
#include "common.h"
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "sim.h"

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_GPUDevice *device = NULL;

#define WINDOW_WIDTH  640*2
#define WINDOW_HEIGHT 480*2

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[]) {
    SDL_SetAppMetadata("Balls", "1.0", "com.example.balls");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("Balls", WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!( device = SDL_CreateGPUDevice(SDL_GPU_SHADERFORMAT_SPIRV, 0, "0") )) {
        SDL_Log("Couldn't aquire GPU device: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_ClaimWindowForGPUDevice(device, window);

    SDL_GPUShaderCreateInfo as;

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            VerletObject vo = {
                .pos = (Vec2) {event->button.x, event->button.y},
            };
            vo.pos_old = vo.pos;
            push(vo);
            break;
        
        default:
            break;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

void simulate() {
    update(1);
}

void draw() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    for (int i = 0; i < object_count; i++) {
        SDL_FRect rect;
        rect.x = objects[i].pos.x;
        rect.y = objects[i].pos.y;
        rect.w = rect.h = 10.0f;
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);  /* put it all on the screen! */
}

SDL_AppResult SDL_AppIterate(void *appstate) {
    const Uint64 now = SDL_GetTicks();

    simulate();
    draw();

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result) {
    SDL_Log("Exiting gracefully.");
}
