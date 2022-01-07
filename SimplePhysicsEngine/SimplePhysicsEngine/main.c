#include "Settings.h"

#include "Utils/Timer.h"
#include "Utils/Renderer.h"
#include "Utils/Window.h"
#include "Game/Ball.h"
#include "Game/Camera.h"
#include "Game/Scene.h"

int main(int argc, char *argv[])
{
    Window *window = NULL;
    Renderer *renderer = NULL;
    Scene *scene = NULL;

    int exitStatus = Settings_InitSDL();
    if (exitStatus == EXIT_FAILURE) goto ERROR_LABEL;
    
    window = Window_New(WINDOW_WIDTH, WINDOW_HEIGHT);
    if (!window) goto ERROR_LABEL;

    renderer = Window_GetRenderer(window);

    g_time = Timer_New();
    if (!g_time) goto ERROR_LABEL;

    // Lance le temps global du jeu
    Timer_Start(g_time);

    bool quitGame = false;
    while (!quitGame)
    {
        // Crée la scène
        scene = Scene_New(renderer);
        if (!scene) goto ERROR_LABEL;

        // Boucle de rendu
        while (true)
        {
            if (scene->m_input->quitPressed || scene->m_input->restartPressed)
            {
                quitGame = scene->m_input->quitPressed;
                break;
            }

            // Met à jour le temps global
            Timer_Update(g_time);

            // Met à jour la scène
            Scene_Update(scene);

            // Efface le rendu précédent
            Renderer_Clear(renderer);

            // Calcule le rendu de la scène
            Scene_Render(scene);

            // Affiche le buffer
            Renderer_Update(renderer);
        }

        // Détruit la scène
        Scene_Free(scene);
        scene = NULL;
    }

    Scene_Free(scene);
    scene = NULL;
    Timer_Free(g_time);
    g_time = NULL;
    Window_Free(window);
    window = NULL;

    Settings_QuitSDL();

    return EXIT_SUCCESS;

ERROR_LABEL:
    printf("ERROR - main()\n");
    assert(false);
    Window_Free(window);
    Scene_Free(scene);
    Timer_Free(g_time);
    Settings_QuitSDL();
    return EXIT_FAILURE;
}