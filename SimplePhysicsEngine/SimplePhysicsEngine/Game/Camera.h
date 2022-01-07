#ifndef _CAMERA_H_
#define _CAMERA_H_

/// @file camera.h
/// @defgroup Camera
/// @{

#include "../Settings.h"
#include "../Utils/Vector.h"
#include "Ball.h"

/// @brief Structure représenant un rectangle 2D alligné sur les axes X et Y.
typedef struct Rect_s
{
    /// @brief Abscisse du sommet en bas à gauche du rectangle.
    float x;

    /// @brief Ordonnée du sommet en bas à gauche du rectangle.
    float y;

    /// @brief Largeur du rectangle.
    float w;

    /// @brief Hauteur du rectangle.
    float h;
} Rect;

/// @brief Construit un rectangle.
/// @param[in] x abscisse du sommet en bas à gauche du rectangle.
/// @param[in] y ordonnée du sommet en bas à gauche du rectangle.
/// @param[in] w largeur du rectangle.
/// @param[in] h hauteur du rectangle.
/// @return Le rectangle spécifié.
Rect Rect_Set(float x, float y, float w, float h);

/// @brief Structure représentant la caméra par laquelle est vue la scène.
typedef struct Camera_s
{
    Rect m_worldView;
    int m_width;
    int m_height;
    float m_yMin;
    float m_yMax;
    Vec2 m_velocity;
    Vec2 m_target;
} Camera;

/// @brief Crée une caméra.
/// @param[in] width la largeur en pixels de la caméra.
/// @param[in] height la hauteur en pixels de la caméra.
/// @return La caméra ou NULL en cas d'erreur.
Camera *Camera_New(int width, int height);

/// @brief Détruit une caméra préalablement allouée avec Camera_New().
/// @param[in,out] camera la caméra à détruire.
void Camera_Free(Camera *camera);

/// @brief Met à jour la caméra.
/// @param camera la caméra.
void Camera_Update(Camera *camera);

/// @brief Définit la zone du monde vue par la caméra.
/// @param[in,out] camera la caméra.
/// @param[in] worldView le rectangle exprimé dans le référentiel monde.
void Camera_SetView(Camera *camera, Rect worldView);

/// @brief Renvoie la zone du monde vue par la caméra.
/// @param[in] camera la caméra.
/// @Return Le rectangle vu par la caméra exprimé dans le référentiel monde.
Rect Camera_GetView(Camera *camera);

/// @brief Transforme des coordonnées exprimées dans le référentiel monde vers le référentiel caméra.
/// @param[in] camera la caméra.
/// @param[in] position la position d'un point dans le référentiel monde.
/// @param[out] x l'abscisse du point dans le référentiel caméra (en pixels).
/// @param[out] y l'ordonnée du point dans le référentiel caméra (en pixels).
void Camera_WorldToView(Camera *camera, Vec2 position, float *x, float *y);

/// @brief Transforme des coordonnées exprimées dans le référentiel caméra vers le référentiel monde.
/// @param[in] camera camera la caméra.
/// @param[in] x l'abscisse d'un point dans le référentiel caméra (en pixels).
/// @param[in] y l'ordonnée d'un point dans le référentiel caméra (en pixels).
/// @param[out] position la position du point dans le référentiel monde.
void Camera_ViewToWorld(Camera *camera, float x, float y, Vec2 *position);

/// @brief Déplace la caméra.
/// @param[in,out] camera la caméra.
/// @param[out] displacement le vecteur de déplacement exprimé dans le référentiel monde.
void Camera_Move(Camera *camera, Vec2 displacement);

/// @}

#endif
