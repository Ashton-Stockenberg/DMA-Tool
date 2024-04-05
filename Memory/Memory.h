#pragma once
#include <Windows.h>
#include <iostream>
#include <vector>
#include <TlHelp32.h>


typedef struct proc {
	char name[MAX_PATH];
	DWORD pid = 0;
};

typedef struct procModule {
	char name[256];
	uintptr_t address;
	DWORD size;
};

class Memory
{
	static HANDLE hProc;
public:
	static proc currentProc;
	static uintptr_t readLocation;
	static bool Init();
	static bool OpenProc(proc p);
	static std::vector<proc> GetProcs();
	static std::vector<procModule> GetMods();
	static std::vector<byte> ReadMemory(uintptr_t address, DWORD size);
};