#include "Stars.h"
#include "Scene.h"


Star Star_Set(Vec2 position) {
	Star star = { 0 };
	star.position = position;

	return star;
}



void Star_Render(Star* star, Scene* scene) {
	Camera* camera = Scene_GetCamera(scene);
	Renderer* renderer = Scene_GetRenderer(scene);
	Textures* textures = scene->m_textures;

    Vec2 lower = Vec2_Sub(star->position, Vec2_Set(0.2f, 0.2f));
    Vec2 upper = Vec2_Add(star->position, Vec2_Set(0.2f, 0.2f));

    float x0, y0, x1, y1;
    Camera_WorldToView(camera, lower, &x0, &y0);
    Camera_WorldToView(camera, upper, &x1, &y1);

    SDL_FRect dstRect = { 0 };
    dstRect.x = x0;
    dstRect.y = y1;
    dstRect.w = fabsf(x1 - x0);
    dstRect.h = fabsf(y1 - y0);

    SDL_RenderCopyF(renderer->m_rendererSDL, textures->m_star, NULL, &dstRect);
}


void updateScore(Scene* scene) {
    // On met à jour la surface et la texture du score
    Renderer* renderer = Scene_GetRenderer(scene);
    SDL_Color white = { 255, 255, 255, 255 };

    sprintf(scene->score.scoreText, "Score : %d", scene->score.score);
    scene->score.surface = TTF_RenderText_Blended(scene->scoreFont, scene->score.scoreText, white);

    SDL_DestroyTexture(scene->score.texture);
    scene->score.texture = SDL_CreateTextureFromSurface(renderer->m_rendererSDL, scene->score.surface);

    SDL_QueryTexture(scene->score.texture, NULL, NULL, &scene->score.position.w, &scene->score.position.h);
}


void displayScore(Scene* scene) {
    // On affiche la texture du score
    SDL_RenderCopy(scene->m_renderer->m_rendererSDL, scene->score.texture, NULL, &scene->score.position);
}


void initScore(Scene* scene) {
    Renderer* renderer = Scene_GetRenderer(scene);
    SDL_Color white = { 255, 255, 255, 255 };

    // On initialise le score à 0
    scene->score.score = 0;
    scene->score.scoreHasChanged = 0;

    // on met à jour le texte avec le bon score
    sprintf(scene->score.scoreText, "Score : %d", scene->score.score);

    // on crée la surface
    scene->score.surface = TTF_RenderText_Blended(scene->scoreFont, scene->score.scoreText, white);
    
    // on crée la texture
    scene->score.texture = SDL_CreateTextureFromSurface(renderer->m_rendererSDL, scene->score.surface);

    // on définit la position
    SDL_QueryTexture(scene->score.texture, NULL, NULL, &scene->score.position.w, &scene->score.position.h);
    scene->score.position.x = 20;
    scene->score.position.y = renderer->m_height - 20 - scene->score.position.h;

    SDL_RenderCopy(renderer->m_rendererSDL, scene->score.texture, NULL, &scene->score.position);
}