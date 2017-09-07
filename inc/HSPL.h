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
#include <string.h>
#include <HSPL_errors.h>
#include <ringbuf.h>

typedef struct protocolContextTag{
	unsigned char b_startByte;
	unsigned char b_sizeByte;
	char s_payloadString[256];
	int i_crc;
}HSPLContext;

char HSPL_Init();
unsigned char HSPL_Protocol_prepareToSend(HSPLContext *context, char *payload);
int HSPL_calculateCRC(HSPLContext *context);
char HSPL_Protocol_Decode(HSPLContext *context, char *msgBuffer);

#endif /* INC_HSPL_H_ */
