#include "Scene.h"
#include "Ball.h"
#include "Camera.h"
#include "Background.h"
#include "../Utils/Timer.h"
#include "../Utils/Menu.h"
#include "ToolsBar.h"
#include "../Settings.h"

int Scene_DoubleCapacity(Scene *scene);

Scene *Scene_New(Renderer *renderer)
{
    Scene *scene = NULL;
    int capacity = 1 << 10;

    int width  = Renderer_GetWidth(renderer);
    int height = Renderer_GetHeight(renderer);

    scene = (Scene *)calloc(1, sizeof(Scene));
    if (!scene) goto ERROR_LABEL;

    // Chargement des fonts
    scene->titleFont = TTF_OpenFont("../Fonts/Calibri.ttf", 56);
    if (!scene->titleFont) goto ERROR_LABEL;

    scene->buttonFont = TTF_OpenFont("../Fonts/Calibri.ttf", 42);
    if (!scene->buttonFont) goto ERROR_LABEL;

    scene->scoreFont = TTF_OpenFont("../Fonts/Calibri.ttf", 36);
    if (!scene->scoreFont) goto ERROR_LABEL;


    scene->m_textures = Textures_New(renderer);
    if (!scene->m_textures) goto ERROR_LABEL;

    scene->m_camera = Camera_New(width, height);
    if (!scene->m_camera) goto ERROR_LABEL;

    scene->m_input = Input_New();
    if (!scene->m_input) goto ERROR_LABEL;

    scene->m_balls = (Ball *)calloc(capacity, sizeof(Ball));
    if (!scene->m_balls) goto ERROR_LABEL;

    // Initialisation des étoiles
    scene->m_starsCount = 0;
    scene->m_stars = (Star*)calloc(100, sizeof(Star));
    if (!scene->m_stars) goto ERROR_LABEL;
  
    scene->m_renderer = renderer;
    scene->m_ballCount = 0;
    scene->m_ballCapacity = capacity;
    scene->m_timeStep = 1.0f / 100.f;

    // Création d'une scène minimale avec trois balles reliées
    Ball *ball1 = Scene_CreateBall(scene, Vec2_Set(-0.75f, 0.0f), scene->m_input->ballSelected);
    Ball *ball2 = Scene_CreateBall(scene, Vec2_Set(+0.75f, 0.0f), scene->m_input->ballSelected);
    Ball *ball3 = Scene_CreateBall(scene, Vec2_Set(0.0f, 1.299f), scene->m_input->ballSelected);
    Ball_Connect(ball1, ball2, 1.5f, 0);
    Ball_Connect(ball1, ball3, 1.5f, 0);
    Ball_Connect(ball2, ball3, 1.5f, 0);


    // Créations des étoiles avec des position aléatoires entre x [-50:50] et y [5:20]
    // et initialisation du texte de score.
    initScore(scene);

    for (int i = 0; i < 100; i++) {
        float x = rand() % 101 - 50;
        float y = rand() % 16 + 5;
        Scene_CreateStar(scene, Vec2_Set(x, y));
    }
    

    return scene;

ERROR_LABEL:
    printf("ERROR - Scene_New()\n");
    assert(false);
    Scene_Free(scene);
    return NULL;
}

void Scene_Free(Scene *scene)
{
    if (!scene) return;

    Camera_Free(scene->m_camera);
    Input_Free(scene->m_input);
    Textures_Free(scene->m_textures);

    // On libère les fonts
    TTF_CloseFont(scene->buttonFont);
    TTF_CloseFont(scene->titleFont);
    TTF_CloseFont(scene->scoreFont);

    // On libère la surface et texture du score
    SDL_FreeSurface(scene->score.surface);
    SDL_DestroyTexture(scene->score.texture);

    if (scene->m_balls)
    {
        free(scene->m_balls);
    }

    if (scene->m_stars) {
        free(scene->m_stars);
    }

    memset(scene, 0, sizeof(Scene));
    free(scene);
}

