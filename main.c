#include <SDL2/SDL.h>

#define NUM_TARGETS 3

typedef struct {
    int x;
    int y;
    int w;
    int h;
    SDL_Color color;
    int is_dragging;
} Target;

Target targets[NUM_TARGETS] = {
    {100, 100, 50, 50, {255, 0, 0, 255}, 0},
    {200, 200, 50, 50, {0, 255, 0, 255}, 0},
    {300, 300, 50, 50, {0, 0, 255, 255}, 0},
};

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("Drag Targets", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Event event;
    while (1) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                break;
            } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                int x = event.button.x;
                int y = event.button.y;
                for (int i = 0; i < NUM_TARGETS; i++) {
                    if (x >= targets[i].x && x <= targets[i].x + targets[i].w && y >= targets[i].y && y <= targets[i].y + targets[i].h) {
                        targets[i].is_dragging = 1;
                    }
                }
            } else if (event.type == SDL_MOUSEBUTTONUP) {
                for (int i = 0; i < NUM_TARGETS; i++) {
                    targets[i].is_dragging = 0;
                }
            } else if (event.type == SDL_MOUSEMOTION) {
                int dx = event.motion.xrel;
                int dy = event.motion.yrel;
                for (int i = 0; i < NUM_TARGETS; i++) {
                    if (targets[i].is_dragging) {
                        targets[i].x += dx;
                        targets[i].y += dy;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        for (int i = 0; i < NUM_TARGETS; i++) {
            SDL_Rect rect = {targets[i].x, targets[i].y, targets[i].w, targets[i].h};
            SDL_SetRenderDrawColor(renderer, targets[i].color.r, targets[i].color.g, targets[i].color.b, targets[i].color.a);
            SDL_RenderFillRect(renderer, &rect);
        }

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}