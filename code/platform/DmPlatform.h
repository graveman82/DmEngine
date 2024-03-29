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
#ifndef DM_PLATFORM_H_INCL
#define DM_PLATFORM_H_INCL

#ifdef _WIN32
#	define  DM_WIN32
#elif defined _LINUX
#	define  DM_LINUX
#else
#	error "Unsupported Platform."
#endif

// Fixed size platform independent types to store integers.
typedef signed char DmInt8;
typedef short DmInt16;
typedef int DmInt32;

typedef unsigned char DmUInt8;
typedef unsigned short DmUInt16;
typedef unsigned int DmUInt32;

#define kDmNullPtr 0

// Export and import specifiers
#ifdef DM_WIN32

#	define  DM_DLL_EXPORT	__declspec( dllexport ) 
#	define  DM_DLL_IMPORT	__declspec( dllimport )

#elif defined DM_LINUX

#	define  DM_DLL_EXPORT
#	define  DM_DLL_IMPORT

#else
#	error "Unsupported Platform."
#endif

#ifdef DM_RND_EXE
#	define DM_API
#else
#	ifdef DM_EXPORTS
#		define DM_API DM_DLL_EXPORT
#	else
#		define DM_API DM_DLL_IMPORT
#	endif
#endif // DM_RND

#endif // DM_PLATFORM_H_INCL