#pragma once
//#define USING_DMA

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

public:
	static proc currentProc;
	static bool Init();
	static void Exit();
	static bool OpenProc(proc p);
	static std::vector<proc> GetProcs();
	static std::vector<procModule> GetMods();
	static std::vector<byte> ReadMemory(uintptr_t address, DWORD size);
};