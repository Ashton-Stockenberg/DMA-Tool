#include "Memory.h"

proc Memory::currentProc{};
HANDLE Memory::hProc;
uintptr_t Memory::readLocation;

bool Memory::Init()
{
    return true;
}
std::vector<proc> Memory::GetProcs()
{
    std::vector<proc> procs;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32 entry{};
    entry.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hSnap, &entry))
    {
        do {
            proc p{};
            p.pid = entry.th32ProcessID;

            size_t i;
            wcstombs_s(&i, p.name, entry.szExeFile, MAX_PATH);
            
            procs.push_back(p);
        } while (Process32Next(hSnap, &entry));
    }

    return procs;
}
bool Memory::OpenProc(proc p)
{
    hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, p.pid);
    if (hProc == INVALID_HANDLE_VALUE) return false;
    currentProc = p;
    return true;
}
std::vector<procModule> Memory::GetMods()
{
    std::vector<procModule> mods;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, currentProc.pid);
    if (hSnap == INVALID_HANDLE_VALUE)
    {
        return mods;
    }

    MODULEENTRY32 entry{};
    entry.dwSize = sizeof(MODULEENTRY32);

    if (Module32First(hSnap, &entry))
    {
        do {
            procModule m{};
            m.address = (uintptr_t)entry.modBaseAddr;
            m.size = entry.modBaseSize;

            size_t i;
            wcstombs_s(&i, m.name, entry.szModule, 256);

            mods.push_back(m);
        } while (Module32Next(hSnap, &entry));
    }

    return mods;
}
std::vector<byte> Memory::ReadMemory(uintptr_t address, DWORD size)
{
    std::vector<byte> bytes;
    if (hProc == INVALID_HANDLE_VALUE || hProc == NULL) return bytes;
    
    bytes.resize(size);
    ReadProcessMemory(hProc, (LPVOID)address, bytes.data(), size, nullptr);
    
    return bytes;
}
