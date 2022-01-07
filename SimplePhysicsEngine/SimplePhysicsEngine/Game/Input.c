#include "Input.h"

Input *Input_New()
{
    Input *input = NULL;

    input = (Input *)calloc(1, sizeof(Input));
    if (!input) goto ERROR_LABEL;

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
            case SDL_SCANCODE_ESCAPE:
                input->quitPressed = true;
                break;

            case SDL_SCANCODE_RETURN:
                input->restartPressed = true;
                break;
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