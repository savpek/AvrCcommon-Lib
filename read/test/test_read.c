#include "framework.h"

#include "read/public/read.h"

#include "usart/public/usart.h"
#include "usart/spy/spy_usart.h"

void (*backup_usart_try_read_char)(void) = NULL;
void (*backup_usart_send_char)(void) = NULL;

void disable_usart_output_mocks()
{
	usart_send_char = backup_usart_send_char;
}

void enable_usart_output_mocks()
{
	usart_send_char = spy_usart_send_char;
}

TEST_GROUP(read);
TEST_SETUP(read) {
	if(backup_usart_try_read_char == NULL)
		backup_usart_try_read_char = usart_try_read_char;
	usart_try_read_char = spy_usart_try_read_char;

	if(backup_usart_send_char == NULL)
		backup_usart_send_char = usart_send_char;
	
	enable_usart_output_mocks();
	spy_usart_reset_output_buffer();
}

TEST_TEAR_DOWN(read) {
	usart_try_read_char = backup_usart_try_read_char;

	disable_usart_output_mocks();
	spy_usart_reset_output_buffer();
}

TEST(read, test_read_char) {
	spy_usart_put_to_receiver_stream("a");
	
	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_UINT8('a', read_char());

	/* Cannot test empty buffer since then readchar will stuck
	 * forever. */
}

TEST(read, test_try_read_char) 
{
	spy_usart_put_to_receiver_stream("a");
	
	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_UINT8('a', read_try_get_char());
	TEST_ASSERT_EQUAL_UINT8('\0', read_try_get_char()); /* Empty */

	spy_usart_put_to_receiver_stream('\0x01');
	TEST_ASSERT_EQUAL_UINT8('\0', read_try_get_char());
}

TEST(read, test_read_data) {
	spy_usart_put_to_receiver_stream("\b");
	
	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_UINT8('\b', read_data());
}

TEST(read, test_read_line__ignore_non_chars)
{
	const char incoming_stream[] = "\t\r\n"; //\t = horizontal tab.
	const char expected_return[] = "";
	const char expected_echo[] = "\r\n";
	char actual_return[10] = {0};
	char* actual_echo;

	spy_usart_put_to_receiver_stream( incoming_stream);
	read_line(actual_return, 5);
	actual_echo = spy_usart_get_output_buffer();

	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_STRING( expected_echo, actual_echo);
	TEST_ASSERT_EQUAL_STRING( expected_return, actual_return);
}

TEST(read, test_read_line__abc_string)
{
	const char incoming_stream[] = "abc\r\n";
	const char expected_return[] = "abc";
	char expected_echo[] = "abc\r\n";
	char actual_return[10] = {0};
	char* actual_echo;

	spy_usart_put_to_receiver_stream( incoming_stream);
	read_line(actual_return, 5);
	actual_echo = spy_usart_get_output_buffer();

	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_STRING( expected_echo, actual_echo);
	TEST_ASSERT_EQUAL_STRING( expected_return, actual_return);
}

TEST(read, test_read_line__string_w_backspace)
{
	char incoming_stream[] = "c\b xxx \r\n";
	char expected_return[] = " xxx ";
	char expected_echo[] = "c\b xxx \r\n";
	char actual_return[10] = {0};
	char* actual_echo;

	spy_usart_put_to_receiver_stream( incoming_stream);
	read_line(actual_return, 10);
	actual_echo = spy_usart_get_output_buffer();

	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_STRING( expected_echo, actual_echo);
	TEST_ASSERT_EQUAL_STRING( expected_return, actual_return);
}

TEST(read, test_read_line__string_w_delete_char)
{
	char incoming_stream[] = "x\177\r\n"; // Delete, OCTAL 177.
	char expected_return[] = "";
	char expected_echo[] = "x\177\r\n";
	char actual_return[10] = {0};
	char* actual_echo;

	spy_usart_put_to_receiver_stream( incoming_stream);
	read_line(actual_return, 10);
	actual_echo = spy_usart_get_output_buffer();

	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_STRING( expected_echo, actual_echo);
	TEST_ASSERT_EQUAL_STRING( expected_return, actual_return);
}
	
TEST(read, test_read_line__overrun_low_index)
{
	char incoming_stream[] = "\b\b\b\b\r\n"; // Delete, OCTAL 177.
	char expected_return[] = "";
	char expected_echo[] = "\r\n";
	char actual_return[10] = {0};
	char* actual_echo;

	spy_usart_put_to_receiver_stream( incoming_stream);
	read_line(actual_return, 10);
	actual_echo = spy_usart_get_output_buffer();

	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_STRING( expected_echo, actual_echo);
	TEST_ASSERT((*(actual_return-1)) != '\b');
}

TEST(read, test_read_line__overrun_high_index)
{
	char incoming_stream[] = "12345678\r\n"; // Delete, OCTAL 177.
	char expected_return[] = "123";
	char expected_echo[] = "123\r\n";
	char actual_return[10] = {0};
	char* actual_echo;

	spy_usart_put_to_receiver_stream( incoming_stream);
	read_line(actual_return, 3);
	actual_echo = spy_usart_get_output_buffer();

	disable_usart_output_mocks();
	TEST_ASSERT_EQUAL_STRING( expected_echo, actual_echo);
	TEST_ASSERT_EQUAL_STRING( expected_return, actual_return);
}

TEST(read, test_read_line__line_changes_on_nl)
{
    char incoming_stream[] = "123\n3";
    char expected_return[] = "123";
    char actual_return[10] = {0};
    spy_usart_put_to_receiver_stream(incoming_stream);
    read_line(actual_return, 9);
    
    disable_usart_output_mocks();
    TEST_ASSERT_EQUAL_STRING(actual_return, expected_return);
}

TEST(read, test_read_line__line_changes_on_br)
{
    char incoming_stream[] = "123\r3\n";
    char expected_return[] = "123";
    char actual_return[10] = {0};
    spy_usart_put_to_receiver_stream(incoming_stream);
    read_line(actual_return, 9);
    
    disable_usart_output_mocks();
    TEST_ASSERT_EQUAL_STRING(expected_return, actual_return);
}

TEST_GROUP_RUNNER(read)
{
	RUN_TEST_CASE(read, test_read_char);
	RUN_TEST_CASE(read, test_try_read_char);
	RUN_TEST_CASE(read, test_read_data);
	RUN_TEST_CASE(read, test_read_line__ignore_non_chars);
	RUN_TEST_CASE(read, test_read_line__abc_string);
	RUN_TEST_CASE(read, test_read_line__string_w_backspace);
	RUN_TEST_CASE(read, test_read_line__string_w_delete_char);
	RUN_TEST_CASE(read, test_read_line__overrun_low_index);
	RUN_TEST_CASE(read, test_read_line__overrun_high_index);
    RUN_TEST_CASE(read, test_read_line__line_changes_on_nl);
    RUN_TEST_CASE(read, test_read_line__line_changes_on_br);
}
