#pragma once
#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// C ��Ÿ�� ��� �����Դϴ�.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <string>

#include <vector>
#include <map>

#define TO_STRING(str) #str;
#define SAFE_DELETE(p)			{ if(p) { delete (p); (p) = nullptr;} }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p); (p) = nullptr;} }
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p) = nullptr;} }

#if defined _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#pragma comment(lib, "VLD/lib/vld.lib")
#include <VLD/vld.h>

#define HResult(hr)										\
{														\
	if (FAILED((HRESULT)hr)) {							\
		std::wstring filePath = __FILEW__;				\
		filePath = filePath.substr(filePath.find_last_of(L"/\\") + 1);	\
		wprintf(L"[%ls\t:\t%d]", filePath.c_str(), __LINE__);			\
		LPWSTR str = nullptr;							\
		FormatMessage(									\
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,	\
			nullptr,													\
			hr,															\
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),					\
			str,														\
			0,															\
			nullptr);													\
			MessageBox(nullptr, str, L"Error", MB_OK);					\
		return hr;														\
}	}																	\

#define HThrow(hr)										\
{														\
	if (FAILED((HRESULT)hr)) {							\
		std::wstring filePath = __FILEW__;				\
		filePath = filePath.substr(filePath.find_last_of(L"/\\") + 1);	\
		wprintf(L"[%ls\t:\t%d]", filePath.c_str(), __LINE__);			\
		LPWSTR str = nullptr;							\
		FormatMessage(									\
			FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,	\
			nullptr,													\
			hr,															\
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),					\
			str,														\
			0,															\
			nullptr);													\
			MessageBox(nullptr, str, L"Error", MB_OK);					\
		throw hr;														\
}	}																	\

#else
#define HResult(hr) (hr)
#define HThrow(hr) { if (FAILED(hr)) throw hr; }
#endif

#include "Utility/DefineUtility.h"
