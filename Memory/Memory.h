#pragma once
#include "../defines.h"

#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>

#ifdef USING_DMA
#include <leechcore.h>
#include <vmmdll.h>
#endif

typedef struct proc
{
	std::string name;
	DWORD pid = 0;
};

typedef struct procModule
{
	std::string name;
	uintptr_t address;
	DWORD size;
};

class Memory
{

#ifdef USING_DMA
	static VMM_HANDLE hVMM;
#else
	static HANDLE hProc;
#endif
	static DWORD pid;

public:
	static proc currentProc;
	static procModule currentMod;
	static uintptr_t readLocation;
	static bool Init();
	static void Exit();
	static bool OpenProc(proc p);
	static std::vector<proc> GetProcs();
	static std::vector<procModule> GetMods();
	static std::vector<byte> ReadMemory(uintptr_t address, DWORD size);
};