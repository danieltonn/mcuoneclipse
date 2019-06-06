/*
 * RaspyUART.h
 *
 *  Created on: 24.05.2019
 *      Author: Erich Styger Local
 */

#ifndef RASPYUART_H_
#define RASPYUART_H_

#include "McuShell.h"
#include <stdint.h>
#include <stdbool.h>

uint8_t RASPYU_ParseCommand(const unsigned char* cmd, bool *handled, const McuShell_StdIOType *io);

void RASPYU_OnJoystickEvent(uint32_t buttons);
bool RASPYU_GetEventsEnabled(void);
void RASPYU_SetEventsEnabled(bool on);

void RASPYU_Deinit(void);
void RASPYU_Init(void);

#endif /* RASPYUART_H_ */