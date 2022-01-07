#include "Timer.h"

Timer *g_time = NULL;

Timer* Timer_New()
{
    Timer* timer = NULL;

    timer = (Timer*)calloc(1, sizeof(Timer));
    if (!timer)
    {
        printf("ERROR - Timer_New()\n");
        assert(false);
        return NULL;
    }

    timer->m_startTime = -1.f;
    timer->m_currentTime = 0.f;
    timer->m_previousTime = timer->m_currentTime;
    timer->m_delta = 0.f;

    return timer;
}

void Timer_Free(Timer* timer)
{
    if (!timer) return;

    memset(timer, 0, sizeof(Timer));
    free(timer);
}

void Timer_Start(Timer* timer)
{
    if (!timer)
        return;

    timer->m_startTime = SDL_GetTicks() / 1000.f;
    timer->m_currentTime = 0.f;
    timer->m_previousTime = 0.f;
    timer->m_delta = 0.f;
}

void Timer_Update(Timer* timer)
{
    timer->m_previousTime = timer->m_currentTime;
    timer->m_currentTime = SDL_GetTicks() / 1000.f - timer->m_startTime;
    timer->m_delta = timer->m_currentTime - timer->m_previousTime;
}

float Timer_GetDelta(Timer *timer)
{
    return timer->m_delta;
}

float Timer_GetElapsed(Timer *timer)
{
    return timer->m_currentTime - timer->m_startTime;
}