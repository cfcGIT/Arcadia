#pragma once
#ifdef ARC_TRACK_MEMORY

#include <memory>

constexpr uint32_t MAX_TRACK_ALLOCS = 256;

/**
* @brief Struct with the data we want to save to track memory errors
*/
struct SMemoryData
{
    void* pMemory = nullptr;
    size_t m_uSize = 0;
    const char* m_pFile = "";
    int m_iLine = -1;
};

/**
* Global vars to track memory allocs
*/
extern bool g_bCountAllocs; // True if we want to track new allocs
extern int g_iTotalAllocs; // Total allocs count
extern size_t g_uTotalBytes; // Total bytes count
extern SMemoryData g_tMemoryData[MAX_TRACK_ALLOCS]; // Array with memory data tracked

namespace Arcadia
{
    namespace Memory
    {
        void* Alloc(size_t _uSize, const char* _pFile, int _iLine);
        void* Alloc(size_t _uSize);
        void Free(void* _p);
    }
}

/**
* Override of new and delete operators 
*/
inline void* operator new(size_t _uSize)
{
    return Arcadia::Memory::Alloc(_uSize);
}

inline void operator delete(void* _p)
{
    Arcadia::Memory::Free(_p);
}

inline void* operator new[](size_t _uSize)
{
    return Arcadia::Memory::Alloc(_uSize);
}

inline void operator delete[](void* _p)
{
    Arcadia::Memory::Free(_p);
}

/**
* Alloc with more info (file and line). Called by the macro arcnew
*/
inline void* operator new(size_t _uSize, const char* _pFile, int _iLine)
{
    return Arcadia::Memory::Alloc(_uSize, _pFile, _iLine);
}

#define arcnew new(__FILE__, __LINE__)

#else

#define arcnew new

#endif