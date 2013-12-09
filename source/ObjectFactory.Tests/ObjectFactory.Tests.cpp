#include "stdafx.h"

#include <tchar.h>

int _tmain(int argc, TCHAR *argv[])
{
	::testing::InitGoogleTest(&argc, argv);

	::testing::GTEST_FLAG(shuffle) = true;

	static const TCHAR PAUSE[] = _T("-pause");

	bool pause = false;

	for (int i = 1; i < argc; i++)
	{
		if (::_tcsicmp(argv[i], PAUSE) == 0)
		{
			pause = true;
		}
	}

	RUN_ALL_TESTS();

	if (pause == true)
	{
		::_tprintf_s(_T("Please press any key to continue."));
		unsigned short c = ::_gettch();

		c;
	}

	return 0;
}
