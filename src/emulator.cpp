#include "foxxy_wiiu360/emulator.hpp"
namespace foxxy_wiiu360 {
Emulator::Emulator(std::size_t memory_size) : bus_(memory_size) {}
bool Emulator::step() { return false; }
}
