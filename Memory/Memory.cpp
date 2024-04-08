#include "Memory.h"

#ifdef USING_DMA
VMM_HANDLE Memory::hVMM;
#else
HANDLE Memory::hProc;
#endif
proc Memory::currentProc{};

bool Memory::Init()
{
#ifdef USING_DMA
    LPSTR args[] = {(LPSTR) "", (LPSTR) "-device", (LPSTR) "FPGA"};
    hVMM = VMMDLL_Initialize(3, args);
    if (!hVMM)
    {
        std::cout << "Failed to init VMM!" << std::endl;
        return false;
    }
#endif

    return true;
}
void Memory::Exit()
{
#ifdef USING_DMA
    VMMDLL_Close(hVMM);
#endif
}

bool Memory::OpenProc(proc p)
{
#ifndef USING_DMA
    HANDLE temp = OpenProcess(PROCESS_ALL_ACCESS, NULL, p.pid);
    if (temp == INVALID_HANDLE_VALUE)
    {
        return false;
    }
    hProc = temp;
#endif
    currentProc = p;

    return true;
}

std::vector<procModule> Memory::GetMods()
{
    std::vector<procModule> mods;
#ifdef USING_DMA
    PVMMDLL_MAP_MODULE pModuleMap = NULL;
    VMMDLL_Map_GetModuleU(hVMM, currentProc.pid, &pModuleMap, 0);

    for (int i = 0; i < pModuleMap->cMap; i++)
    {
        mods.push_back({ std::string(pModuleMap->pMap[i].uszText), pModuleMap->pMap[i].vaBase });
    }
    VMMDLL_MemFree(pModuleMap);
    pModuleMap = NULL;
#else
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, currentProc.pid);
    if (hSnap == INVALID_HANDLE_VALUE) return mods;

    MODULEENTRY32 entry{};
    entry.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnap, &entry))
    {
        do {
            procModule m{};
            m.address = (uintptr_t)entry.modBaseAddr;
            m.size = entry.modBaseSize;

            size_t i;
            char temp[MAX_PATH];
            wcstombs_s(&i, temp, entry.szModule, 256);

            m.name = temp;

            mods.push_back(m);
        } while (Module32Next(hSnap, &entry));
    }
#endif

        return mods;
}

std::vector<proc> Memory::GetProcs()
{
    std::vector<proc> procs;
#ifdef USING_DMA
    PVMMDLL_PROCESS_INFORMATION pdata = 0;
    DWORD pword = 0;

    VMMDLL_ProcessGetInformationAll(hVMM, &pdata, &pword);

    for (int i = 0; i < pword; i++)
    {
        procs.push_back({ std::string(pdata[i].szName), pdata[i].dwPID });
    }

    VMMDLL_MemFree(pdata);
#else

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 entry{};
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &entry))
    {
        do {
            proc p{};
            p.pid = entry.th32ProcessID;

            size_t i;
            char temp[MAX_PATH];
            wcstombs_s(&i, temp, entry.szExeFile, MAX_PATH);


            procs.push_back({ temp, p.pid });
        } while (Process32Next(hSnap, &entry));
    }
#endif
    return procs;
}


std::vector<byte> Memory::ReadMemory(uintptr_t address, DWORD size)
{
    std::vector<byte> bytes;
    bytes.resize(size);
#ifdef USING_DMA
    VMMDLL_MemReadEx(hVMM, currentProc.pid, address, bytes.data(), size, 0, VMMDLL_FLAG_NOCACHE);
#else
    ReadProcessMemory(hProc, (LPCVOID)address, bytes.data(), size, nullptr);
#endif

    return bytes;
}
