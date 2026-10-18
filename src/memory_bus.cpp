#include "foxxy_wiiu360/memory_bus.hpp"
namespace foxxy_wiiu360 {
MemoryBus::MemoryBus(std::size_t size) : memory_(size, 0) {}
bool MemoryBus::read8(std::uint32_t a, std::uint8_t& v) const {
 if (static_cast<std::size_t>(a) >= memory_.size()) return false;
 v = memory_[a]; return true;
}
bool MemoryBus::read32be(std::uint32_t a, std::uint32_t& v) const {
 if (static_cast<std::size_t>(a) > memory_.size() || memory_.size() - a < 4) return false;
 v = (std::uint32_t(memory_[a]) << 24) | (std::uint32_t(memory_[a+1]) << 16) |
     (std::uint32_t(memory_[a+2]) << 8) | std::uint32_t(memory_[a+3]);
 return true;
}
bool MemoryBus::write8(std::uint32_t a, std::uint8_t v) {
 if (static_cast<std::size_t>(a) >= memory_.size()) return false;
 memory_[a] = v; return true;
}
bool MemoryBus::write32be(std::uint32_t a, std::uint32_t v) {
 if (static_cast<std::size_t>(a) > memory_.size() || memory_.size() - a < 4) return false;
 memory_[a] = std::uint8_t(v >> 24); memory_[a+1] = std::uint8_t(v >> 16);
 memory_[a+2] = std::uint8_t(v >> 8); memory_[a+3] = std::uint8_t(v);
 return true;
}
void MemoryBus::clear(std::uint8_t v) { for (auto& b : memory_) b = v; }
}
