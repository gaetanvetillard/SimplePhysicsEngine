#ifndef _BALL_H_
#define _BALL_H_

/// @file Ball.h
/// @defgroup Physics
/// @{

#include "../Settings.h"
#include "../Utils/Vector.h"

#define MAX_EDGES 10

typedef struct Scene_s Scene;
typedef struct Ball_s Ball;

typedef enum SpringFlag_e
{
    SPRING_RENDERED = 1 << 0,
} SpringFlag;

/// @brief Structure représentant un ressort entre une balle et son point d'attache.
typedef struct Spring_s
{
    int flags;

    /// @brief Pointeur vers le point d'attache.
    Ball *other;

    /// @brief Longueur du ressort au repos.
    float length;
} Spring;

/// @brief Structure représentant une balle. Elle peut être liée à d'autres balle avec des ressorts.
struct Ball_s
{
    /// @brief Vecteur position de la balle.
    Vec2 position;

    /// @brief Vecteur vitesse de la balle.
    Vec2 velocity;

    /// @brief Masse de la balle (exprimée en kg).
    float mass;

    /// @brief Coefficient de friction de la balle.
    float friction;

    /// @brief Nombre de ressorts liant la balle à d'autres balles.
    int springCount;

    /// @brief Tableau contenant les ressorts attachés à la balle.
    Spring springs[MAX_EDGES];
};

/// @brief Initialise une balle et permet de définir sa position.
/// @param[in] position le vecteur position de la balle.
/// @return La balle initialisée.
Ball Ball_Set(Vec2 position);

/// @brief Lie deux balles avec un ressort dont la longueur au repos est spécifiée.
/// @param[in,out] ball1 la première balle.
/// @param[in,out] ball2 la seconde balle.
/// @param[in] length la longueur au repos du ressort.
/// @return EXIT_SUCCESS ou EXIT_FAILURE.
int Ball_Connect(Ball *ball1, Ball *ball2, float length);

/// @brief Supprime le ressort liant deux balles.
/// @param[in,out] ball1 la première balle.
/// @param[in,out] ball2 la seconde balle.
/// @return EXIT_SUCCESS ou EXIT_FAILURE.
int Ball_Deconnect(Ball *ball1, Ball *ball2);

/// @brief Renvoie la position d'une balle dans le référentiel monde.
/// @param ball la balle.
/// @return La position de la balle dans le référentiel monde.
Vec2 Ball_GetPosition(Ball *ball);

/// @brief Met à jour la vitesse d'une balle en fonction des forces qui lui sont appliquées.
/// @param[in,out] ball la balle à mettre à jour.
/// @param[in] timeStep le pas de temps.
void Ball_UpdateVelocity(Ball *ball, float timeStep);

/// @brief Met à jour la position d'une balle en fonction de sa vitesse.
/// @param[in,out] ball la balle à mettre à jour.
/// @param[in] timeStep le pas de temps.
void Ball_UpdatePosition(Ball *ball, float timeStep);

/// @brief Dessine une balle dans la scène.
/// @param ball la balle à dessiner.
/// @param scene la scène.
void Ball_Render(Ball *ball, Scene *scene);

/// @brief Dessine un ressort entre deux points.
/// @param start position du début dans le référentiel monde.
/// @param end position de la fin dans le référentiel monde.
/// @param scene la scène.
/// @param active booléen indiquant si le ressort est actif (change la texture utilisée).
void Ball_RenderSpring(Vec2 start, Vec2 end, Scene *scene, bool active);

/// @}

#endif