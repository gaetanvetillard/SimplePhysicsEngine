#include "Ball.h"
#include "Scene.h"

Ball Ball_Set(Vec2 position)
{
    Ball ball = { 0 };

    ball.position = position;
    ball.velocity = Vec2_Set(0.f, 0.f);
    ball.mass = 0.4f;
    ball.friction = 0.5f;

    return ball;
}

int Ball_Connect(Ball *ball1, Ball *ball2, float length)
{
    if ((ball1 == ball2)
        || (ball1->springCount >= MAX_EDGES)
        || (ball2->springCount >= MAX_EDGES))
        return EXIT_FAILURE;

    ball1->springs[ball1->springCount].other = ball2;
    ball2->springs[ball2->springCount].other = ball1;
    ball1->springs[ball1->springCount].length = length;
    ball2->springs[ball2->springCount].length = length;

    ball1->springCount++;
    ball2->springCount++;

    return EXIT_SUCCESS;
}

int Ball_Deconnect(Ball *ball1, Ball *ball2)
{
    int springCount1 = ball1->springCount;
    int springCount2 = ball2->springCount;
    int exitStatus = EXIT_SUCCESS;
    int i;

    // Supprime la ball2 des connexions de la ball1
    for (i = 0; i < springCount1; ++i)
    {
        if (ball1->springs[i].other == ball2)
        {
            ball1->springs[i] = ball1->springs[springCount1 - 1];
            ball1->springCount--;
            break;
        }
    }
    if (i >= springCount1)
    {
        exitStatus = EXIT_FAILURE;
    }

    // Supprime la ball1 des connexions de la ball2
    for (i = 0; i < springCount2; ++i)
    {
        if (ball2->springs[i].other == ball1)
        {
            ball2->springs[i] = ball2->springs[springCount2 - 1];
            ball2->springCount--;
            break;
        }
    }
    if (i >= springCount2)
    {
        exitStatus = EXIT_FAILURE;
    }

    return exitStatus;
}

Vec2 Ball_GetPosition(Ball *ball)
{
    return ball->position;
}

void Ball_UpdateVelocity(Ball *ball, float timeStep)
{
    // TODO : Remplacez par votre fonction
}

void Ball_UpdatePosition(Ball *ball, float timeStep)
{
    // TODO : Remplacez par votre fonction
}

void Ball_Render(Ball *ball, Scene *scene)
{
    Camera *camera = Scene_GetCamera(scene);
    Renderer *renderer = Scene_GetRenderer(scene);
    Textures *textures = scene->m_textures;

    Vec2 lower = Vec2_Sub(ball->position, Vec2_Set(0.2f, 0.2f));
    Vec2 upper = Vec2_Add(ball->position, Vec2_Set(0.2f, 0.2f));

    float x0, y0, x1, y1;
    Camera_WorldToView(camera, lower, &x0, &y0);
    Camera_WorldToView(camera, upper, &x1, &y1);

    SDL_FRect dstRect = { 0 };
    dstRect.x = x0;
    dstRect.y = y1;
    dstRect.w = fabsf(x1 - x0);
    dstRect.h = fabsf(y1 - y0);

    SDL_RenderCopyF(renderer->m_rendererSDL, textures->m_body, NULL, &dstRect);
}

void Ball_RenderSpring(Vec2 start, Vec2 end, Scene *scene, bool active)
{
    Camera *camera = Scene_GetCamera(scene);
    Renderer *renderer = Scene_GetRenderer(scene);
    Textures *textures = scene->m_textures;
    SDL_Texture *springTexture =
        active ? textures->m_spring : textures->m_springInactive;

    float shift = 0.1f;

    Vec2 direction = Vec2_Normalize(Vec2_Sub(end, start));
    Vec2 pointL = Vec2_Add(start, Vec2_Scale(direction, shift));
    Vec2 pointR = Vec2_Sub(end, Vec2_Scale(direction, shift));
    Vec2 pointTL = Vec2_Add(pointL, Vec2_Scale(Vec2_Perp(direction), 0.1f));
    Vec2 pointC = Vec2_Scale(Vec2_Add(pointL, pointR), 0.5f);

    float xL, yL, xR, yR, xT, yT, xC, yC;
    Camera_WorldToView(camera, pointC, &xC, &yC);
    Camera_WorldToView(camera, pointL, &xL, &yL);
    Camera_WorldToView(camera, pointR, &xR, &yR);
    Camera_WorldToView(camera, pointTL, &xT, &yT);

    float length = Vec2_Length(Vec2_Set(xR - xL, yR - yL));
    float width = Vec2_Length(Vec2_Set(xT - xL, yT - yL)) * 2.0f;
    float angle = atan2f(yR - yL, xR - xL) * 180.0f / (float)M_PI;

    SDL_FRect dstRect = { 0 };
    dstRect.x = xC - width / 2.0f;
    dstRect.y = yC - length / 2.0f;
    dstRect.w = width;
    dstRect.h = length;

    SDL_RenderCopyExF(
        renderer->m_rendererSDL, springTexture, NULL, &dstRect,
        (double)angle - 90.0, NULL, 0
    );
}