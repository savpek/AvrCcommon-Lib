#include "./utest/public/utest.h"

#include "./str/public/str.h"

TEST_GROUP(str);

TEST_SETUP(str) {

}

TEST_TEAR_DOWN(str) {

}

TEST(str, test_str_compare) {
	TEST_ASSERT( str_compare("abc", "abc", STR_FROM_BEGIN, STR_TO_END) == SC_TRUE );
	TEST_ASSERT( str_compare("abc", "acb", STR_FROM_BEGIN, STR_TO_END) == SC_FALSE );
	TEST_ASSERT( str_compare("", "", STR_FROM_BEGIN, STR_TO_END) == SC_TRUE );
	TEST_ASSERT( str_compare("abcd", "", STR_FROM_BEGIN, STR_TO_END) == SC_FALSE );
	TEST_ASSERT( str_compare("", "abcd", STR_FROM_BEGIN, STR_TO_END) == SC_FALSE );
	TEST_ASSERT( str_compare("abc", "abcd", STR_FROM_BEGIN, STR_TO_END) == SC_FALSE );
	TEST_ASSERT( str_compare("abcd", "abc", STR_FROM_BEGIN, STR_TO_END) == SC_FALSE );
	TEST_ASSERT( str_compare("abcd", "abc", STR_FROM_BEGIN, 2) == SC_TRUE );
	TEST_ASSERT( str_compare("abcdef", "abc", STR_FROM_BEGIN, 3) == SC_FALSE );
	TEST_ASSERT( str_compare("abcdef", "xbcd", 1, 3) == SC_TRUE );
	TEST_ASSERT( str_compare("abcdef", "xbcd", 2, 4) == SC_FALSE );
}
#if 0
TEST(str, test_str_from_uint8_hex) {
	volatile char str_buffer[30] = {0};

	str_from_uint8_hex(0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0x00", str_buffer);

	str_from_uint8_hex(~0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0xFF", str_buffer);

	str_from_uint8_hex(20, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0x14", str_buffer);
}

TEST(str, test_str_from_uint32_hex) {
	volatile char str_buffer[30] = {0};

	str_from_uint32_hex(0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0x00000000", str_buffer);

	str_from_uint32_hex(~0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0xFFFFFFFF", str_buffer);

	str_from_uint32_hex(20, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0x00000014", str_buffer);
}

TEST(str, test_str_from_uint8) {
	volatile char str_buffer[30] = {0};

	str_from_uint8(0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0", str_buffer);

	str_from_uint8(~0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("255", str_buffer);

	/* How overflow will work ->*/
	str_from_uint8(255+10, str_buffer);
	TEST_ASSERT_EQUAL_STRING("9", str_buffer);
}

TEST(str, test_str_from_uint32) {
	volatile char str_buffer[30] = {0};

	str_from_uint32(0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0", str_buffer);

	str_from_uint32(~0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("4294967295", str_buffer);

	str_from_uint32(3500, str_buffer);
	TEST_ASSERT_EQUAL_STRING("3500", str_buffer);

	/* How overflow will work ->*/
	str_from_uint32(4294967295+10, str_buffer);
	TEST_ASSERT_EQUAL_STRING("9", str_buffer);
}

TEST(str, test_str_from_int32) {
	volatile char str_buffer[30] = {0};

	str_from_int32(0, str_buffer);
	TEST_ASSERT_EQUAL_STRING("0", str_buffer);

	str_from_int32(-100, str_buffer);
	TEST_ASSERT_EQUAL_STRING("-100", str_buffer);

	str_from_int32(100, str_buffer);
	TEST_ASSERT_EQUAL_STRING("100", str_buffer);

	str_from_int32(-2147483648, str_buffer);
	TEST_ASSERT_EQUAL_STRING("-2147483648", str_buffer);

	str_from_int32(2147483647, str_buffer);
	TEST_ASSERT_EQUAL_STRING("2147483647", str_buffer);

	/* How overflow will work ->*/
	str_from_int32(2147483647+10, str_buffer);
	TEST_ASSERT_EQUAL_STRING("-2147483639", str_buffer);

	str_from_int32(-2147483648-10, str_buffer);
	TEST_ASSERT_EQUAL_STRING("2147483638", str_buffer);
}

TEST(str, test_str_merge) {
	volatile char str_bufferx[30] = {0};

	str_merge("merged", str_bufferx, 0);
	TEST_ASSERT_EQUAL_STRING("merged", str_bufferx);
	str_merge(" merged", str_bufferx, 6);
	TEST_ASSERT_EQUAL_STRING("merged merged", str_bufferx);
}

TEST(str, str_get_token_indexes__basic_functionality) {
	uint8_t begin_idx;
	uint8_t end_idx;

	char delimiter = ' ';
	uint8_t token_number = 0;
	str_get_token_indexes("Find from this", delimiter, token_number, &begin_idx, &end_idx);

	uint8_t expected = 0;
	TEST_ASSERT_EQUAL_UINT8( expected, begin_idx);
	expected = 3;
	TEST_ASSERT_EQUAL_UINT8( expected, end_idx);

	token_number = 1;
	str_get_token_indexes("Find from this", delimiter, token_number, &begin_idx, &end_idx);
	expected = 5;
	TEST_ASSERT_EQUAL_UINT8( expected, begin_idx);
	expected = 8;
	TEST_ASSERT_EQUAL_UINT8( expected, end_idx);

	token_number = 2;
	str_get_token_indexes("Find from this", delimiter, token_number, &begin_idx, &end_idx);
	expected = 10;
	TEST_ASSERT_EQUAL_UINT8( expected, begin_idx);
	expected = 13;
	TEST_ASSERT_EQUAL_UINT8( expected, end_idx);
	
	TEST_ASSERT( str_get_token_indexes("Find from this", delimiter, token_number, &begin_idx, &end_idx)
				 == SC_SUCCESS );
}


TEST(str, str_get_token_indexes__token_out_of_range) {
	uint8_t begin_idx;
	uint8_t end_idx;

	char delimiter = ' ';
	uint8_t token_number = 4;
	TEST_ASSERT( str_get_token_indexes("Find from this", delimiter, token_number, &begin_idx, &end_idx)
				 == SC_OUT_OF_RANGE );
}

TEST(str, str_get_token_indexes__null_arguments) {
	uint8_t begin_idx;
	uint8_t end_idx;

	char delimiter = ' ';
	char *test_string = "Find from this";
	uint8_t token_number = 1;
	TEST_ASSERT( str_get_token_indexes(NULL, delimiter, token_number, &begin_idx, &end_idx)
				 == SC_NULL_ARGUMENT);
				 
	TEST_ASSERT( str_get_token_indexes(NULL, delimiter, token_number, NULL, &end_idx)
				 == SC_NULL_ARGUMENT);
				 
	TEST_ASSERT( str_get_token_indexes(NULL, delimiter, token_number, &begin_idx, NULL)
				 == SC_NULL_ARGUMENT);
}
#endif

TEST(str, test_str_is_substring_of) {
    TEST_ASSERT( str_is_substring_of("abcd", "ab", 0) == SC_TRUE);
    TEST_ASSERT( str_is_substring_of("abcd", "xy", 0) == SC_FALSE);
    TEST_ASSERT( str_is_substring_of("abcd", "bc", 1) == SC_TRUE);
    TEST_ASSERT( str_is_substring_of("abcd", "er", 1) == SC_FALSE);
    TEST_ASSERT( str_is_substring_of("cd", "cde", 0) == SC_FALSE);
    TEST_ASSERT( str_is_substring_of("cd", "cd", 0) == SC_TRUE);
}


TEST(str, test_str_is_substring_of_with_ending) {
    TEST_ASSERT( str_is_word_in_string("ab", "ab", 0, "") == SC_TRUE );
    TEST_ASSERT( str_is_word_in_string("abc", "ab", 0, "") == SC_FALSE );
    TEST_ASSERT( str_is_word_in_string("abc c", "abc", 0, " ") == SC_TRUE );
    TEST_ASSERT( str_is_word_in_string("abc cd e", "cd", 4, "") == SC_FALSE );
    TEST_ASSERT( str_is_word_in_string("abc cd e", "cd", 4, " ") == SC_TRUE );
    
}

TEST_GROUP_RUNNER(str) {
#if 0
	RUN_TEST_CASE(str, str_get_token_indexes__basic_functionality);
	RUN_TEST_CASE(str, str_get_token_indexes__token_out_of_range);
	RUN_TEST_CASE(str, str_get_token_indexes__null_arguments);
	RUN_TEST_CASE(str, test_str_compare);
	RUN_TEST_CASE(str, test_str_from_uint8_hex);
	RUN_TEST_CASE(str, test_str_merge);
	RUN_TEST_CASE(str, test_str_from_uint32_hex);
	RUN_TEST_CASE(str, test_str_from_uint32);
	RUN_TEST_CASE(str, test_str_from_uint8);
	RUN_TEST_CASE(str, test_str_from_int32);
#endif
    RUN_TEST_CASE(str, test_str_is_substring_of);
    RUN_TEST_CASE(str, test_str_is_substring_of_with_ending);
    
}