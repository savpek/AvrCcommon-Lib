/*
 * errorh.h
 *
 * Created: 20.11.2011 11:35:53
 *  Author: savpek
 */


#ifndef ERRORH_H_
#define ERRORH_H_

/* Define error-codes here! */
typedef enum
	{
	/* True, OK, SUCCESS etc. type return values */
	SC_PASS = 1,
	SC_SUCCESS = 1,
	SC_DONE = 1,
	SC_TRUE = 1,

	/* Failures */
	SC_NULL = 0,
	SC_FAILURE = 0,
	SC_FALSE = 0,

	/* More informative error codes */
	SC_NOT_EMPTY = -1,
	SC_EMPTY = -2,
	SC_LOCKED = -3,
	SC_TIMEOUT = -4,
	SC_OUT_OF_RANGE = -5,
	SC_NOT_NUMBER = -6,
	SC_VALUE_ERROR = -7,
	SC_GOTO_NEXT = -8,
	SC_END = -9,
	SC_EXIT = -10,
	SC_NO_RESPONCE = -11,
	SC_EMPTY_CMD = -12,
	SC_ACCESS_DENIED = -13,
	SC_FULL = -15,
	SC_INVALID_ID = -16,
	SC_INVALID_VALUE = -17,
	SC_NULL_ARGUMENT = -18,

	/* Serial transmission errors */
	SC_OVERRUN = -1,
	SC_PARITY = -2,
	SC_INPUT_VALUE = -3,
	SC_RX = -4,
	SC_TX = -5,
	SC_RX_EMPTY = -6,
	SC_TX_BUSY = -7,

	/* Status codes */
	SC_HIGH = 1,
	SC_LOW = 0,
	} statusc_t;

/*! ASSERT handler! Define this null if building release. */
#define ASSERT(a) statusc_assert_body(a, __FILE__, __LINE__)

/*! @brief Don't use directly! See ERRORH_ASSERT() macro!
 *
 *	@param uint32_t assert_value : If not true, 1, trigger assert.
 *	@param char * file_name 	 : From macro.
 *	@param uint32_t assert_line  : From macro.
 *
 * 	@return void */
extern void statusc_assert_body(uint8_t assert_value, char* file_name, uint32_t assert_line );
#endif /* ERRORH_H_ */