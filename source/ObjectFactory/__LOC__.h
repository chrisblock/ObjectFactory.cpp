#pragma once

#define _STRINGIFY(x) #x
#define STRINGIFY(x) _STRINGIFY(x)

#define __FILE_A__ __FILE__
#define __FILE_W__ __FILEW__

#define __LINE_A__ STRINGIFY(__LINE__)
#define __LINE_W__ _STR2WSTR(__LINE_A__)

#define __LOC_A__ __FILE_A__ " (" __LINE_A__ "): "

#define __LOC_W__ __FILE_W__ L" (" __LINE_W__ L"): "

#ifdef UNICODE
	#define __LOC__ __LOC_W__
#else
	#define __LOC__ __LOC_A__
#endif