Renderer *Scene_GetRenderer(Scene *scene)
{
    return scene->m_renderer;
}

Camera *Scene_GetCamera(Scene *scene)
{
    return scene->m_camera;
}

Input *Scene_GetInput(Scene *scene)
{
    return scene->m_input;
}

Vec2 Scene_GetMousePosition(Scene *scene)
{
    return scene->m_mousePos;
}

int Scene_DoubleCapacity(Scene *scene)
{
    Ball *newBalls = NULL;
    int newCapacity = scene->m_ballCapacity << 1;

    newBalls = (Ball *)realloc(scene->m_balls, newCapacity * sizeof(Ball));
    if (!newBalls) goto ERROR_LABEL;

    scene->m_balls = newBalls;
    scene->m_ballCapacity = newCapacity;

    return EXIT_SUCCESS;

ERROR_LABEL:
    printf("ERROR - Scene_DoubleCapacity()\n");
    return EXIT_FAILURE;
}

Ball *Scene_CreateBall(Scene *scene, Vec2 position, int type)
{
    if (scene->m_ballCount >= scene->m_ballCapacity)
    {
        int exitStatus = Scene_DoubleCapacity(scene);
        if (exitStatus == EXIT_FAILURE) goto ERROR_LABEL;
    }

    Ball *ball = &scene->m_balls[scene->m_ballCount];
    scene->m_ballCount++;

    *ball = Ball_Set(position, type);

    return ball;

ERROR_LABEL:
    printf("ERROR - Scene_CreateBall()\n");
    return NULL;
}

Star* Scene_CreateStar(Scene* scene, Vec2 position)
{
    Star* star = &scene->m_stars[scene->m_starsCount];
    scene->m_starsCount++;

    *star = Star_Set(position);

    return star;
}

void Scene_RemoveStar(Scene* scene, Star* star) {
    int starsCount = scene->m_starsCount;
    Star* stars = scene->m_stars;
    int index = (int)(star - stars);

    if (index < 0 || index >= starsCount)
        return;

    // on récupère la dernière étoile
    Star* lastStar = &stars[starsCount - 1];
    if (star != lastStar) {
        // on échange l'étoile à supprimer avec la dernière étoile
        *star = *lastStar;
    }

    // on rajoute une étoile aléatoirement à la place de la dernière étoile
    lastStar = Scene_CreateStar(scene, Vec2_Set(rand() % 101 - 50, rand() % 16 + 5));
}

void Scene_RemoveBall(Scene *scene, Ball *ball)
{
    int ballCount = Scene_GetBallCount(scene);
    Ball *balls = Scene_GetBalls(scene);
    int index = (int)(ball - balls);
    int springCount = 0;

    if (index < 0 || index >= ballCount)
        return;

    // Supprime les ressorts liés à la balle
    springCount = ball->springCount;
    for (int i = 0; i < springCount; ++i)
    {
        Ball_Deconnect(ball, ball->springs[i].other);
    }

    Ball *lastBall = &balls[ballCount - 1];
    if (ball != lastBall)
    {
        // Copie la dernière balle à la position de la balle à supprimer
        *ball = *lastBall;

        // Met à jour ses ressorts
        ball->springCount = 0;
        springCount = lastBall->springCount;
        for (int i = 0; i < springCount; ++i)
        {
            Ball *other = lastBall->springs[i].other;
            float length = lastBall->springs[i].length;
            Ball_Deconnect(lastBall, other);
            Ball_Connect(ball, other, length, 0);
        }
    }

    // Supprime la dernière balle
    scene->m_ballCount--;
}

int Scene_GetBallCount(Scene *scene)
{
    return scene->m_ballCount;
}

Ball *Scene_GetBalls(Scene *scene)
{
    return scene->m_balls;
}

