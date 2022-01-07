#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include "../Settings.h"
#include "../Utils/Renderer.h"

#define LAYER_COUNT 5

typedef struct Textures_s
{
    SDL_Texture *m_body;
    SDL_Texture *m_spring;
    SDL_Texture *m_springInactive;
    SDL_Texture *m_ground;
    SDL_Texture *m_layers[LAYER_COUNT];
} Textures;

Textures *Textures_New(Renderer *renderer);
void Textures_Free(Textures *tex);

#endif
