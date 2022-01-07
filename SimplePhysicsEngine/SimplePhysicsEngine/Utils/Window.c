#include "Window.h"

Window *Window_New(int width, int height)
{
    Window *window = NULL;
    Renderer *renderer = NULL;
    int exitStatus;

    window = (Window *)calloc(1, sizeof(Window));
    if (!window) goto ERROR_LABEL;

    renderer = (Renderer *)calloc(1, sizeof(Renderer));
    if (!renderer) goto ERROR_LABEL;

    window->m_renderer = renderer;
    renderer->m_width = width;
    renderer->m_height = height;

    window->m_windowSDL = SDL_CreateWindow(
        "Simple Physics Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height, SDL_WINDOW_OPENGL);

    if (!window->m_windowSDL)
    {
        printf("ERROR - SDL_CreateWindow\n");
        printf("      - SDL : %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    renderer->m_rendererSDL = SDL_CreateRenderer(
        window->m_windowSDL, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer->m_rendererSDL)
    {
        printf("ERROR - SDL_CreateRenderer\n");
        printf("      - SDL : %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    exitStatus = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    if (exitStatus == SDL_FALSE)
    {
        exitStatus = SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    }
    SDL_SetRenderDrawColor(renderer->m_rendererSDL, 0, 0, 0, 255);

    return window;

ERROR_LABEL:
    printf("ERROR - Window_New()\n");
    assert(false);
    Window_Free(window);
    return NULL;
}

void Window_Free(Window * window)
{
    if (!window) return;

    if (window->m_windowSDL)
    {
        SDL_DestroyWindow(window->m_windowSDL);
    }
    if (window->m_renderer)
    {
        Renderer *renderer = window->m_renderer;
        if (renderer->m_rendererSDL)
            SDL_DestroyRenderer(renderer->m_rendererSDL);

        free(renderer);
    }
    free(window);
}

Renderer *Window_GetRenderer(Window *window)
{
    return window->m_renderer;
}