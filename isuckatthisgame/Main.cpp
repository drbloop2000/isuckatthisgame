#include <Windows.h>
#include "Memory.hpp"
#include <stdio.h>
#include <Psapi.h>
int main(void) {
	const bool did_init = Memory::init();
	if (!did_init) {
		printf("%s\n", "Failed to init");
		return -1;
	}
	printf("Current PID: %d\n", Memory::pid);
	HANDLE process_handle = OpenProcess(PROCESS_ALL_ACCESS, false, Memory::pid);
	if (!process_handle) {
		printf("%s\n", "Failed to create handle");
		return -1;
	}

	HMODULE module = nullptr;
	DWORD d = 0;
	uintptr_t game = 0;
	uintptr_t player = 0;
	const size_t module_size = sizeof(module);
	if (!K32EnumProcessModules(process_handle, &module, module_size, &d) || !Memory::read_memory<uintptr_t>(process_handle, reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(module) + Memory::Offsets::game_local), &game) || !game || !Memory::read_memory<uintptr_t>(process_handle, reinterpret_cast<void*>(game + Memory::Offsets::player), &player) || !player) {
		CloseHandle(process_handle);
		return -1;
	}
	float health = 9999.0f;
	void* address = reinterpret_cast<void*>(player + Memory::Offsets::health_structure + Memory::Offsets::current_health);
	if (!Memory::write_memory<float>(process_handle, address, &health)) {
		CloseHandle(process_handle);
		return -1;
	}
	CloseHandle(process_handle);
	printf("%s\n", "u should have inf health now");
}
