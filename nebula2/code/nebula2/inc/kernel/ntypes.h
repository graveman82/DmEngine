#ifndef N_TYPES_H
#define N_TYPES_H
//------------------------------------------------------------------------------
/**
    Lowlevel Nebula defines.

    (C) 2002 RadonLabs GmbH

        - 18-Dec-22     mrsung  added fixed size integer types;
                                removed shortcuts for unsigneds;
                                va_copy if less VC 2013;
                                don't use NULL but in Win32API calls (so, it must be defined in windows.h etc)

    Modifications: (C) 2001 Marat Sungatullin
*/
#ifndef __XBxX__
#include <cstdint>
#include <errno.h>
#include <stdio.h>
#include <new>
#endif

#include "kernel/nsystem.h"
#include "kernel/ndebug.h"
#include "kernel/ndefclass.h"

// fixed size integer types
typedef std::int8_t nInt8;
typedef std::int16_t nInt16;
typedef std::int32_t nInt32;
typedef std::int64_t nInt64;

typedef std::uint8_t nUInt8;
typedef std::uint16_t nUInt16;
typedef std::uint32_t nUInt32;
typedef std::uint64_t nInt64;

// Shortcut Typedefs
typedef float float2[2];
typedef float float3[3];
typedef float float4[4];

struct nFloat4
{
    float x;
    float y;
    float z;
    float w;
};

struct nFloat3
{
    float x;
    float y;
    float z;
};

struct nFloat2
{
    float x;
    float y;
};
/**
    An nFourCC is usually represented in textual form in the source code
    as a character constant comprised of 4 characters:

    @verbatim
    'HELO'@endverbatim

    These four characters are interpreted as an integer value, making
    comparisons much faster than using a string identifier, while
    retaining, roughly, the readability of a string.

    These are used in the script interface when defining a script
    command via nClass::AddCmd(), as well as identifiers in the
    nVariableServer (and related nVariableContext and nVariable)
    classes.
*/
typedef unsigned int nFourCC;
typedef double nTime;

#if _HAS_CXX17 == 0
#error "This library needs at least a C++11 compliant compiler"
#endif

#define N_NULLHANDLE (0L)

//------------------------------------------------------------------------------
#define N_MAXPATH (512)     // maximum length for complete path
#define N_MAXNAMELEN (128)   // maximum length for single path component

//------------------------------------------------------------------------------
#define nID(a, b, c, d) ((a << 24) | (b << 16) | (c << 8) | (d))
#define MAKE_FOURCC(c0, c1, c2, c3) ((c0) | (c1 << 8) | (c2 << 16) | (c3 << 24))
#define FOURCC(i) (((i & 0xff000000) >> 24) | ((i & 0x00ff0000) >> 8) | ((i & 0x0000ff00) << 8) | ((i & 0x000000ff) << 24))
#define N_WHITESPACE " \r\n\t"

#if defined(__LINUX__) || defined(__MACOSX__)
#define n_stricmp strcasecmp
#else
#define n_stricmp stricmp
#endif

#ifdef N_OS_WIN32
#define snprintf _snprintf
#define vsnprintf _vsnprintf
#endif

#if defined (_MSC_VER) && (_MSC_VER < 1800)
#define va_copy(d, s) d = s
#endif

#ifdef __GNUC__
// Hey! Look! A cute GNU C++ extension!
#define min(a, b)   a <? b
#define max(a, b)   a >? b
#endif

// maps unsigned 8 bits/channel to D3DCOLOR
#define N_ARGB(a, r, g, b) ((nUInt32)((((a)&0xff) << 24) | (((r)&0xff) << 16) | (((g)&0xff) << 8) | ((b)&0xff)))
#define N_RGBA(r, g, b, a) N_ARGB(a, r, g, b)
#define N_XRGB(r, g, b)   N_ARGB(0xff, r, g, b)
#define N_COLORVALUE(r, g, b, a) N_RGBA((nUInt32)((r)*255.f), (nUInt32)((g)*255.f), (nUInt32)((b)*255.f), (nUInt32)((a)*255.f))

//------------------------------------------------------------------------------
//  public kernel C functions
//------------------------------------------------------------------------------
void __cdecl n_printf(const char*, ...)
    __attribute__((format(printf, 1, 2)));
