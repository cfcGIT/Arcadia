#ifdef ARC_TRACK_MEMORY

#include "Arcadia/Memory.h"

int g_iTotalAllocs = 0;
int g_iInitialAllocs = 0;
int g_iFinalAllocs = 0;
size_t g_uTotalBytes = 0;
size_t g_uInitialBytes = 0;
size_t g_uFinalBytes = 0;

std::map<void*, SMemoryData> g_mMemoryData{};

#endif