#ifndef UTEST_FRAMEWORK_H
#define UTEST_FRAMEWORK_H

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define TEST_LOCATION TOSTRING( line: __LINE__)

#define TEST_ASSERT(condition)                                                                     utest_assert(condition, TEST_LOCATION)

#define TEST_ASSERT_EQUAL_INT8(expected, actual)                                                   utest_assert_int32( (int8_t)expected, (int8_t)actual, TEST_LOCATION)
#define TEST_ASSERT_EQUAL_INT32(expected, actual)                                                  utest_assert_int32( expected, actual, TEST_LOCATION)
#define TEST_ASSERT_EQUAL_UINT8(expected, actual)                                                  utest_assert_uint8( expected, actual, TEST_LOCATION)
#define TEST_ASSERT_EQUAL_UINT32(expected, actual)                                                 utest_assert_uint32( expected, actual, TEST_LOCATION)

#define TEST_ASSERT_EQUAL_STRING(expected, actual)                                                 utest_assert_string(expected, actual, TEST_LOCATION)

//TODO: Add these functionalities to framework!
#if 0
	#define TEST_ASSERT_EQUAL_MEMORY(expected, actual, len)                                            UNITY_TEST_ASSERT_EQUAL_MEMORY(expected, actual, len, __LINE__, NULL)
	#define TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements)                               UNITY_TEST_ASSERT_EQUAL_INT8_ARRAY(expected, actual, num_elements, __LINE__, NULL)
	#define TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_INT32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
	#define TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements)                               UNITY_TEST_ASSERT_EQUAL_UINT_ARRAY(expected, actual, num_elements, __LINE__, NULL)
	#define TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_UINT8_ARRAY(expected, actual, num_elements, __LINE__, NULL)
	#define TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements)                             UNITY_TEST_ASSERT_EQUAL_UINT32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
	#define TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements)                               UNITY_TEST_ASSERT_EQUAL_HEX8_ARRAY(expected, actual, num_elements, __LINE__, NULL)
	#define TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements)                              UNITY_TEST_ASSERT_EQUAL_HEX32_ARRAY(expected, actual, num_elements, __LINE__, NULL)
	#define TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements)                        UNITY_TEST_ASSERT_EQUAL_MEMORY_ARRAY(expected, actual, len, num_elements, __LINE__, NULL)
#endif

/* DO NOT USE THESE DIRECTLY! Only via macros! */
extern void utest_assert(uint8_t condition, const char* location);
extern void utest_assert_uint8(uint8_t expected, uint8_t actual, const char* location);
extern void utest_assert_uint32(uint32_t expected, uint32_t actual, const char* location);
extern void utest_assert_int32(int32_t expected, int32_t actual, const char* location);
extern void utest_assert_string(char* expected, char* actual, const char* location);

#endif
