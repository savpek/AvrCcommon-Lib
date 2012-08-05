/*!
 *	@file D:\Dropbox\AVR32\TLCR\FIRMWARE\src\api\print\test\test_print.c
 *  @author: savpek
 *
 *	@brief Test file for unity.
 */


#include "framework.h"
#include "./print/public/print.h"
#include "./usart/public/usart.h"
#include "./usart/spy/spy_usart.h"
#include "./print/public/print.h"

#define OUTPUT_STREAM_FUNCTION usart_send_char

void (*backup_usart_putchar)( void) = NULL;

/*! You must change output streams during tests because you need same
 *	output driver for unity error messages! */
#define SET_DEFAULT_OUTPUT() OUTPUT_STREAM_FUNCTION = backup_usart_putchar;
#define SET_SPY_OUTPUT()	 OUTPUT_STREAM_FUNCTION = spy_usart_send_char;

/*! @brief Set-up test group for: str
 *	@param Group name */
TEST_GROUP(print);

/*! @brief Group setup function..
 *	@param Group name */
TEST_SETUP(print) {
	if(backup_usart_putchar == NULL)
		backup_usart_putchar = OUTPUT_STREAM_FUNCTION;

	usart_send_char = spy_usart_send_char;
	spy_usart_reset_output_buffer();
}

/*! @brief Group teardown function..
 *	@param Group name */
TEST_TEAR_DOWN(print) {
	OUTPUT_STREAM_FUNCTION = backup_usart_putchar;
}

/*! @brief Test print_char function from api.
 *	@param Group name
 *	@param Test name */
TEST(print, test_print_char) {
	spy_usart_reset_output_buffer();

	SET_SPY_OUTPUT();
	print_char('b');
	print_char('c');
	SET_DEFAULT_OUTPUT();
	char* output_stream = spy_usart_get_output_buffer();
	TEST_ASSERT_EQUAL_UINT8('b', output_stream[0]);
	TEST_ASSERT_EQUAL_UINT8('c', output_stream[1]);
}

/*! @brief Test print_string
 *	@param Group name
 *	@param Test name */
TEST(print, test_print_line) {
	char* output_stream = spy_usart_get_output_buffer();

	SET_SPY_OUTPUT();

	spy_usart_reset_output_buffer();
	print_line("this is test line");
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("this is test line\n\r", output_stream);

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_line("");
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("\n\r", output_stream);
}

/*! @brief Test print_string
 *	@param Group name
 *	@param Test name */
TEST(print, test_print_string) {
	char* output_stream = spy_usart_get_output_buffer();

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_string("this is test line");
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("this is test line", output_stream);

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_string("");
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("", output_stream);
}

/*! @brief Test print_hex8
 *	@param Group name
 *	@param Test name */
TEST(print, test_print_hex8) {
	char* output_stream = spy_usart_get_output_buffer();

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_hex8(0x00);
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("0x00", output_stream);

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_hex8(255);
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("0xFF", output_stream);

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_hex8(100);
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("0x64", output_stream);

}

/*! @brief Test print_hex32
 *	@param Group name
 *	@param Test name */
TEST(print, test_print_hex32) {
	char* output_stream = spy_usart_get_output_buffer();

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_hex32(0x00);
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("0x00000000", output_stream);

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_hex32(~0);
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("0xFFFFFFFF", output_stream);

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_hex32(98000);
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("0x00017ED0", output_stream);
}

/*! @brief Test print_dec
 *	@param Group name
 *	@param Test name */
TEST(print, test_print_dec) {
	char* output_stream = spy_usart_get_output_buffer();

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_dec(0);
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("0", output_stream);

	SET_SPY_OUTPUT();
	spy_usart_reset_output_buffer();
	print_dec(500);
	SET_DEFAULT_OUTPUT();
	TEST_ASSERT_EQUAL_STRING("500", output_stream);
}

/*	@brief Set up all runnable tests from this module.
 *	@param group name.*/
TEST_GROUP_RUNNER(print) {
	RUN_TEST_CASE(print, test_print_char);
	RUN_TEST_CASE(print, test_print_line);
	RUN_TEST_CASE(print, test_print_string);
	RUN_TEST_CASE(print, test_print_hex8);
	RUN_TEST_CASE(print, test_print_hex32);
	RUN_TEST_CASE(print, test_print_dec);
}
