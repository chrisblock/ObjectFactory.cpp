#pragma once

#include <tchar.h>

#include <string>

std::basic_string<CHAR> ConvertWideToMultiByte(LPCWSTR wideString);

std::basic_string<WCHAR> ConvertMultiByteToWide(LPCSTR multiByteString);

std::basic_string<CHAR> ConvertToAString(LPCSTR str);

std::basic_string<CHAR> ConvertToAString(LPCWSTR str);

std::basic_string<WCHAR> ConvertToWString(LPCSTR str);

std::basic_string<WCHAR> ConvertToWString(LPCWSTR str);

#ifdef UNICODE
#define ConvertToTString ConvertToWString
#else
#define ConvertToTString ConvertToAString
#endif
