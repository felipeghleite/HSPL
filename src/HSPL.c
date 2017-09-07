/**
 * @file HSPL.c
 * @author Felipe Leite
 * @date 07 Sep 2017
 * @brief File containing source code of the Hardware Script Programming Language
 *
 * The HSPL supports the protocol layer of this script language.
 * Through the HPSLContext, the functions in this source code can prepare the
 * structure or can decode a packet received over a physical communication link.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */

#ifndef SRC_HSPL_C_
#define SRC_HSPL_C_

#include <HSPL.h>

/**
 * @brief It clears the structure passed over to this function.
 *
 * It clears all the fields of the structure HSPLContext
 *
 * @return @c HSPL_NO_ERROR is always returned.
 */
char HSPL_Init(HSPLContext *context){
	context->b_sizeByte = 0;
	context->b_startByte = 0;
	context->s_payloadString[0] = 0;
	context->i_crc = 0;

	return HSPL_NO_ERROR;
}

/**
 * @brief This function prepare a HSPLContext to be sent over the communication link.
 *
 * It receives a pointer to a HSPLContext structure and a string payload.
 * It prepares all the fields of the structure, including the 4-byte checksum.
 *
 * @return @c HSPL_NO_ERROR is always returned.
 */
unsigned char HSPL_Protocol_prepareToSend(HSPLContext *context, char *payload){
	context->b_startByte = 0x55;
	context->b_sizeByte = strlen(payload);
	strcpy(context->s_payloadString, payload);
	context->i_crc = HSPL_calculateCRC(context);

	return HSPL_NO_ERROR;

}

/**
 * @brief This function calculates the checksum of the structure.
 *
 * It receives a pointer to a HSPLContext structure and calculate the checksum of it.
 *
 * @return @c HSPL_PAYLOAD_SIZE_ERROR is returned if the HSPLContext have no payload
 * or returns the CRC if there was no error.
 */
int HSPL_calculateCRC(HSPLContext *context){
	int CRC = 0xFFFF;
	int *temp;
	temp = context;
	int size = context->b_sizeByte + 2;
	size = size/4;
	if(context->b_sizeByte == 0){
		return HSPL_PAYLOAD_SIZE_ERROR; //error
	}

	while(size--){
		CRC ^= (int)*temp++;
	}

	//context->i_crc = CRC;

	return CRC;
}

/**
 * @brief This function decodes a byte array into a HSPLContext structure.
 *
 * It receives a pointer to a HSPLContext structure and a byte array containing
 * all the bytes received through the physical channel link.
 * It puts all the bytes into the HSPLContext structure and checks if the checksum is correct.
 *
 * @return @c HSPL_DECODE_ERROR is returned if the checksum is not correct or
 * HSPL_NO_ERROR is returned if there was no error.
 */
char HSPL_Protocol_Decode(HSPLContext *context, char *msgBuffer){

	int checkCRC;

	context->b_startByte = msgBuffer++[0];
	context->b_sizeByte = msgBuffer++[0];
	strcpy(context->s_payloadString, msgBuffer);
	msgBuffer += sizeof(context->s_payloadString) + 2 ; //TODO: +2 porque a memória é alinhada em 32bits. (struct é feita com char+char+char[256]+int = 262 bytes q dá 32,75 int's. ou seja, tem que caber em 33 ints
	context->i_crc = *(int*)msgBuffer;

	checkCRC = HSPL_calculateCRC(context);
	if(checkCRC != context->i_crc)
		return HSPL_DECODE_ERROR;
	else return HSPL_NO_ERROR;
}



#endif /* SRC_HSPL_C_ */
