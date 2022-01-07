#include "Menu.h"
#include "../Game/Scene.h"

void DisplayMenu(Scene* scene) {
	Renderer* renderer = Scene_GetRenderer(scene);
	Renderer_Fill(renderer, Color_Set(0, 0, 0, 140));


	SDL_Color white = { 255, 255, 255, 255 };

	// On crée les surfaces
	SDL_Surface* title_ = TTF_RenderText_Blended(scene->titleFont, "Pause", white);
	SDL_Surface* returnButton = TTF_RenderText_Blended(scene->buttonFont, "Reprendre", white);
	SDL_Surface* resetButton = TTF_RenderText_Blended(scene->buttonFont, "Nouvelle partie", white);
	SDL_Surface* exitButton = TTF_RenderText_Blended(scene->buttonFont, "Quitter le jeu", white);
	

	// On crée les textures
	SDL_Texture* titleTexture = SDL_CreateTextureFromSurface(renderer->m_rendererSDL, title_);
	SDL_Texture* returnTexture = SDL_CreateTextureFromSurface(renderer->m_rendererSDL, returnButton);
	SDL_Surface* resetTexture = SDL_CreateTextureFromSurface(renderer->m_rendererSDL, resetButton);
	SDL_Texture* exitTexture = SDL_CreateTextureFromSurface(renderer->m_rendererSDL, exitButton);


	SDL_Rect position;

	// Titre
	SDL_QueryTexture(titleTexture, NULL, NULL, &position.w, &position.h);
	position.y = 100;
	position.x = renderer->m_width / 2 - position.w / 2;

	SDL_RenderCopy(renderer->m_rendererSDL, titleTexture, NULL, &position);



	// Bouton retour au jeu
	SDL_QueryTexture(returnTexture, NULL, NULL, &position.w, &position.h);
	position.y = 250;
	position.x = renderer->m_width / 2 - position.w / 2;

	SDL_Rect returnButtonBg = { renderer->m_width / 2 - 350 / 2, position.y - position.h / 2, 350, position.h * 1.8 };
	SDL_SetRenderDrawColor(renderer->m_rendererSDL, 204, 153, 255, 200);
	SDL_RenderFillRect(renderer->m_rendererSDL, &returnButtonBg);

	SDL_RenderCopy(renderer->m_rendererSDL, returnTexture, NULL, &position);



	// Bouton nouvelle partie
	SDL_QueryTexture(resetTexture, NULL, NULL, &position.w, &position.h);
	position.y = 350;
	position.x = renderer->m_width / 2 - position.w / 2;

	SDL_Rect resetButtonBg = { renderer->m_width / 2 - 350 / 2, position.y - position.h / 2, 350, position.h * 1.8 };
	SDL_SetRenderDrawColor(renderer->m_rendererSDL, 204, 153, 255, 200);
	SDL_RenderFillRect(renderer->m_rendererSDL, &resetButtonBg);

	SDL_RenderCopy(renderer->m_rendererSDL, resetTexture, NULL, &position);



	// Bouton quitter
	SDL_QueryTexture(exitTexture, NULL, NULL, &position.w, &position.h);
	position.y = 450;
	position.x = renderer->m_width / 2 - position.w / 2;
	
	SDL_Rect exitButtonBg = { renderer->m_width / 2 - 350 / 2, position.y - position.h / 2, 350, position.h * 1.8 };
	SDL_SetRenderDrawColor(renderer->m_rendererSDL, 255, 255, 255, 125);
	SDL_RenderFillRect(renderer->m_rendererSDL, &exitButtonBg);

	SDL_RenderCopy(renderer->m_rendererSDL, exitTexture, NULL, &position);


	// On libère les surfaces
	SDL_FreeSurface(title_);
	SDL_FreeSurface(returnButton);
	SDL_FreeSurface(resetButton);
	SDL_FreeSurface(exitButton);

	// On met le renderer à jour
	Renderer_Update(renderer);


	// On attend une entrée utilisateur
	Input* input = scene->m_input;
	while (1) {
		Input_Update(input);
		
		if (!input->menuOpened || input->quitPressed) {
			break;
		}

		if (input->mouseLPressed) {
			if (input->mouseX >= returnButtonBg.x && input->mouseX <= returnButtonBg.x + returnButtonBg.w 
				&& input->mouseY >= returnButtonBg.y && input->mouseY <= returnButtonBg.y + returnButtonBg.h) 
			{
				input->menuOpened = false;
				break;
			}

			else if (input->mouseX >= exitButtonBg.x && input->mouseX <= exitButtonBg.x + exitButtonBg.w 
				&& input->mouseY >= exitButtonBg.y && input->mouseY <= exitButtonBg.y + exitButtonBg.h) 
			{
				input->quitPressed = true;
				break;
			}

			else if (input->mouseX >= resetButtonBg.x && input->mouseX <= resetButtonBg.x + resetButtonBg.w
				&& input->mouseY >= resetButtonBg.y && input->mouseY <= resetButtonBg.y + resetButtonBg.h)
			{
				input->restartPressed = true;
				break;
			}
		}
	}
}