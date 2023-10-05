/*
MIT License
Death Machine Game Engine
Copyright (c) 2023 graveman82

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#ifndef DM_ERRORDEFS_H_INCL
#define DM_ERRORDEFS_H_INCL

#include "platform/DmPlatform.h"

class DmResult
{
public:
	enum ErrorCodes
	{
		kEC_Unk,
		kEC_Ok,
		kEC_InvalidArg,
		kEC_NoMem

	};
	
	enum ErrorSources
	{
		kES_Undefined,
		kES_Container
	};

	enum ErrorFlags
	{
		kEF_HasValuePtr = (1 << 0)
	};

	DmResult(ErrorCodes errorCode, ErrorSources source = kES_Undefined, DmUInt8 flags = 0U)
		: m_errorCode((DmUInt16)errorCode)
		, m_source((DmUInt8)source)
		, m_flags(flags)
	{
	}

	
	DmUInt16 m_errorCode;
	DmUInt8 m_source;
	DmUInt8 m_flags;
};

inline DmResult DmOkResult() { return DmResult(DmResult::kEC_Ok); }
inline DmResult DmUnkError() { return DmResult(DmResult::kEC_Unk); }
 
DM_API DmResult __cdecl DmAssertOut(const char* filename, DmUInt32 nLine, const char* msg = kDmNullPtr);
#endif // DM_ERRORDEFS_H_INCL