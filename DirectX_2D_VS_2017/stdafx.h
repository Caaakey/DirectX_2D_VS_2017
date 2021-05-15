#pragma once
#if (_MSC_VER >= 1915)
#define no_init_all deprecated
#endif
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// C 런타임 헤더 파일입니다.
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
#pragma comment(lib, "VLD/vld.lib")
#include <VLD/vld.h>
#include <comdef.h>

#define HResult(hr)										\
{														\
	HRESULT hResult = (HRESULT)hr;						\
	if (FAILED(hResult)) {								\
		std::wstring filePath = __FILEW__;				\
		filePath = filePath.substr(filePath.find_last_of(L"/\\") + 1);	\
		wprintf(L"[%ls\t:\t%d]", filePath.c_str(), __LINE__);			\
		_com_error err(hr);												\
		MessageBox(nullptr, err.ErrorMessage(), L"Error", MB_OK);		\
		return hr;														\
}	}

#define HThrow(hr)										\
{														\
	HRESULT hResult = (HRESULT)hr;						\
	if (FAILED(hResult)) {								\
		std::wstring filePath = __FILEW__;				\
		filePath = filePath.substr(filePath.find_last_of(L"/\\") + 1);	\
		wprintf(L"[%ls\t:\t%d]", filePath.c_str(), __LINE__);			\
		_com_error err(hr);												\
		MessageBox(nullptr, err.ErrorMessage(), L"Error", MB_OK);		\
		throw hr;														\
}	}																	\

extern TCHAR* FORMAT_MESSAGE(DWORD err)
{
	TCHAR* msg = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		nullptr,
		err,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(TCHAR*)&msg,
		0,
		nullptr);

	return msg;
}

#else
#define HResult(hr) (hr)
#define HThrow(hr) { if (FAILED(hr)) throw hr; }
extern TCHAR* FORMAT_MESSAGE(DWORD err) { return nullptr; }
#endif

#include "Utility/StringUtility.h"
#include "Utility/FileUtility.h"

#include "Utility/Headers.h"
