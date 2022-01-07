#include "Settings.h"

int Settings_InitSDL()
{
    // Initialise la SDL2
    int flags = SDL_INIT_VIDEO;
    if (SDL_Init(flags) < 0)
    {
        printf("ERROR - SDL_Init %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Initialise la SDL2 image
    flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (IMG_Init(flags) != flags)
    {
        printf("ERROR - IMG_Init %s\n", IMG_GetError());
    }

    return EXIT_SUCCESS;
}

void Settings_QuitSDL()
{
    IMG_Quit();
    SDL_Quit();
}