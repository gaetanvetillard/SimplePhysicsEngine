#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#ifdef _WIN32
#  include <SDL.h>
#  include <SDL_image.h>
#else
#  include <SDL2/SDL.h>
#  include <SDL2/SDL_image.h>
#endif

#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/// @brief Initialise la SDL.
/// @return EXIT_SUCCESS ou EXIT_FAILURE.
int Settings_InitSDL();

/// @brief Quitte la SDL.
void Settings_QuitSDL();

#endif