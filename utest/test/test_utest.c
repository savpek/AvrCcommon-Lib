/* These tests are only for visual inspection.
 * Goal is keep utest framework as simple as possible,
 * theres some stuff needed to make. */
#include "./utest/public/utest.h"

/*! @brief Set-up test group for: utest
 *	@param Group name */
TEST_GROUP(utest);

/*! @brief Group setup function..
 *	@param Group name */
TEST_SETUP(utest) {

}

/*! @brief Group teardown function..
 *	@param Group name */
TEST_TEAR_DOWN(utest) {

}

TEST(utest, all_asserts_should_fail) {
	TEST_ASSERT(0);
	TEST_ASSERT_EQUAL_UINT8(100, 12);
	TEST_ASSERT_EQUAL_UINT32(10000, 12);
	TEST_ASSERT_EQUAL_INT32(-10000, 10000);
	TEST_ASSERT_EQUAL_INT8(-100, 100);
	TEST_ASSERT_EQUAL_STRING("ab", "ii");
}

TEST(utest, all_asserts_should_pass) {
	TEST_ASSERT(1);
	TEST_ASSERT_EQUAL_UINT8(100, 100);
	TEST_ASSERT_EQUAL_UINT32(10000, 10000);
	TEST_ASSERT_EQUAL_INT32(-10000, -10000);
	TEST_ASSERT_EQUAL_INT8(-100, -100);
	TEST_ASSERT_EQUAL_STRING("ab", "ab");
}

/*	@brief Set up all runnable tests from this module.
 *	@param group name.*/
TEST_GROUP_RUNNER(utest) {
	RUN_TEST_CASE(utest, all_asserts_should_pass);
	RUN_TEST_CASE(utest, all_asserts_should_fail);
}