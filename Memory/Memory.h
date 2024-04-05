#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>
#include <leechcore.h>
#include <vmmdll.h>

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
	static VMM_HANDLE hVMM;
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