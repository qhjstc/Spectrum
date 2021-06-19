#ifndef BASEPROJECTF4_WAVE_WINDOWS_H
#define BASEPROJECTF4_WAVE_WINDOWS_H

#include "main.h"
#include "arm_math.h"

void Hanning_Win(float inputs, uint16_t len);
void BlackMan_Win(float inputs, uint16_t len);

#endif //BASEPROJECTF4_WAVE_WINDOWS_H
