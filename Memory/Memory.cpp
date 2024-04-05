#include "Memory.h"

VMM_HANDLE Memory::hVMM;
DWORD Memory::pid;
proc Memory::currentProc{};
procModule Memory::currentMod{};
uintptr_t Memory::readLocation;

bool Memory::Init()
{
    LPSTR args[] = {(LPSTR) "", (LPSTR) "-device", (LPSTR) "FPGA"};
    hVMM = VMMDLL_Initialize(3, args);
    if (!hVMM)
    {
        std::cout << "Failed to init VMM!" << std::endl;
        return false;
    }

    return true;
}
void Memory::Exit()
{
    VMMDLL_Close(hVMM);
}

std::vector<proc> Memory::GetProcs()
{
    std::vector<proc> procs;

    PVMMDLL_PROCESS_INFORMATION pdata = 0;
    DWORD pword = 0;

    VMMDLL_ProcessGetInformationAll(hVMM, &pdata, &pword);

    for (int i = 0; i < pword; i++)
    {
        procs.push_back({std::string(pdata[i].szName), pdata[i].dwPID});
    }

    VMMDLL_MemFree(pdata);

    return procs;
}
bool Memory::OpenProc(proc p)
{
    if (!VMMDLL_PidGetFromName(hVMM, (LPSTR)p.name.c_str(), &pid))
    {
        std::cout << "Failed to get pid!" << std::endl;
        return false;
    }

    currentProc = p;

    return true;
}
std::vector<procModule> Memory::GetMods()
{
    std::vector<procModule> mods;

    PVMMDLL_MAP_MODULE pModuleMap = NULL;
    VMMDLL_Map_GetModuleU(hVMM, pid, &pModuleMap, 0);

    for (int i = 0; i < pModuleMap->cMap; i++)
    {
        mods.push_back({std::string(pModuleMap->pMap[i].uszText), pModuleMap->pMap[i].vaBase});
    }
    VMMDLL_MemFree(pModuleMap);
    pModuleMap = NULL;

    return mods;
}
std::vector<byte> Memory::ReadMemory(uintptr_t address, DWORD size)
{
    std::vector<byte> bytes;
    bytes.resize(size);

    VMMDLL_MemReadEx(hVMM, pid, address, bytes.data(), size, 0, VMMDLL_FLAG_NOCACHE);

    return bytes;
}
