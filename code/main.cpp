#include <stdio.h>
#include "SDL.h"
#include "constants.h"
// #include "include/glad/glad.h"

int game_is_running = 0;
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Rect rect;

bool is_selecting = false;

int last_frame_time = 0;

int initialize_window()
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
    {
        fprintf(stderr, "ERROR Initializing SDL.\n");
        return FALSE;
    }

    window = SDL_CreateWindow(NULL,
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WINDOW_WIDTH,
                              WINDOW_HEIGHT,
                              SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        fprintf(stderr, "Error creating sdl window.\n");
        return FALSE;
    }

    // SDL_GLContext context;
    // context = SDL_GL_CreateContext(window);

    // if (!context)
    // {
    //     fprintf(stderr, "Error creating sdl GL context.\n");
    //     return FALSE;
    // }

    // gladLoadGLLoader(SDL_GL_GetProcAddress);
    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  0);
    if (!renderer)
    {
        fprintf(stderr, "Error creating the rednerer");
    }
    return TRUE;
}

void setup()
{

}

void process_input()
{
    SDL_Event event;
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        game_is_running = 0;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            game_is_running = 0;
        }
        break;
    case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            is_selecting = true;
            rect.x = event.button.x;
            rect.y = event.button.y;
        }
        break;
    case SDL_MOUSEMOTION:
        if (is_selecting)
        {
            rect.w = event.motion.x - rect.x;
            rect.h = event.motion.y - rect.y;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        if (event.button.button == SDL_BUTTON_LEFT)
        {
            is_selecting = false;
            rect.w = 0;
            rect.h = 0;
        }
        break;
    }
}

void update()
{
    float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

    last_frame_time = SDL_GetTicks();

}

void render()
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 100);
    if (is_selecting)
    {
        SDL_RenderFillRect(renderer, &rect);
    }

    SDL_RenderPresent(renderer);
}

void destroy_game()
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    game_is_running = initialize_window();

    setup();

    while (game_is_running)
    {
        process_input();
        update();
        render();
    }
    destroy_game();
    return 0;
}