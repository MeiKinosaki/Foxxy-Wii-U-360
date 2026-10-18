#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
namespace foxxy_wiiu360 {
class MemoryBus {
public:
 explicit MemoryBus(std::size_t size = 2 * 1024 * 1024);
 bool read8(std::uint32_t address, std::uint8_t& value) const;
 bool read32be(std::uint32_t address, std::uint32_t& value) const;
 bool write8(std::uint32_t address, std::uint8_t value);
 bool write32be(std::uint32_t address, std::uint32_t value);
 std::size_t size() const noexcept { return memory_.size(); }
 void clear(std::uint8_t value = 0);
private:
 std::vector<std::uint8_t> memory_;
};
}
