#ifndef _INPUT_H_
#define _INPUT_H_

#include "../Settings.h"

typedef struct Input_s
{
    bool quitPressed;
    bool restartPressed;

    bool mouseLPressed;
    bool mouseRPressed;
    bool mouseLDown;
    bool mouseRDown;

    int mouseX;
    int mouseY;
    int mouseDeltaX;
    int mouseDeltaY;
} Input;

Input *Input_New();
void Input_Free(Input *input);
void Input_Update(Input *input);

#endif
