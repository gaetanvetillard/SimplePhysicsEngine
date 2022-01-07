#ifndef _TEXTURES_H_
#define _TEXTURES_H_

#include "../Settings.h"
#include "../Utils/Renderer.h"

#define LAYER_COUNT 5

typedef struct Textures_s
{
    /// Textures des balles

    SDL_Texture* m_body;
    SDL_Texture* m_bodyGirafe;
    SDL_Texture* m_bodySpider;
    SDL_Texture* m_bodySnail;
    SDL_Texture* m_bodyPanda;

    /// Textures des ressorts
    SDL_Texture* m_spring;
    SDL_Texture* m_springInactive;
    SDL_Texture* m_springBambou;

    SDL_Texture* m_ground;

    /// Texture des étoiles
    SDL_Texture* m_star;

    /// Texture de la croix rouge
    SDL_Texture* m_redCross;

    SDL_Texture* m_layers[LAYER_COUNT];
} Textures;

Textures *Textures_New(Renderer *renderer);
void Textures_Free(Textures *tex);

#endif
