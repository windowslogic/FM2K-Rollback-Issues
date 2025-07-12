// SDL version of DirectDraw version made earlier.
// THIS CODE IS FOR DEMONSTRATION PURPOSES ONLY AND DOES NOT COMPILE.

#include <SDL.h>

SDL_Window* window;
SDL_Renderer* renderer;

void InitSDL() {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("SDL Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_Rect rect = { 100, 100, 200, 150 };
    SDL_RenderFillRect(renderer, &rect);

    SDL_RenderPresent(renderer);
}

void Cleanup() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    InitSDL();

    bool running = true;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
        Render();
    }

    Cleanup();
    return 0;
}
