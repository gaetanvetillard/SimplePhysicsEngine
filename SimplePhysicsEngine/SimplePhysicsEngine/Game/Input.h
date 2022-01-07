#ifndef _INPUT_H_
#define _INPUT_H_

#include "../Settings.h"

typedef struct Input_s
{
    bool quitPressed;
    bool restartPressed;
    /// @brief Si le menu est ouvert avec ECHAP
    bool menuOpened;

    bool mouseLPressed;
    bool mouseRPressed;
    bool mouseLDown;
    bool mouseRDown;

    /// @brief Réinitialisation de la vue avec ESPACE
    bool spaceKeyDown;

    int mouseX;
    int mouseY;
    int mouseDeltaX;
    int mouseDeltaY;

    /// @brief La balle choisie (molette ou 1 2 3 4 5)
    int ballSelected;
} Input;

Input *Input_New();
void Input_Free(Input *input);
void Input_Update(Input *input);

#endif
