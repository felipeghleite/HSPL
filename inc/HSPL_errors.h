/**
 * @file HSPL.h
 * @author Felipe Leite
 * @date 07 Sep 2017
 * @brief File containing the errors code of the Hardware Script Programming Language
 *
 * The HSPL supports the protocol layer of this script language.
 * Through the HPSLContext, the functions in this source code can prepare the
 * structure or can decode a packet received over a physical communication link.
 *
 * @see http://www.stack.nl/~dimitri/doxygen/docblocks.html
 * @see http://www.stack.nl/~dimitri/doxygen/commands.html
 */
#ifndef INC_HSPL_ERRORS_H_
#define INC_HSPL_ERRORS_H_

enum HSPL_errors_code{
	HSPL_NO_ERROR = 0,
	HSPL_DECODE_ERROR,
	HSPL_PAYLOAD_SIZE_ERROR
};

#endif /* INC_HSPL_ERRORS_H_ */
