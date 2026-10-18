#include "Memory.hpp"
#include "Windows.h"
#include <stdio.h>
#include <string>
#include <array>
#include <cstdio>
#include <TlHelp32.h>
//#include "task"
using namespace std;
#define PROCESS_NAME L"NewColossus_x64vk.exe"
static int get_pid_from_name(const wchar_t* name) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot == INVALID_HANDLE_VALUE)
        return -1;

    PROCESSENTRY32W entry{};
    entry.dwSize = sizeof(entry);

    int pid = -1;

    if (Process32FirstW(snapshot, &entry)) {
        do {
            if (_wcsicmp(entry.szExeFile, name) == 0) {
                pid = static_cast<int>(entry.th32ProcessID);
                break;
            }
        } while (Process32NextW(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return pid;
}

namespace Memory {
    int Memory::pid = -1;
    template<typename T>
    bool write_memory(void* process_handle, void* address, void* memory_buffer) {
        //WriteProcessMemory()
        return WriteProcessMemory(process_handle, address, memory_buffer, sizeof(T), nullptr) != 0;
    }
    template bool write_memory<float>(void* process_handle, void* address, void* memory_buffer);
    template<typename T>
    bool read_memory(void* process_handle, void* address, void* memory_buffer) {
        return ReadProcessMemory(process_handle, address, memory_buffer, sizeof(T), nullptr) != 0;
    }
    template bool read_memory<float>(void* process_handle, void* address, void* memory_buffer);
    template bool read_memory<uintptr_t>(void* process_handle, void* address, void* memory_buffer);
	bool init(void) {
        printf("%s\n", "we init");
		int pid = get_pid_from_name(PROCESS_NAME);
        printf("%d\n", pid);
		if (pid == -1) {
			return false;
		}
        Memory::pid = pid;
		return true;
	}
}
