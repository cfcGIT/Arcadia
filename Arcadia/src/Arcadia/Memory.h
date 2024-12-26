#pragma once

#ifdef ARC_TRACK_MEMORY

#include <memory>

extern int g_iTotalAllocs;
extern int g_iInitialAllocs; // Allocs before creating the app
extern int g_iFinalAllocs; // Allocs after deleting the app


// TODO: Save size, file and line in a struct to better track the trace of a memory error

inline void* operator new(size_t _uSize)
{
	g_iTotalAllocs++;
	return malloc(_uSize);
}

inline void operator delete(void* _p)
{
	if (_p)
	{
		g_iTotalAllocs--;
		free(_p);
	}
}

inline void* operator new[](size_t _uSize)
{
	g_iTotalAllocs++;
	return malloc(_uSize);
}

inline void operator delete[](void* _p)
{
	if (_p)
	{
		g_iTotalAllocs--;
		free(_p);
	}
}

//inline void* operator new(size_t _uSize, const char* _sFile, int _iLine)
//{
//	// TODO: ... 
//	g_iTotalAllocs++;
//	return malloc(_uSize);
//}
//
//#define arcnew new(__FILE__, __LINE__)

#endif