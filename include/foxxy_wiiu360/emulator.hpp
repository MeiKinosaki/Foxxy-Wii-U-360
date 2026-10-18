#pragma once
#include "foxxy_wiiu360/memory_bus.hpp"
#include <array>
#include <cstdint>
namespace foxxy_wiiu360 {
struct CpuState {
 std::array<std::uint32_t, 32> gpr{};
 std::uint32_t pc = 0;
 std::uint32_t lr = 0;
 std::uint32_t ctr = 0;
 std::uint32_t cr = 0;
 std::uint32_t xer = 0;
 bool halted = false;
};
class Emulator {
public:
 explicit Emulator(std::size_t memory_size = 2 * 1024 * 1024);
 MemoryBus& bus() noexcept { return bus_; }
 const MemoryBus& bus() const noexcept { return bus_; }
 CpuState& cpu() noexcept { return cpu_; }
 const CpuState& cpu() const noexcept { return cpu_; }
 // v0.1b is a validated foundation only; no PowerPC instruction executes yet.
 bool step();
private:
 MemoryBus bus_;
 CpuState cpu_{};
};
}
