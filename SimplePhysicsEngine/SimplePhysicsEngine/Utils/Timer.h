#ifndef _TIMER_H_
#define _TIMER_H_

/// @file timer.h
/// @defgroup Timer
/// @{

#include "../Settings.h"

/// @brief Structure représentant un chronomètre.
typedef struct Timer_s
{
    /// @brief Temps de départ.
    float m_startTime;

    /// @brief Temps du dernier appel à Timer_Update().
    float m_currentTime;

    /// @brief Temps de l'avant dernier appel à Timer_Update().
    float m_previousTime;

    /// @brief Ecart entre les deux derniers appels à Timer_Update().
    float m_delta;
} Timer;

/// @brief Temps global pour le jeu.
extern Timer *g_time;

/// @brief Crée un nouveau timer.
/// @return Le timer créé.
Timer* Timer_New();

/// @brief Détruit un timer préalablement alloué avec Timer_New().
/// @param[in,out] timer le timer à détruire.
void Timer_Free(Timer* timer);

/// @brief Lance le timer.
/// @param[in,out] timer le timer.
void Timer_Start(Timer* timer);

/// @brief Met à jour le timer en fonction du temps actuel.
/// @param[in,out] timer le timer.
void Timer_Update(Timer* timer);

/// @brief Renvoie l'écart de temps (en secondes) entre les deux derniers appels à la fonction
/// Timer_Update().
/// @param[in] timer le timer.
/// @return L'écart de temps entre les deux dernières mises à jour.
float Timer_GetDelta(Timer *timer);

/// @brief Renvoie l'écart de temps (en secondes) entre le lancement du timer avec la fonction
/// Timer_Start() et le dernier appel à la fonction Timer_Update().
/// @param[in] timer le timer.
/// @return Le nombre de secondes écoulées depuis le lancement du timer et la dernière mise à jour.
float Timer_GetElapsed(Timer *timer);

#endif