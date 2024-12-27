#pragma once
#ifdef ARC_TRACK_MEMORY

#include <memory>

struct SMemoryData
{
	void* pMemory = nullptr;
	size_t m_uSize = 0;
	const char* m_pFile = nullptr;
	int m_iLine = -1;
};

extern int g_iTotalAllocs;
extern int g_iInitialAllocs; // Allocs before creating the app
extern int g_iFinalAllocs; // Allocs after deleting the app
extern size_t g_uTotalBytes;
extern size_t g_uInitialBytes;
extern size_t g_uFinalBytes;

extern std::map<void*, SMemoryData> g_mMemoryData;

inline void* operator new(size_t _uSize)
{
	g_iTotalAllocs++;
	return malloc(_uSize);

	// TODO: I can't do this because of the creation of g_mMemoryData itself. Call other new function or something.
	//void* pMemory = malloc(_uSize);
	//g_iTotalAllocs++;
	//g_uTotalBytes += _uSize;
	//SMemoryData& oMemoryData = g_mMemoryData[pMemory];
	//oMemoryData.pMemory = pMemory;
	//oMemoryData.m_uSize = _uSize;
	//return pMemory;
}

inline void operator delete(void* _p)
{
	if (_p)
	{
		g_iTotalAllocs--;

		// TODO: Hack to avoid going through here in the deletion of the g_mMemoryData itself. I don't feel great with this. Call other delete function or something.
		if (g_mMemoryData.size() > 0 && g_mMemoryData.size() != (g_iFinalAllocs - g_iInitialAllocs))
		{
			auto it = g_mMemoryData.find(_p);
			if (it != g_mMemoryData.end())
			{
				g_uTotalBytes -= ((SMemoryData)((*it).second)).m_uSize;
				g_mMemoryData.erase(it);
			}
		}
		
		free(_p);
	}
}

inline void* operator new[](size_t _uSize)
{
	g_iTotalAllocs++;
	return malloc(_uSize);

	// TODO: I can't do this because of the creation of g_mMemoryData itself. Call other new function or something.
	//void* pMemory = malloc(_uSize);
	//g_iTotalAllocs++;
	//g_uTotalBytes += _uSize;
	//SMemoryData& oMemoryData = g_mMemoryData[pMemory];
	//oMemoryData.pMemory = pMemory;
	//oMemoryData.m_uSize = _uSize;
	//return pMemory;
}

inline void operator delete[](void* _p)
{
	if (_p)
	{
		g_iTotalAllocs--;

		// TODO: Hack to avoid going through here in the deletion of the g_mMemoryData itself. I don't feel great with this. Call other delete function or something.
		if (g_mMemoryData.size() > 0 && g_mMemoryData.size() != (g_iFinalAllocs - g_iInitialAllocs))
		{
			auto it = g_mMemoryData.find(_p);
			if (it != g_mMemoryData.end())
			{
				g_uTotalBytes -= ((SMemoryData)((*it).second)).m_uSize;
				g_mMemoryData.erase(it);
			}
		}

		free(_p);
	}
}

inline void* operator new(size_t _uSize, const char* _sFile, int _iLine)
{
	void* pMemory = malloc(_uSize);

	g_iTotalAllocs++;
	g_uTotalBytes += _uSize;

	SMemoryData& oMemoryData = g_mMemoryData[pMemory];
	oMemoryData.pMemory = pMemory;
	oMemoryData.m_uSize = _uSize;
	oMemoryData.m_pFile = _sFile;
	oMemoryData.m_iLine = _iLine;

	return pMemory;
}

#define arcnew new(__FILE__, __LINE__)

#else

#define arcnew new

#endif