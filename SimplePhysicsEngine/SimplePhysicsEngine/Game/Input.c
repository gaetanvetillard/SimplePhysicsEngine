#include "Input.h"

Input *Input_New()
{
    Input *input = NULL;

    input = (Input *)calloc(1, sizeof(Input));
    if (!input) goto ERROR_LABEL;

    // initialisation de la balle selectionée 
    input->ballSelected = 0;

    return input;

ERROR_LABEL:
    printf("ERROR - Input_New()\n");
    assert(false);
    Input_Free(input);
    return NULL;
}

void Input_Free(Input *input)
{
    if (!input)
        return;

    free(input);
}

void Input_Update(Input *input)
{
    SDL_Event evt;

    input->quitPressed = false;
    input->restartPressed = false;
    input->mouseLPressed = false;
    input->mouseRPressed = false;
    input->spaceKeyDown = false;

    int lastMouseX = input->mouseX;
    int lastMouseY = input->mouseY;

    while (SDL_PollEvent(&evt))
    {
        switch (evt.type)
        {
        case SDL_QUIT:
            input->quitPressed = true;
            break;

        case SDL_KEYDOWN:
            if (evt.key.repeat)
                break;

            switch (evt.key.keysym.scancode)
            {
            // ECHAP pour accéder au menu pause
            case SDL_SCANCODE_ESCAPE:
                input->menuOpened = !input->menuOpened;
                break;

            // ENTREE pour relancer une partie
            case SDL_SCANCODE_RETURN:
                input->restartPressed = true;
                break;

            // ESPACE pour réinitialiser la vue
            case SDL_SCANCODE_SPACE:
                input->spaceKeyDown = true;
                break;

            // Choix de la balle 
            case SDL_SCANCODE_1:
                input->ballSelected = 0;
                break;

            case SDL_SCANCODE_2:
                input->ballSelected = 1;
                break;

            case SDL_SCANCODE_3:
                input->ballSelected = 2;
                break;
               
            case SDL_SCANCODE_4:
                input->ballSelected = 3;
                break;

            case SDL_SCANCODE_5:
                input->ballSelected = 4;
                break;

            case SDL_SCANCODE_6:
                input->ballSelected = 5;
                break;
            // Fin du choix de la balle
                
            default:
                break;
            }
            break;

        case SDL_KEYUP:
            if (evt.key.repeat)
                break;

            switch (evt.key.keysym.scancode)
            {
            default:
                break;
            }
            break;

        case SDL_MOUSEWHEEL:
            // Choix de la balle, molette up pour aller vers la droite
            // molette down pour aller vers la gauche
            if (evt.wheel.y > 0)
                if (input->ballSelected == 5) input->ballSelected = 0;
                else input->ballSelected += 1;
            else
                if (input->ballSelected == 0) input->ballSelected = 5;
                else input->ballSelected -= 1;
            break;

        case SDL_MOUSEMOTION:
            input->mouseX = evt.motion.x;
            input->mouseY = evt.motion.y;
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch (evt.button.button)
            {
            case SDL_BUTTON_LEFT:
                input->mouseLDown = true;
                input->mouseLPressed = true;
                break;
            case SDL_BUTTON_RIGHT:
                input->mouseRDown = true;
                input->mouseRPressed = true;
                break;
            default:
                break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch (evt.button.button)
            {
            case SDL_BUTTON_LEFT:
                input->mouseLDown = false;
                break;
            case SDL_BUTTON_RIGHT:
                input->mouseRDown = false;
                break;
            default:
                break;
            }
            break;
        }
    }

    input->mouseDeltaX = input->mouseX - lastMouseX;
    input->mouseDeltaY = input->mouseY - lastMouseY;
}