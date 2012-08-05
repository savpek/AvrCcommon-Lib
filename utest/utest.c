#include "framework.h"
#include "utest/private/utest_template.h"

// Required ...
#include "str/public/str.h"

static uint8_t test_runned = 0;
static uint8_t test_failed = 0;

/* This isn't thread safe testing framework btw...
 * Longest possible print is int32_t type string. */
char string_buffer[STR_DEC_INT32_SIZE] = {0};

static void utest_print(const char * string) {
	for(int i = 0; string[i] != 0; i++) {
		UTEST_OUTPUT_CHAR(string[i]);
	}
}

static void utest_print_line(char* string) {
	utest_print(string);
	UTEST_OUTPUT_CHAR('\n');
	UTEST_OUTPUT_CHAR('\r');
}

static inline void utest_print_eol() {
	utest_print_line("");
}

/* This will run all test cases inside of utest_fixture() function. */
void utest_main(void (*utest_fixture)( void)) {
	utest_print_eol();
	utest_print_eol();
	utest_print_line("UTESTS:");
	utest_print_line("----");
	utest_fixture();
	utest_print_line("----");

	utest_str_from_uint8(test_runned, string_buffer);
	utest_print(string_buffer);
	utest_print(", ");
	utest_str_from_uint8(test_failed, string_buffer);
	utest_print(string_buffer);
	utest_print(" Failed.");
	utest_print_eol();
}

void utest_runner(	utest_function * test_setup,
					utest_function * test_body,
					utest_function * test_teardown,
					const char * printableName,
					const char * file ) {
						
	utest_print(printableName);
	utest_print(" from ");
	utest_print(file);
	utest_print_eol();

	test_setup();
	test_body();
	test_teardown();

	test_runned++;
}

/* Failure output functions ->*/
static void print_failure_msg_head() {
	utest_print("\033[91m>>>  FAIL! Expected ");
}

static void print_failure_msg_middle() {
	utest_print(" but was ");
}

static void print_failure_msg_footer(char * location) {
	utest_print(" ");
	utest_print(location);
	utest_print_eol();
	utest_print("\033[0m"); 
}

static void print_values_uint8(uint8_t value) {
	utest_print("[");
	utest_str_from_uint8(value, string_buffer);
	utest_print(string_buffer);
	utest_print(", ");

	utest_str_from_uint8_hex(value, string_buffer);
	utest_print(string_buffer);
	utest_print("]");
}

static void print_values_uint32(uint32_t value) {
	utest_print("[");
	utest_str_from_uint32(value, string_buffer);
	utest_print(string_buffer);
	utest_print(", ");

	utest_str_from_uint32_hex(value, string_buffer);
	utest_print(string_buffer);
	utest_print("]");
}

static void print_values_int32(int32_t value) {
	utest_print("[");
	utest_str_from_int32(value, string_buffer);
	utest_print(string_buffer);
	utest_print(", ");

	utest_str_from_uint32_hex((uint32_t)value, string_buffer);
	utest_print(string_buffer);
	utest_print("]");
}

static void print_values_string(char* value_string) {
	utest_print("[");
	utest_print(value_string);
	utest_print("]");
}

/* Assert functions -> */
void utest_assert(uint8_t condition, const char* location) {
	if(condition == 0) {
		print_failure_msg_head();
		utest_print("[TRUE]");
		print_failure_msg_middle();
		utest_print("[FALSE]");
		print_failure_msg_footer(location);
		test_failed++;
	}
}

void utest_assert_uint8(uint8_t expected, uint8_t actual, const char* location) {
	if(expected != actual) {
		print_failure_msg_head();
		print_values_uint8(expected);
		print_failure_msg_middle();
		print_values_uint8(actual);
		print_failure_msg_footer(location);
		test_failed++;
	}
}

void utest_assert_uint32(uint32_t expected, uint32_t actual, const char* location) {
	if(expected != actual) {
		print_failure_msg_head();
		print_values_uint32(expected);
		print_failure_msg_middle();
		print_values_uint32(actual);
		print_failure_msg_footer(location);
		test_failed++;
	}
}

void utest_assert_int32(int32_t expected, int32_t actual, const char* location) {
	if(expected != actual) {
		print_failure_msg_head();
		print_values_int32(expected);
		print_failure_msg_middle();
		print_values_int32(actual);
		print_failure_msg_footer(location);
		test_failed++;
	}
}

void utest_assert_string(char* expected, char* actual, const char* location) {
	statusc_t result = utest_str_compare(expected, actual, STR_NO_LIMIT);
	if( result == SC_FALSE)
	{
		print_failure_msg_head();
		print_values_string(expected);
		print_failure_msg_middle();
		print_values_string(actual);
		print_failure_msg_footer(location);
		test_failed++;
	}
}