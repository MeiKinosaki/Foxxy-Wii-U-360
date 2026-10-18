#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>
namespace foxxy_wiiu360 {
struct MemoryRegionInfo { std::uint32_t base=0; std::size_t size=0; bool readable=true; bool writable=true; };
class MemoryBus {
public:
 explicit MemoryBus(std::size_t size=2*1024*1024);
 bool mapRegion(std::uint32_t base,std::size_t size,bool readable=true,bool writable=true);
 bool read8(std::uint32_t address,std::uint8_t& value) const;
 bool read16be(std::uint32_t address,std::uint16_t& value) const;
 bool read32be(std::uint32_t address,std::uint32_t& value) const;
 bool write8(std::uint32_t address,std::uint8_t value);
 bool write16be(std::uint32_t address,std::uint16_t value);
 bool write32be(std::uint32_t address,std::uint32_t value);
 bool loadImage(std::uint32_t address,const std::vector<std::uint8_t>& image);
 std::size_t size() const noexcept;
 std::vector<MemoryRegionInfo> regions() const;
 void clear(std::uint8_t value=0);
private:
 struct Region { MemoryRegionInfo info; std::vector<std::uint8_t> bytes; };
 const Region* findRegion(std::uint32_t address,std::size_t width,bool write) const;
 Region* findRegion(std::uint32_t address,std::size_t width,bool write);
 std::vector<Region> regions_;
};
}
