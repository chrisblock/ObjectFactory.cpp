#include "stdafx.h"

#include <tchar.h>

int _tmain(int argc, TCHAR *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	::testing::GTEST_FLAG(shuffle) = true;

	RUN_ALL_TESTS();

	return EXIT_SUCCESS;
}
