#ifndef _STARS_H_
#define _STARS_H_

#include "../Settings.h"
#include "../Utils/Vector.h"

typedef struct Scene_s Scene;

/// @brief Structure repr�sentant une �toile de score
typedef struct Star_s {
	/// @brief Vecteur position de l'�toile
	Vec2 position;
} Star;



/// @brief Initialise une �toile avec sa position
/// @param[in] position le vecteur position de l'�toile.
/// @return L'�toile initialis�e.
Star Star_Set(Vec2 position);



/// @brief Dessine une �toile dans la sc�ne.
/// @param star l'�toile � dessiner.
/// @param scene la sc�ne.
void Star_Render(Star* star, Scene* scene);


/// @brief Mise a jour de l'affichage du score
/// @param scene la sc�ne
void updateScore(Scene* scene);


/// @brief Affichage du score
/// @param scene la sc�ne
void displayScore(Scene* scene);


/// @brief Cr�ation du score en texte
/// @param scene la sc�ne
void initScore(Scene* scene);

#endif
