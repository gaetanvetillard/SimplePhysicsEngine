#ifndef _TOOLS_H_
#define _TOOLS_H_

#include "../Settings.h"

float Float_Clamp(float value, float a, float b);

float Float_SmoothDamp(
    float current, float target, float *currentVelocity,
    float smoothTime, float maxSpeed, float deltaTime);

#endif
