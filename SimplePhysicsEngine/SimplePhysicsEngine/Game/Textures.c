#include "Textures.h"

Textures *Textures_New(Renderer *renderer)
{
    Textures *textures = NULL;
    char path[1024] = { 0 };

    textures = (Textures *)calloc(1, sizeof(Textures));
    if (!textures) goto ERROR_LABEL;

    textures->m_body = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/Body.png");
    if (!textures->m_body)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    textures->m_spring = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/Spring.png");
    if (!textures->m_spring)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    textures->m_springInactive = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/Spring_Inactive.png");
    if (!textures->m_springInactive)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    textures->m_ground = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/Ground_Tile.png");
    if (!textures->m_ground)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    for (int i = 0; i < LAYER_COUNT; ++i)
    {
        sprintf(path, "../Assets/Background_Layer%d.png", i);
        textures->m_layers[i] = IMG_LoadTexture(renderer->m_rendererSDL, path);
        if (!textures->m_layers[i])
        {
            printf("ERROR - IMG_LoadTexture\n");
            printf("      - %s\n", SDL_GetError());
            goto ERROR_LABEL;
        }
    }

    return textures;

ERROR_LABEL:
    printf("ERROR - Textures_New()\n");
    assert(false);
    Textures_Free(textures);
    return NULL;
}

void Textures_Free(Textures *textures)
{
    if (!textures) return;

    if (textures->m_body)
    {
        SDL_DestroyTexture(textures->m_body);
    }
    if (textures->m_spring)
    {
        SDL_DestroyTexture(textures->m_spring);
    }
    if (textures->m_springInactive)
    {
        SDL_DestroyTexture(textures->m_springInactive);
    }
    if (textures->m_ground)
    {
        SDL_DestroyTexture(textures->m_ground);
    }
    for (int i = 0; i < LAYER_COUNT; ++i)
    {
        if (textures->m_layers[i])
        {
            SDL_DestroyTexture(textures->m_ground);
        }
    }

    // Met la mémoire à zéro (sécurité)
    memset(textures, 0, sizeof(Textures));

    free(textures);
}