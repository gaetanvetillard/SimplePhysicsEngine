#include "Textures.h"

Textures *Textures_New(Renderer *renderer)
{
    Textures *textures = NULL;
    char path[1024] = { 0 };

    textures = (Textures *)calloc(1, sizeof(Textures));
    if (!textures) goto ERROR_LABEL;

    // On charge les textures des balles

    textures->m_body = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/Body.png");
    if (!textures->m_body)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    textures->m_bodyGirafe = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/BodyGirafe.png");
    if (!textures->m_bodyGirafe)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    textures->m_bodySnail = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/BodySnail.png");
    if (!textures->m_bodySnail)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    textures->m_bodySpider = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/BodySpider.png");
    if (!textures->m_bodySpider)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    textures->m_bodyPanda = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/BodyPanda.png");
    if (!textures->m_bodyPanda)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    // On charge les ressorts

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

    textures->m_springBambou = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/SpringBambou.png");
    if (!textures->m_springBambou)
    {
        printf("ERROR - IMG_LoadTexture\n");
        printf("      - %s\n", SDL_GetError());
        goto ERROR_LABEL;
    }

    // On charge l'étoile

    textures->m_star = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/Star.png");
    if (!textures->m_star)
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

    // On charge la croix rouge

    textures->m_redCross = IMG_LoadTexture(renderer->m_rendererSDL, "../Assets/RedCross.png");
    if (!textures->m_redCross)
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

    // on supprime les textures

    if (textures->m_body) SDL_DestroyTexture(textures->m_body);
    if (textures->m_bodyGirafe) SDL_DestroyTexture(textures->m_bodyGirafe);
    if (textures->m_bodySnail) SDL_DestroyTexture(textures->m_bodySnail);
    if (textures->m_bodySpider) SDL_DestroyTexture(textures->m_bodySpider);
    if (textures->m_bodyPanda) SDL_DestroyTexture(textures->m_bodyPanda);

    if (textures->m_spring)
    {
        SDL_DestroyTexture(textures->m_spring);
    }
    if (textures->m_springInactive)
    {
        SDL_DestroyTexture(textures->m_springInactive);
    }

    if (textures->m_springBambou) SDL_DestroyTexture(textures->m_springBambou);
    if (textures->m_star) SDL_DestroyTexture(textures->m_star);
    if (textures->m_redCross) SDL_DestroyTexture(textures->m_redCross);
    

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