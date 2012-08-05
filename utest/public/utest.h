/*! @brief Unit test redirect header.
 *
 *	@file utest.h
 *  @author: savpek
 *
 *	This file redirects to Unity (with Unity_fixture additions.
 */

#ifndef UTEST_H_
#define UTEST_H_

#include "framework.h"

#ifndef UTEST_OUTPUT_CHAR
# error DEFINE UTEST_OUTPUT_CHAR(a) FUNCTION!
#endif

#include "utest/private/utest_asserts.h"
#include "utest/private/utest_template.h"

#endif /* UTEST_H_ */