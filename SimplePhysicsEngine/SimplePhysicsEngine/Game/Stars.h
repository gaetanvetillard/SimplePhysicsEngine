#ifndef _STARS_H_
#define _STARS_H_

#include "../Settings.h"
#include "../Utils/Vector.h"

typedef struct Scene_s Scene;

/// @brief Structure représentant une étoile de score
typedef struct Star_s {
	/// @brief Vecteur position de l'étoile
	Vec2 position;
} Star;



/// @brief Initialise une étoile avec sa position
/// @param[in] position le vecteur position de l'étoile.
/// @return L'étoile initialisée.
Star Star_Set(Vec2 position);



/// @brief Dessine une étoile dans la scène.
/// @param star l'étoile à dessiner.
/// @param scene la scène.
void Star_Render(Star* star, Scene* scene);


/// @brief Mise a jour de l'affichage du score
/// @param scene la scène
void updateScore(Scene* scene);


/// @brief Affichage du score
/// @param scene la scène
void displayScore(Scene* scene);


/// @brief Création du score en texte
/// @param scene la scène
void initScore(Scene* scene);

#endif
