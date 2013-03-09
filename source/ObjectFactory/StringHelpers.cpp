#include "stdafx.h"

#include "StringHelpers.h"

basic_string<CHAR> ConvertWideToMultiByte(LPCWSTR wideString)
{
	auto length = ::wcslen(wideString) + 1;

	unique_ptr<CHAR[]> str(new CHAR[length]);

	::WideCharToMultiByte(CP_ACP, 0, wideString, -1, str.get(), length, NULL, NULL);

	basic_string<CHAR> result(str.get());

	return result;
}

basic_string<WCHAR> ConvertMultiByteToWide(LPCSTR multiByteString)
{
	auto length = ::strlen(multiByteString) + 1;

	unique_ptr<WCHAR[]> str(new WCHAR[length]);

	::MultiByteToWideChar(CP_ACP, 0, multiByteString, -1, str.get(), length);

	basic_string<WCHAR> result(str.get());

	return result;
}

basic_string<CHAR> ConvertToAString(LPCSTR str)
{
	basic_string<CHAR> result(str);

	return result;
}

basic_string<CHAR> ConvertToAString(LPCWSTR str)
{
	basic_string<CHAR> result = ::ConvertWideToMultiByte(str);

	return result;
}

basic_string<WCHAR> ConvertToWString(LPCSTR str)
{
	basic_string<WCHAR> result = ::ConvertMultiByteToWide(str);

	return result;
}

basic_string<WCHAR> ConvertToWString(LPCWSTR str)
{
	basic_string<WCHAR> result(str);

	return result;
}
