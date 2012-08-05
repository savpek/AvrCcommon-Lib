/* Thanks for original work: 2010 James Grenning. This file is mostly copied from
 * his wrapper for Unity framework. */

#ifndef UTEST_TEMPLATE_H_
#define UTEST_TEMPLATE_H_

#include "framework.h"

typedef void utest_function();

extern void utest_main(void (*utest_fixture)( void));

extern void utest_runner(utest_function * setup,
        utest_function * body,
        utest_function * teardown,
        const char * printableName,
        const char * file);

#define TEST_GROUP(group)\
    int TEST_GROUP_##group = 0

#define TEST_SETUP(group) void TEST_##group##_SETUP()

#define TEST_TEAR_DOWN(group) void TEST_##group##_TEAR_DOWN()


#define TEST(group, name) \
    void TEST_##group##_##name##_();\
    void TEST_##group##_##name##_run()\
    {\
        utest_runner(TEST_##group##_SETUP,\
             TEST_##group##_##name##_,\
            TEST_##group##_TEAR_DOWN,\
            "TEST(" #group ", " #name ")",\
            __FILE__);\
    }\
    void  TEST_##group##_##name##_()

#define DECLARE_TEST_CASE(group, name) \
    void TEST_##group##_##name##_run()

#define RUN_TEST_CASE(group, name) \
        DECLARE_TEST_CASE(group, name);\
    TEST_##group##_##name##_run();

#define TEST_GROUP_RUNNER(group)\
    void TEST_##group##_GROUP_RUNNER_runAll();\
    void TEST_##group##_GROUP_RUNNER()\
    {\
        TEST_##group##_GROUP_RUNNER_runAll();\
    }\
    void TEST_##group##_GROUP_RUNNER_runAll()

#define RUN_TEST_GROUP(group)\
    void TEST_##group##_GROUP_RUNNER();\
    TEST_##group##_GROUP_RUNNER();

#endif /* UNITY_FIXTURE_H_ */