BallQuery Scene_GetNearestBall(Scene *scene, Vec2 position)
{
    int ballCount = Scene_GetBallCount(scene);
    Ball *balls = Scene_GetBalls(scene);
    BallQuery query = { 0 };


    // on initialise query avec la balle et la distance
    // seulement si il y a plus d'une balle sur la scene
    if (ballCount > 0) {
        query.ball = &balls[0];
        query.distance = Vec2_Distance(balls[0].position, position);
    }


    // pour chaque balle jusqu'à ballCount
    for (int i = 1; i < ballCount; i++) {
        float distance = Vec2_Distance(balls[i].position, position);
        if (distance < query.distance || i == 0) {
            query.distance = distance;
            query.ball = &balls[i];
        }
    }

    // si la distance la plus proche est supérieure à 1 alors return ball null
    if (query.distance >= 1.0f)
        query.ball = NULL;
    
    return query;
}

int Scene_GetNearestBalls(Scene *scene, Vec2 position, BallQuery *queries, int queryCount)
{
    int ballCount = Scene_GetBallCount(scene);
    Ball *balls = Scene_GetBalls(scene);


    int selectedBallType = scene->m_input->ballSelected;
    float maxLength = 1.5f;
    // Balle girafe
    if (selectedBallType == 1) maxLength = 3.0f;
    // Balle escargot
    else if (selectedBallType == 2) maxLength = 1.0f;

    // on génère un tableau avec MAX_QUERY_COUNT cases pour stocker les indexs
    // des balles valides et on initialise chaque case à -1
    int minIndexes[MAX_QUERY_COUNT];
    // initialisation du tableau
    for (int i = 0; i < MAX_QUERY_COUNT; i++)
        minIndexes[i] = -1;
    
    // on initialise le tableau queries avec des query null
    for (int i = 0; i < MAX_QUERY_COUNT; i++) {
        BallQuery query = { 0 };
        queries[i] = query;
    }


    int counter = 0;
    for (int i = 0; i < queryCount; i++) {
        // si il reste des balles dans la scène qui n'ont pas
        // été vérifiées
        if (ballCount > i) {
            float minDistance = INFINITY;
            BallQuery query;
            // pour chaque balle si l'index de la balle n'est pas dans minIndexes

            // variable hasChanged : 1 si oui pour mettre à jour le counter
            // counter qui sera la valeur de scene->m_validCount
            int hasChanged = 0;

            // pour chaque balle
            for (int j = 0; j < ballCount; j++) {
                // on regarde si l'index de la balle est déjà
                // dans le tableau minIndexes[]
                int isOk = 1;
                for (int k = 0; k < MAX_QUERY_COUNT; k++) {
                    if (minIndexes[k] == j)
                        isOk = 0;
                }

                // s'il n'est pas encore dans le tableau on vérifie la condition
                if (isOk) {
                    float distance = Vec2_Distance(position, balls[j].position);

                    if (distance < minDistance && distance > 0.0f && distance <= maxLength * 2
                        && balls[j].springCount < MAX_EDGES
                        ) {
                        minDistance = distance;
                        minIndexes[i] = j;
                        query.ball = &balls[j];
                        query.distance = distance;
                        queries[i] = query;
                        hasChanged = 1;
                    }
                }
            }
               
            if (hasChanged) counter++;
        }

        // sinon on break
        else {
            break;
        }
    }



    return counter;
}

void Scene_CheckStarHit(Scene* scene) {
    Star* stars = scene->m_stars;
    Ball* balls = scene->m_balls;
    int  starsCount = scene->m_starsCount;
    int ballsCount = scene->m_ballCount;

    // pour chaque étoile
    for (int i = 0; i < starsCount; i++) {
        Star* star = &stars[i];
        
        // pour chaque balle on regarde si la balle est proche de l'étoile
        // si la distance est < à 0.3f, on considère que la balle a touché
        // l'étoile
        for (int j = 0; j < ballsCount; j++) {
            Ball* ball = &balls[j];

            if (Vec2_Distance(ball->position, star->position) < 0.3f && ball->springCount > 1) {
                Scene_RemoveStar(scene, star);
                scene->score.score++;
                scene->score.scoreHasChanged = 1;
                break;
            }
        }
    }
}

