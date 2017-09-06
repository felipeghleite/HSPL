/*
 * HSPL.c
 *
 *  Created on: 5 de set de 2017
 *      Author: fleite
 */

#ifndef SRC_HSPL_C_
#define SRC_HSPL_C_

#include <HSPL.h>

void HSPL_Init(HSPLContext *context){
	context->b_sizeByte = 0;
	context->b_startByte = 0;
	context->s_payloadString[0] = 0;
	context->i_crc = 0;
}

unsigned char HSPL_Protocol_prepareToSend(HSPLContext *context, char *payload){
	context->b_startByte = 0x55;
	context->b_sizeByte = strlen(payload);
	strcpy(context->s_payloadString, payload);
	HSPL_calculateCRC(context);

	return 0;

}

int HSPL_calculateCRC(HSPLContext *context){
	int CRC = 0xFFFF;
	int *temp;
	temp = context;
	int size = context->b_sizeByte + 2;
	size = size/4;
	if(context->b_sizeByte == 0){
		return -1; //error
	}

	while(size--){
		CRC ^= (int)*temp++;
	}

	context->i_crc = CRC;
}

unsigned char HSPL_Protocol_Decode(HSPLContext *context, char *msgBuffer){

	int index, size;

	context->b_startByte = msgBuffer++[0];
	context->b_sizeByte = msgBuffer++[0];
	strcpy(context->s_payloadString, msgBuffer);
	msgBuffer += sizeof(context->s_payloadString) + 2 ; //TODO: +2 porque a memória é alinhada em 32bits. (struct é feita com char+char+char[256]+int = 262 bytes q dá 32,75 int's. ou seja, tem que caber em 33 ints
	context->i_crc = *(int*)msgBuffer;
}



#endif /* SRC_HSPL_C_ */