void __cdecl n_error(const char*, ...)
    __attribute__((noreturn))
    __attribute__((format(printf, 1, 2)));
void __cdecl n_message(const char*, ...)
    __attribute__((format(printf, 1, 2)));
void __cdecl n_dbgout(const char*, ...)
    __attribute__((format(printf, 1, 2)));
void n_sleep(double);
char* n_strdup(const char*);
char* n_strncpy2(char*, const char*, size_t);
bool n_strmatch(const char*, const char*);
void n_strcat(char*, const char*, size_t);

void n_barf(const char*, const char*, int)
    __attribute__((noreturn));
void n_barf2(const char*, const char*, const char*, int)
    __attribute__((noreturn));

void* n_dllopen(const char*);
void  n_dllclose(void*);
void* n_dllsymbol(void*, const char*);

nFourCC n_strtofourcc(const char*);
const char* n_fourcctostr(nFourCC);

//------------------------------------------------------------------------------
//  Nebula memory management and debugging stuff.
//------------------------------------------------------------------------------
extern bool nMemoryLoggingEnabled;
struct nMemoryStats
{
    int highWaterSize;      // max allocated size so far
    int totalCount;         // total number of allocations
    int totalSize;          // current allocated size
};

int n_dbgmemdumpleaks();
void n_dbgmeminit();                // initialize memory debugging system
nMemoryStats n_dbgmemgetstats();    // defined in ndbgalloc.cc

#ifdef new
#undef new
#endif

#ifdef delete
#undef delete
#endif

// implemented in ndbgalloc.cc
void* operator new(size_t size);
void* operator new(size_t size, const char* file, int line);
void* operator new(size_t size, void* place, const char* file, int line);
void* operator new[](size_t size);
void* operator new[](size_t size, const char* file, int line);
void operator delete(void* p);
void operator delete(void* p, const char* file, int line);
void operator delete(void*, void*, const char* file, int line);
void operator delete[](void* p);
void operator delete[](void* p, const char* file, int line);
void* n_malloc_dbg(size_t size, const char* file, int line);
void* n_calloc_dbg(size_t num, size_t size, const char* file, int line);
void* n_realloc_dbg(void* memblock, size_t size, const char* file, int line);
void n_free_dbg(void* memblock, const char* file, int line);

#if defined(_DEBUG) && defined(__WIN32__)
#define n_new(type) new(__FILE__,__LINE__) type
#define n_placement_new(place, type) new(place, __FILE__,__LINE__) type
#define n_new_array(type,size) new(__FILE__,__LINE__) type[size]
#define n_delete(ptr) delete ptr
#define n_delete_array(ptr) delete[] ptr
#define n_malloc(size) n_malloc_dbg(size, __FILE__, __LINE__)
#define n_calloc(num, size) n_calloc_dbg(num, size, __FILE__, __LINE__)
#define n_realloc(memblock, size) n_realloc_dbg(memblock, size, __FILE__, __LINE__)
#define n_free(memblock) n_free_dbg(memblock, __FILE__, __LINE__)
#else
#define n_new(type) new type
#define n_placement_new(place, type) new(place) type
#define n_new_array(type,size) new type[size]
#define n_delete(ptr) delete ptr
#define n_delete_array(ptr) delete[] ptr
#define n_malloc(size) malloc(size)
#define n_calloc(num, size) calloc(num, size)
#define n_realloc(memblock, size) realloc(memblock, size)
#define n_free(memblock) free(memblock)
#endif

// define an nAttribute C++ class extension, declares
// a function member, setter and getter method for the attribute
// #define __ref_attr(TYPE,NAME) private: TYPE NAME; public: void Set##NAME(const TYPE& t) {this->NAME = t; }; const TYPE& Get##NAME() const { return this->NAME; };
// #define __attr(TYPE,NAME)     private: TYPE NAME; public: void Set##NAME(TYPE t) {this->NAME = t}; TYPE Get##NAME() const { return this->NAME; };

#define nSetter(METHOD, TYPE, MEMBER) inline void METHOD(TYPE t) { this->MEMBER = t; }
#define nGetter(TYPE, METHOD, MEMBER) inline TYPE METHOD() const { return this->MEMBER; }

//--------------------------------------------------------------------
#endif
