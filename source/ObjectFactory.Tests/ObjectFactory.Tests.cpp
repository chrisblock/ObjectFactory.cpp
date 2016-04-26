#include "stdafx.h"

#include <conio.h>
#include <tchar.h>

int _tmain(int argc, TCHAR *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	::testing::GTEST_FLAG(shuffle) = true;

	RUN_ALL_TESTS();

#ifdef _DEBUG
	if (::_isatty(::_fileno(stdin)) != 0)
	{
		::_tprintf(_T("Press any key to continue."));

		std::int32_t result = ::_getch();

		result;
	}
#endif

	return EXIT_SUCCESS;
}
