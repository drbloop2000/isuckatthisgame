#pragma once
#include <stdint.h>
namespace Memory {
	namespace Offsets {
		static constexpr uintptr_t game_local = 0x3C7CD40;
		static constexpr uintptr_t player = 0x6100;
		static constexpr uintptr_t health_structure = 0x23CD0;
		static constexpr uintptr_t current_health = 0x10;
		static constexpr uintptr_t max_health = 0x18;
	}
	template<typename T>
	bool write_memory(void* process_handle, void* address, void* memory_buffer);
	template<typename T>
	bool read_memory(void* process_handle, void* address, void* memory_buffer);
	extern int pid;
	bool init(void);
}
