/*
 * HSPL.h
 *
 *  Created on: 5 de set de 2017
 *      Author: fleite
 */

#ifndef INC_HSPL_H_
#define INC_HSPL_H_

#include <stdio.h>
#include <string.h>

typedef struct protocolContextTag{
	unsigned char b_startByte;
	unsigned char b_sizeByte;
	char s_payloadString[256];
	int i_crc;
}HSPLContext;

void HSPL_Init();
unsigned char HSPL_Protocol_prepareToSend(HSPLContext *context, char *payload);
int HSPL_calculateCRC(HSPLContext *context);
unsigned char HSPL_Protocol_Decode(HSPLContext *context, char *msgBuffer);

#endif /* INC_HSPL_H_ */
