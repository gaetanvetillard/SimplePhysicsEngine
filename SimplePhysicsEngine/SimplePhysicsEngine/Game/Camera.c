#include "Camera.h"
#include "../Utils/Tools.h"
#include "../Utils/Timer.h"

Rect Rect_Set(float x, float y, float w, float h)
{
    Rect rect = { .x = x, .y = y, .w = w, .h = h };
    return rect;
}

Camera *Camera_New(int width, int height)
{
    Camera *camera = NULL;

    camera = (Camera *)calloc(1, sizeof(Camera));
    if (!camera) goto ERROR_LABEL;

    float worldW = 19.0f;
    // Calcule la hauteur pour un ratio 16/9
    float worldH = 9.0f / 16.0f * worldW;

    camera->m_width = width;
    camera->m_height = height;
    camera->m_worldView = Rect_Set(-0.5f * worldW, -1.2f, worldW, worldH);
    camera->m_target = Vec2_Set(-0.5f * worldW, -1.2f);

    camera->m_yMin = -1.2f;
    camera->m_yMax = 20.0f;

    return camera;

ERROR_LABEL:
    printf("ERROR - Camera_New()\n");
    assert(false);
    Camera_Free(camera);
    return NULL;
}

void Camera_Free(Camera *camera)
{
    if (!camera) return;

    memset(camera, 0, sizeof(Camera));
    free(camera);
}

void Camera_Update(Camera *camera)
{
    Vec2 position = Vec2_Set(camera->m_worldView.x, camera->m_worldView.y);
    Vec2 newPos = { 0 };
    Vec2 target = camera->m_target;
    newPos.x = Float_SmoothDamp(
        position.x, target.x, &(camera->m_velocity.x),
        0.10f, 100.0f, Timer_GetDelta(g_time)
    );
    newPos.y = Float_SmoothDamp(
        position.y, target.y, &(camera->m_velocity.y),
        0.10f, 100.0f, Timer_GetDelta(g_time)
    );

    camera->m_worldView.x = newPos.x;
    camera->m_worldView.y = newPos.y;
}

void Camera_CheckBounds(Camera *camera)
{
    Rect *worldView = &camera->m_worldView;
    Vec2 target = camera->m_target;

    worldView->y = fmaxf(worldView->y, camera->m_yMin);
    worldView->y = fminf(worldView->y, camera->m_yMax - worldView->h);

    target.y = fmaxf(target.y, camera->m_yMin);
    target.y = fminf(target.y, camera->m_yMax - worldView->h);

    camera->m_target = target;
}

void Camera_WorldToView(Camera *camera, Vec2 position, float *x, float *y)
{
    float xScale = (float)camera->m_width  / camera->m_worldView.w;
    float yScale = (float)camera->m_height / camera->m_worldView.h;
    *x = (position.x - camera->m_worldView.x) * xScale;
    *y = (position.y - camera->m_worldView.y) * yScale;
    *y = camera->m_height - *y;
}

void Camera_ViewToWorld(Camera *camera, float x, float y, Vec2 *position)
{
    y = camera->m_height - y;
    float ratioX = (float)x / (float)camera->m_width;
    float ratioY = (float)y / (float)camera->m_height;
    position->x = camera->m_worldView.x + ratioX * (camera->m_worldView.w);
    position->y = camera->m_worldView.y + ratioY * (camera->m_worldView.h);
}

void Camera_Move(Camera *camera, Vec2 displacement)
{
    camera->m_target = Vec2_Add(camera->m_target, displacement);

    Camera_CheckBounds(camera);
}

void Camera_SetView(Camera *camera, Rect worldView)
{
    camera->m_worldView = worldView;

    Camera_CheckBounds(camera);
}

Rect Camera_GetView(Camera *camera)
{
    return camera->m_worldView;
}
