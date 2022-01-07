#include "Renderer.h"

int Renderer_GetWidth(Renderer *renderer)
{
    return renderer->m_width;
}

int Renderer_GetHeight(Renderer *renderer)
{
    return renderer->m_height;
}

void Renderer_Clear(Renderer* renderer)
{
    SDL_Renderer* rendererSDL = renderer->m_rendererSDL;
    SDL_SetRenderDrawColor(rendererSDL, (Uint8)0, (Uint8)0, (Uint8)0, (Uint8)255);
    SDL_RenderClear(rendererSDL);
}

void Renderer_Fill(Renderer *renderer, Color color)
{
    SDL_Rect rect = { 0 };
    SDL_Renderer* rendererSDL = renderer->m_rendererSDL;

    rect.x = 0;
    rect.y = 0;
    rect.w = renderer->m_width;
    rect.h = renderer->m_height;

    SDL_SetRenderDrawBlendMode(rendererSDL, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(rendererSDL, (Uint8)color.r, (Uint8)color.g, (Uint8)color.b, (Uint8)color.a);
    SDL_RenderFillRect(rendererSDL, &rect);
}

Color Color_Set(int r, int g, int b, int a)
{
    Color color = { 0 };
    color.r = (uint8_t)r;
    color.g = (uint8_t)g;
    color.b = (uint8_t)b;
    color.a = (uint8_t)a;

    return color;
}

void Renderer_Update(Renderer* renderer)
{
    SDL_RenderPresent(renderer->m_rendererSDL);
}