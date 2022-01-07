#ifndef _RENDERER_H_
#define _RENDERER_H_

/// @file renderer.h
/// @defgroup Renderer
/// @{

#include "../Settings.h"

/// @brief Structure représentant la moteur de rendu.
typedef struct Renderer_s
{
    /// @brief Le moteur de rendu SDL.
    SDL_Renderer *m_rendererSDL;

    /// @brief La largeur en pixels de l'image rendue.
    int m_width;

    /// @brief La hauteur en pixels de l'image rendue.
    int m_height;
} Renderer;

/// @brief Structure représentant une couleur au format RGBA.
typedef struct Color_s
{
    /// @brief L'intensité de la composante rouge entre 0 et 255.
    uint8_t r;

    /// @brief L'intensité de la composante verte entre 0 et 255.
    uint8_t g;

    /// @brief L'intensité de la composante bleue entre 0 et 255.
    uint8_t b;

    /// @brief La composante alpha (transparence) de la couleur.
    /// La couleur est parfaitement transparante quand elle vaut 0 et elle est opaque quand elle vaut 255.
    uint8_t a;
} Color;

/// @brief Construit une couleur à partir de ses composantes [R,V,B,A] chacune entre 0 et 255.
/// @param[in] r l'intensité du rouge.
/// @param[in] g l'intensité du vert.
/// @param[in] b l'intensité du bleu.
/// @param[in] a la composante alpha (transparence) de la couleur.
/// La couleur est parfaitement transparante quand elle vaut 0 et elle est opaque quand elle vaut 255.
/// @return La couleur spécifiée.
Color Color_Set(int r, int g, int b, int a);

/// @brief Met à jour le moteur de rendu.
/// Cette fonction permet de d'afficher à l'écran la dernière image rendue.
/// @param[in,out] renderer le moteur de rendu.
void Renderer_Update(Renderer* renderer);

/// @brief Efface le rendu précédent. Le rendu devient entièrement noir.
/// @param[in,out] renderer le moteur de rendu.
void Renderer_Clear(Renderer* renderer);

/// @brief Remplit le rendu avec une couleur donnée.
/// @param[in,out] renderer le moteur de rendu.
/// @param[in] color la couleur de remplissage.
void Renderer_Fill(Renderer* renderer, Color color);

/// @brief Renvoie la largeur du moteur de rendu.
/// @param[in,out] renderer le moteur de rendu.
/// @return La largeur du moteur de rendu.
int Renderer_GetWidth(Renderer *renderer);

/// @brief Renvoie la hauteur du moteur de rendu.
/// @param[in,out] renderer le moteur de rendu.
/// @return La hauteur du moteur de rendu.
int Renderer_GetHeight(Renderer *renderer);

#endif
