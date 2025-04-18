#ifdef ARC_TRACK_MEMORY

bool g_bCountAllocs = false;
int g_iTotalAllocs = 0;
size_t g_uTotalBytes = 0;
SMemoryData g_tMemoryData[MAX_TRACK_ALLOCS] = {};

namespace Arcadia
{
    namespace Memory
    {
        /**
        * @brief Alloc new memory and track with size, file and line
        */
        void* Alloc(size_t _uSize, const char* _pFile, int _iLine)
        {
            void* pMemory = malloc(_uSize);
            if (g_bCountAllocs && g_iTotalAllocs < MAX_TRACK_ALLOCS)
            {
                g_uTotalBytes += _uSize;

                SMemoryData& oMemoryData = g_tMemoryData[g_iTotalAllocs];
                oMemoryData.pMemory = pMemory;
                oMemoryData.m_uSize = _uSize;
                oMemoryData.m_pFile = _pFile;
                oMemoryData.m_iLine = _iLine;

                g_iTotalAllocs++;

                if (PRINT_DEBUG)
                {
                    // fprintf to avoid indirect recursion. TODO: Change spdlog to another library that doesn't make new allocations.
                    fprintf(stdout, "[+] Alloc %zu from %s(%d). Total: %zu bytes in %d allocs\n", _uSize, _pFile, _iLine, g_uTotalBytes, g_iTotalAllocs);
                    //ARC_CORE_DEBUG("Alloc {0} from {1}({2}). Total: {3} bytes in {4} allocs.", _uSize, _pFile, _iLine, g_uTotalBytes, g_iTotalAllocs);
                }
            }
            return pMemory;
        }

        /**
        * @brief Alloc new memory and track with size
        */
        void* Alloc(size_t _uSize)
        {
            return Alloc(_uSize, "unknown", -1);
        }

        /**
        * @brief Free memory and untrack
        */
        void Free(void* _p)
        {
            if (_p)
            {
                if (g_bCountAllocs)
                {
                    for (int i = 0; i < g_iTotalAllocs; ++i)
                    {
                        if (g_tMemoryData[i].pMemory == _p)
                        {
                            g_iTotalAllocs--;
                            g_uTotalBytes -= g_tMemoryData[i].m_uSize;

                            if (PRINT_DEBUG)
                            {
                                // fprintf to avoid indirect recursion. TODO: Change spdlog to another library that doesn't make new allocations.
                                fprintf(stdout, "[-] Dealloc %zu from %s(%d). Total: %zu bytes in %d allocs.\n", g_tMemoryData[i].m_uSize, g_tMemoryData[i].m_pFile, g_tMemoryData[i].m_iLine, g_uTotalBytes, g_iTotalAllocs);
                                //ARC_CORE_DEBUG("Dealloc {0} from {1}({2}). Total: {3} bytes in {4} allocs.", g_tMemoryData[i].m_uSize, g_tMemoryData[i].m_pFile, g_tMemoryData[i].m_iLine, g_uTotalBytes, g_iTotalAllocs);
                            }

                            // Move all subsequent elements one position to the left
                            for (int j = i; j < g_iTotalAllocs; ++j)
                            {
                                g_tMemoryData[j] = g_tMemoryData[j + 1];
                            }
                            // Restore last element to default (to keep clean the elements we are not using)
                            g_tMemoryData[g_iTotalAllocs].m_uSize = 0;
                            g_tMemoryData[g_iTotalAllocs].m_pFile = "";
                            g_tMemoryData[g_iTotalAllocs].m_iLine = -1;


                            break;
                        }
                    }
                }
                free(_p);
            }
        }
    }
}


#endif