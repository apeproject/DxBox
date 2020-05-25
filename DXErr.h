#pragma once
#include "Win.h"
#include <sal.h>

extern "C" {
const WCHAR* WINAPI DXGetErrorStringW( _In_ HRESULT hr );
#define DXGetErrorString DXGetErrorStringW
void WINAPI DXGetErrorDescriptionW( _In_ HRESULT hr, _Out_cap_(count) WCHAR* desc, _In_ size_t count );
#define DXGetErrorDescription DXGetErrorDescriptionW
HRESULT WINAPI DXTraceW( _In_z_ const WCHAR* strFile, _In_ DWORD dwLine, _In_ HRESULT hr, _In_opt_ const WCHAR* strMsg, _In_ bool bPopMsgBox );
#define DXTrace DXTraceW
#if defined(DEBUG) || defined(_DEBUG)
#define DXTRACE_MSG(str)              DXTrace( __FILEW__, (DWORD)__LINE__, 0, str, false )
#define DXTRACE_ERR(str,hr)           DXTrace( __FILEW__, (DWORD)__LINE__, hr, str, false )
#define DXTRACE_ERR_MSGBOX(str,hr)    DXTrace( __FILEW__, (DWORD)__LINE__, hr, str, true )
#else
#define DXTRACE_MSG(str)              (0L)
#define DXTRACE_ERR(str,hr)           (hr)
#define DXTRACE_ERR_MSGBOX(str,hr)    (hr)
#endif
}