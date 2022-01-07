#ifndef _VECTOR_H_
#define _VECTOR_H_

/// @file vector.h
/// @defgroup Vector
/// @{

#include "../Settings.h"

/// @brief Structure représentant un vecteur 2D dont les composantes sont de type float.
typedef struct Vec2_s
{
    /// @brief Abscisse du vecteur.
    float x;

    /// @brief Ordonnée du vecteur.
    float y;
} Vec2;

/// @brief Construit un vecteur à partir de ses composantes.
/// @param[in] x la composante x.
/// @param[in] y la composante y.
/// @return Le vecteur ayant les composantes données.
Vec2 Vec2_Set(float x, float y);

/// @brief Additionne deux vecteurs.
/// @param[in] v1 le premier vecteur.
/// @param[in] v2 le second vecteur.
/// @return La somme de v1 et v2.
Vec2 Vec2_Add(Vec2 v1, Vec2 v2);

/// @brief Soustrait deux vecteurs.
/// @param[in] v1 le premier vecteur.
/// @param[in] v2 le second vecteur.
/// @return La différence de v1 par v2.
Vec2 Vec2_Sub(Vec2 v1, Vec2 v2);

/// @brief Multiplie un vecteur par un scalaire.
/// @param[in] v le vecteur.
/// @param[in] s le scalaire.
/// @return Le produit de s et v.
Vec2 Vec2_Scale(Vec2 v, float s);

/// @brief Calcule la longueur (norme euclidienne) d'un vecteur.
/// @param[in] v le vecteur.
/// @return La norme euclidienne de v.
float Vec2_Length(Vec2 v);

/// @brief Normalise un vecteur.
/// @param[in] v le vecteur.
/// @return Le vecteur unitaire de même direction.
Vec2 Vec2_Normalize(Vec2 v);

/// @brief Renvoie la distance entre deux points.
/// @param[in] v1 les coordonnées du premier point.
/// @param[in] v2 les coordonnées du second point.
/// @return La distance séparant les deux points.
float Vec2_Distance(Vec2 v1, Vec2 v2);

/// @brief Renvoie le vecteur orthogonal à un vecteur obtenu
/// par rotation de 90 degrés dans le sens trigonométrique.
/// @param[in] v le vecteur.
/// @return Le vecteur orthogonal à v dans le sens direct.
Vec2 Vec2_Perp(Vec2 v);

#endif