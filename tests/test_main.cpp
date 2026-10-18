#include "foxxy_wiiu360/emulator.hpp"
#include <cstdlib>
#include <iostream>
using namespace foxxy_wiiu360;
static void check(bool condition, const char* message) {
 if (!condition) { std::cerr << "FAIL: " << message << '\n'; std::exit(1); }
}
int main() {
 MemoryBus bus(16);
 check(bus.write8(0, 0xAB), "write8 in bounds");
 std::uint8_t byte = 0;
 check(bus.read8(0, byte) && byte == 0xAB, "read8 round trip");
 check(bus.write32be(4, 0x12345678), "write32be in bounds");
 std::uint32_t word = 0;
 check(bus.read32be(4, word) && word == 0x12345678, "big endian round trip");
 check(!bus.read8(16, byte), "read out of bounds rejected");
 check(!bus.write8(16, 1), "write out of bounds rejected");
 check(!bus.read32be(14, word), "truncated read rejected");
 check(!bus.write32be(14, 0), "truncated write rejected");
 Emulator emu(64);
 check(emu.cpu().pc == 0 && !emu.cpu().halted, "CPU initial state");
 check(!emu.step(), "v0.1b does not claim instruction execution");
 std::cout << "All Foxxy-Wii-U-360 v0.1b tests passed.\n";
}
