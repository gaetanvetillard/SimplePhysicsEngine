#include "Background.h"
#include "Scene.h"

void Background_Render(Scene *scene)
{
    Camera *camera = Scene_GetCamera(scene);
    Renderer *renderer = Scene_GetRenderer(scene);
    Textures *textures = scene->m_textures;
    Rect view = Camera_GetView(camera);

    float xShiftFactors[LAYER_COUNT] = { 0.0f, 0.05f, 0.2f, 0.4f, 0.6f };
    float yShiftFactors[LAYER_COUNT] = { 0.0f, 0.05f, 0.1f, 0.2f, 0.3f };

    // Couleur de remplissage (identique au ciel)
    Renderer_Fill(renderer, Color_Set(145, 134, 161, 255));

    // Dimension du fond dans le référentiel monde
    float worldW = 1.3f * 16.0f;
    float worldH = 1.3f * 9.0f;

    // Dessine les différents calques du fond (parallax)
    for (int i = 0; i < LAYER_COUNT; ++i)
    {
        Vec2 origin = Vec2_Set(
            view.x * (1.0f - xShiftFactors[i]),
            -0.2f + view.y * (1.0f - yShiftFactors[i])
        );

        int tileXMin = (int)floorf((view.x - origin.x) / worldW);
        int tileXMax = (int)ceilf((view.x + view.w - origin.x) / worldW);

        for (int tileXIdx = tileXMin; tileXIdx < tileXMax; ++tileXIdx)
        {
            int tileYIdx = 0;
            Vec2 lower = Vec2_Set(tileXIdx * worldW, (tileYIdx + 1) * worldH);
            Vec2 upper = Vec2_Set((tileXIdx + 1) * worldW, tileYIdx * worldH);

            lower = Vec2_Add(lower, origin);
            upper = Vec2_Add(upper, origin);

            float x0, x1, y0, y1;
            Camera_WorldToView(camera, lower, &x0, &y0);
            Camera_WorldToView(camera, upper, &x1, &y1);

            SDL_FRect dstRect = { 0 };
            dstRect.x = x0;
            dstRect.y = y0;
            dstRect.w = fabsf(x1 - x0);
            dstRect.h = fabsf(y1 - y0);

            SDL_RenderCopyF(renderer->m_rendererSDL, textures->m_layers[i], NULL, &dstRect);
        }
    }
}

void TileMap_Render(Scene *scene)
{
    Camera *camera = Scene_GetCamera(scene);
    Renderer *renderer = Scene_GetRenderer(scene);
    Textures *textures = scene->m_textures;
    Rect view = Camera_GetView(camera);

    // Dimension du sol dans le référentiel monde
    float worldW = 10.0f;
    float worldH = 1.0f;

    // Dessine le sol
    Vec2 origin = Vec2_Set(0.0f, -1.2f);

    int tileXMin = (int)floorf((view.x - origin.x) / worldW);
    int tileXMax = (int)ceilf((view.x + view.w - origin.x) / worldW);

    for (int tileXIdx = tileXMin; tileXIdx < tileXMax; ++tileXIdx)
    {
        int tileYIdx = 0;
        Vec2 lower = Vec2_Set(tileXIdx * worldW, (tileYIdx + 1) * worldH);
        Vec2 upper = Vec2_Set((tileXIdx + 1) * worldW, tileYIdx * worldH);

        lower = Vec2_Add(lower, origin);
        upper = Vec2_Add(upper, origin);

        float x0, x1, y0, y1;
        Camera_WorldToView(camera, lower, &x0, &y0);
        Camera_WorldToView(camera, upper, &x1, &y1);

        SDL_FRect dstRect = { 0 };
        dstRect.x = x0;
        dstRect.y = y0;
        dstRect.w = fabsf(x1 - x0);
        dstRect.h = fabsf(y1 - y0);

        SDL_RenderCopyF(renderer->m_rendererSDL, textures->m_ground, NULL, &dstRect);
    }
}
