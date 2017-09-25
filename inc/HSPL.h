/**
 * @file HSPL.h
 * @author Felipe Leite
 * @date 07 Sep 2017
 * @brief File containing header file of the Hardware Script Programming Language
 *
 * The HSPL supports the protocol layer of this script language.
 * Through the HPSLContext, the functions in this source code can prepare the
 * structure or can decode a packet received over a physical communication link.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */
#ifndef INC_HSPL_H_
#define INC_HSPL_H_

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <HSPL_errors.h>
#include <ringbuf.h>
#include <memmem.h>

#define startPreAmbleSize 3

typedef struct protocolContextTag{
	uint8_t b_startPreAmble[startPreAmbleSize];
	uint8_t b_sizeByte;
	uint8_t s_payloadString[256];
	uint32_t i_crc;
}HSPLContext;

char HSPL_Init(HSPLContext *context);
unsigned char HSPL_Protocol_prepareToSend(HSPLContext *context, char *payload);
int HSPL_calculateCRC(HSPLContext *context);
char HSPL_Protocol_Decode(HSPLContext *context, char *msgBuffer, int size);

#endif /* INC_HSPL_H_ */
