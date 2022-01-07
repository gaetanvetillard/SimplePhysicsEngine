#ifndef _SCENE_H_
#define _SCENE_H_

/// @file scene.h
/// @defgroup Scene
/// @{

#include "../Settings.h"
#include "../Utils/Renderer.h"

#include "Ball.h"
#include "Camera.h"
#include "Textures.h"
#include "Input.h"

/// @brief Structure représentant le résultat d'une recherche de balle.
typedef struct BallQuery_s
{
    /// @brief Pointeur vers la balle.
    Ball *ball;

    /// @brief Distance entre la balle et la position donnée.
    float distance;
} BallQuery;

#define MAX_QUERY_COUNT 4

/// @brief Structure représentant la scène de la simulation.
/// Elle contient la caméra par laquelle la scène est vue ainsi que toutes les balles.
typedef struct Scene_s
{
    /// @brief Moteur de rendu.
    Renderer *m_renderer;

    Input *m_input;

    /// @brief Caméra par laquelle la scène est vue.
    Camera *m_camera;

    Textures *m_textures;

    /// @brief Tableau contenant les balles présentes dans la scène.
    Ball *m_balls;

    /// @brief Nombre de balles dans la scène.
    int m_ballCount;

    /// @brief Nombre maximal de balles avant d'effectuer une réallocation mémoire.
    int m_ballCapacity;

    /// @brief Position de la souris dans le référentiel monde.
    Vec2 m_mousePos;

    /// @brief Dernières requêtes effectuées sur les balles.
    BallQuery m_queries[MAX_QUERY_COUNT];

    /// @brief Nombre de requêtes valides.
    int m_validCount;

    /// @brief Pas de temps fixe utilisé pour la physique.
    float m_timeStep;

    /// @brief Accumulateur pour le pas de temps fixe.
    float m_accu;
} Scene;

/// @brief Construit une scène.
/// @param[in] renderer le moteur de rendu.
/// @return La scène créée. Renvoie NULL en cas d'erreur.
Scene *Scene_New(Renderer *renderer);

/// @brief Détruit une scène précédemment construite avec Scene_New().
/// Le pointeur vers la scène doit être affecté à NULL après l'appel à cette fonction.
/// @param[in,out] scene la scène à détruire.
void Scene_Free(Scene *scene);

/// @brief Renvoie le moteur de rendu associé à la scène.
/// @param[in] scene la scène.
/// @return Le moteur de rendu associé à la scène.
Renderer *Scene_GetRenderer(Scene *scene);

/// @brief Renvoie la caméra par laquelle la scène est vue.
/// @param[in] scene la scène.
/// @return La caméra associée à la scène.
Camera *Scene_GetCamera(Scene *scene);

Input *Scene_GetInput(Scene *scene);

/// @brief Renvoie la position de la souris dans le référentiel monde.
/// @param scene la scène.
/// @return La position de la souris dans le référentiel monde.
Vec2 Scene_GetMousePosition(Scene *scene);

/// @brief Ajoute une balle à la scène.
/// @param[in,out] scene la scène.
/// @param[in] position la position de la nouvelle balle.
/// @return EXIT_SUCCESS ou EXIT_FAILURE.
Ball *Scene_CreateBall(Scene *scene, Vec2 position);

/// @brief Supprime une balle de la scène.
/// Les adresses des balles sont invalidées après l'appel à cette fonction.
/// @param[in,out] scene la scène.
/// @param[in,out] ball pointeur vers la balle à supprimer.
void Scene_RemoveBall(Scene *scene, Ball *ball);

/// @brief Renvoie le nombre de balles présentes dans la scène.
/// @param[in] scene la scène.
/// @return Le nombre de balles présentes dans la scène.
int Scene_GetBallCount(Scene *scene);

/// @brief Renvoie le tableau contenant les balles présentes dans la scène.
/// La taille de ce tableau s'obtient avec la fonction Scene_GetBallCount().
/// @param[in] scene la scène.
/// @return Le tableau contenant les balles présentes dans la scène.
Ball *Scene_GetBalls(Scene *scene);

/// @brief Met à jour les positions des balles présentes dans la scène.
/// Cette fonction correspond au moteur physique.
/// @param[in,out] scene la scène.
void Scene_Update(Scene *scene);

/// @brief Calcule le rendu de la scène vue par sa caméra.
/// @param[in] scene la scène à rendre.
void Scene_Render(Scene *scene);

//-------------------------------------------------------------------------------------------------
// Fonctions de recherche

/// @brief Recherche dans une scène la balle la plus proche d'une position donnée.
/// @param[in] scene la scène dans laquelle faire la recherche.
/// @param[in] position la position autour de laquelle faire la recherche.
/// @return Une structure BallQuery contenant un pointeur vers la balle la plus proche
/// ainsi que sa distance avec la position spécifiée.
/// Si la scène ne contient aucune balle, le pointeur vers la balle vaut NULL.
BallQuery Scene_GetNearestBall(Scene *scene, Vec2 position);

/// @brief Recherche dans une scène les balles les plus proches d'une position donnée.
/// @param[in] scene la scène dans laquelle faire la recherche.
/// @param[in] position la position autour de laquelle faire la recherche.
/// @param[out] queries tableau dans lequel vont être écrit les résultats.
/// Il doit contenir au moins queryCount cases.
/// @param[in] queryCount le nombre de balles à rechercher.
/// @return EXIT_SUCCESS ou EXIT_FAILURE. Le resultat de la recherche est écrit dans le tableau queries.
int Scene_GetNearestBalls(Scene *scene, Vec2 position, BallQuery *queries, int queryCount);

#endif