void Scene_FixedUpdate(Scene *scene, float timeStep)
{
    int ballCount = Scene_GetBallCount(scene);
    Ball *balls = Scene_GetBalls(scene);

    for (int i = 0; i < ballCount; i++)
    {
        Ball_UpdateVelocity(&balls[i], timeStep);
    }
    for (int i = 0; i < ballCount; i++)
    {
        Ball_UpdatePosition(&balls[i], timeStep);
    }
}

void Scene_UpdateGame(Scene *scene)
{
    Input *input = Scene_GetInput(scene);
    Camera *camera = Scene_GetCamera(scene);


    // Calcule la position de la souris et son déplacement
    Vec2 mousePos = Vec2_Set(0.0f, 0.0f);
    Vec2 mouseDelta = Vec2_Set(0.0f, 0.0f);
    Camera_ViewToWorld(camera, (float)input->mouseX, (float)input->mouseY, &mousePos);
    Camera_ViewToWorld(camera, (float)(input->mouseX + input->mouseDeltaX), (float)(input->mouseY + input->mouseDeltaY), &mouseDelta);
    mouseDelta = Vec2_Sub(mouseDelta, mousePos);
    scene->m_mousePos = mousePos;


    // Déplacement de la caméra
    if (input->mouseRDown)
    {
        Camera_Move(camera, Vec2_Scale(mouseDelta, -1.f));
        return;
    }

    
    // On regarde si une balle a atteint une étoile
    Scene_CheckStarHit(scene);
    
    // On définit le nombre max de ressort en fonction de la balle
    int springMax;
    if (input->ballSelected == 2) springMax = 2;
    else if (input->ballSelected == 3) springMax = 8;
    else springMax = 3;

    // on met à jour les balles les plus proches et le nombre
    // de balles à distance valide dans m_validCount
    scene->m_validCount = Scene_GetNearestBalls(scene, mousePos, scene->m_queries, springMax);

    
    // On rajoute une balle
    if (input->mouseLPressed && input->ballSelected <= 4) {
        // si la souris est plus haut que 3 sur le référentiel du jeu
        // et qu'il n'est possible de relier aucun ressort, alors on return
        if (scene->m_validCount == 0 && mousePos.y >= 3.0f) { return; }


        // création de la balle
        Ball* ball = Scene_CreateBall(scene, mousePos, input->ballSelected);
        
        // type de ressort, 0 normal et 1 bambou
        int springType = 0;
        if (input->ballSelected == 4) springType = 1;

        // on récupère le tableau avec les structures BallQuery
        BallQuery* queries = scene->m_queries;

        // on récupère le nombre de balles et on définit le 
        // nombre max de balles en fonction du nombre max
        // de ressort que la balle peut accepter
        int max, ballCount = Scene_GetBallCount(scene) - 1;

        if (ballCount < ball->springMax) max = ballCount;
        else max = ball->springMax;


        // on définit la longueur du ressort en fonction
        // du type de la balle
        float springLength;
        switch (ball->type) {
        case 1:
            springLength = 3.0f;
            break;

        case 2:
            springLength = 1.f;
            break;
        
        default:
            springLength = 1.5f;
            break;
        }

        
        for (int i = 0; i < max; i++) {
            if (!queries[i].ball)
                break;
            
            Ball_Connect(ball, queries[i].ball, springLength, springType);
        }
    }    

    // On supprime une balle
    if (input->mouseLPressed && input->ballSelected == 5) {
        BallQuery nearestBall = Scene_GetNearestBall(scene, mousePos);

        if (nearestBall.ball)
            Scene_RemoveBall(scene, nearestBall.ball);
    }


    // reset la vue
    if (input->spaceKeyDown) {
        int width = Renderer_GetWidth(scene->m_renderer);
        int height = Renderer_GetHeight(scene->m_renderer);

        Camera_Free(camera);
        scene->m_camera = Camera_New(width, height);
        if (!scene->m_camera) printf("Error > Scene_UpdateGame > new camera\n");
    }
}

