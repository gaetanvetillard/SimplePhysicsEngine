#include "ToolsBar.h"
#include "../Game/Scene.h"

void DisplayBar(Scene* scene) {
	Renderer* renderer = Scene_GetRenderer(scene);
	Textures* textures = scene->m_textures;

	int WIDTH = renderer->m_width, HEIGHT = renderer->m_height;

	// Background
	SDL_Rect background = { WIDTH / 2 - 155, HEIGHT - 60, 310, 60 };
	SDL_SetRenderDrawColor(renderer->m_rendererSDL, 145, 134, 160, 255);
	SDL_RenderFillRect(renderer->m_rendererSDL, &background);
	

	// Outline
	SDL_Rect selected = { WIDTH / 2 - 150, HEIGHT - 55, 50, 50 };
	selected.x += scene->m_input->ballSelected * 50;
	SDL_SetRenderDrawColor(renderer->m_rendererSDL, 198, 194, 206, 255);
	SDL_RenderFillRect(renderer->m_rendererSDL, &selected);


	SDL_Texture* ballsTextures[6] = { textures->m_body, textures->m_bodyGirafe, textures->m_bodySnail, textures->m_bodySpider, textures->m_bodyPanda, textures->m_redCross };

	// Cases
	SDL_Rect barCase = { WIDTH / 2 - 95, HEIGHT - 50, 40, 40 };
	SDL_Rect ballCase = { barCase.x + 2.5, barCase.y + 2.5, barCase.w - 5, barCase.h - 5 };
	SDL_SetRenderDrawColor(renderer->m_rendererSDL, 161, 166, 182, 255);
	
	for (int i = 0; i < 6; i++) {
		barCase.x = background.x + 10 + i * 50;
		ballCase.x = barCase.x + 2.5;
		SDL_RenderFillRect(renderer->m_rendererSDL, &barCase);
		SDL_RenderCopy(renderer->m_rendererSDL, ballsTextures[i], NULL, &ballCase);
	}
}