void Scene_Update(Scene *scene)
{
    float timeStep = scene->m_timeStep;

    // Met à jour les entrées de l'utilisateur
    Input_Update(scene->m_input);

    // si le menu est ouvert, on arrête de mettre à jour le jeu
    if (!scene->m_input->menuOpened) {
        // Met à jour le moteur physique (pas de temps fixe)
        scene->m_accu += Timer_GetDelta(g_time);
        while (scene->m_accu >= timeStep)
        {
            Scene_FixedUpdate(scene, timeStep);
            scene->m_accu -= timeStep;
        }

        // Met à jour la caméra (déplacement)
        Camera_Update(scene->m_camera);

        // Met à jour le jeu
        Scene_UpdateGame(scene);
    }
}

void Scene_RenderBalls(Scene *scene)
{
    int ballCount = Scene_GetBallCount(scene);
    Ball *balls = Scene_GetBalls(scene);
    for (int i = 0; i < ballCount; i++)
    {
        Ball *ball = &balls[i];
        int springCount = ball->springCount;
        for (int j = 0; j < springCount; j++)
        {
            // Supprime le flag
            ball->springs[j].flags &= ~SPRING_RENDERED;
        }
    }

    for (int i = 0; i < ballCount; i++)
    {
        Ball *ball = &balls[i];
        Vec2 start = Ball_GetPosition(ball);

        int springCount = ball->springCount;
        for (int j = 0; j < springCount; j++)
        {
            Spring *spring = ball->springs + j;
            if ((spring->flags & SPRING_RENDERED) != 0)
            {
                continue;
            }

            // Ajoute le flag
            spring->flags |= SPRING_RENDERED;

            // Affiche le ressort
            Vec2 end = Ball_GetPosition(spring->other);
            Ball_RenderSpring(start, end, scene, true, spring->type);
        }
    }

    for (int i = 0; i < ballCount; i++)
    {
        // Affiche la balle
        Ball_Render(&balls[i], scene);
    }
}

void Scene_RenderStars(Scene* scene) {
    int starsCount = scene->m_starsCount;
    Star* stars = scene->m_stars;

    for (int i = 0; i < starsCount; i++)
    {
        // Affiche l'étoile
        Star_Render(&stars[i], scene);
    }
}


void Scene_Render(Scene *scene)
{
    // Dessine le fond (avec parallax)
    Background_Render(scene);

    // Dessine le sol
    TileMap_Render(scene);

    // Si on a une balle en main et que le menu n'est pas ouvert,
    // on affiche les ressorts qui pourront être reliées
    if (scene->m_input->mouseRDown == false && !scene->m_input->menuOpened && scene->m_input->ballSelected != 5)
    {
        // Dessine les ressorts inactifs
        BallQuery *queries = scene->m_queries;
        for (int i = 0; i < MAX_QUERY_COUNT; ++i)
        {
            if (queries[i].ball) {
                Vec2 start = Scene_GetMousePosition(scene);
                Vec2 end = Ball_GetPosition(queries[i].ball);

                Ball_RenderSpring(start, end, scene, false, 0);
            }
        }
    }

    // Dessine les étoiles
    Scene_RenderStars(scene);

    // Dessine les balles (avec les ressorts actifs)
    Scene_RenderBalls(scene);

    // Fait apparaître la barre d'outils
    DisplayBar(scene);

    // Si on doit updateScore
    if (scene->score.scoreHasChanged) {
        updateScore(scene);
        scene->score.scoreHasChanged = 0;
    }

    // Fait apparaître le score
    displayScore(scene);

    // Fait apparaitre le menu
    if (scene->m_input->menuOpened) {
        DisplayMenu(scene);
    }
}