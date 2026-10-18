#include "foxxy_wiiu360/memory_bus.hpp"
#include <algorithm>
#include <limits>
#include <utility>

namespace foxxy_wiiu360 {
MemoryBus::MemoryBus(std::size_t n) {
 if (n) mapRegion(0, n);
}

bool MemoryBus::mapRegion(std::uint32_t base, std::size_t n, bool rd, bool wr) {
 if (!n || n > std::numeric_limits<std::uint32_t>::max() ||
     n - 1 > std::numeric_limits<std::uint32_t>::max() - base) return false;
 const std::uint64_t end = std::uint64_t(base) + n;
 for (const auto& r : regions_) {
  const std::uint64_t re = std::uint64_t(r.info.base) + r.info.size;
  if (std::uint64_t(base) < re && std::uint64_t(r.info.base) < end) return false;
 }
 Region r;
 r.info = {base, n, rd, wr};
 r.bytes.resize(n, 0);
 regions_.push_back(std::move(r));
 std::sort(regions_.begin(), regions_.end(),
           [](const Region& a, const Region& b) { return a.info.base < b.info.base; });
 return true;
}

const MemoryBus::Region* MemoryBus::findRegion(std::uint32_t a, std::size_t n, bool wr) const {
 if (!n || n - 1 > std::numeric_limits<std::uint32_t>::max() - a) return nullptr;
 const std::uint64_t end = std::uint64_t(a) + n;
 for (const auto& r : regions_) {
  const std::uint64_t re = std::uint64_t(r.info.base) + r.info.size;
  if (a >= r.info.base && end <= re && (wr ? r.info.writable : r.info.readable)) return &r;
 }
 return nullptr;
}

MemoryBus::Region* MemoryBus::findRegion(std::uint32_t a, std::size_t n, bool wr) {
 return const_cast<Region*>(static_cast<const MemoryBus*>(this)->findRegion(a, n, wr));
}

bool MemoryBus::read8(std::uint32_t a, std::uint8_t& v) const {
 const auto* r = findRegion(a, 1, false);
 if (!r) return false;
 v = r->bytes[a - r->info.base];
 return true;
}

bool MemoryBus::read16be(std::uint32_t a, std::uint16_t& v) const {
 const auto* r = findRegion(a, 2, false);
 if (!r) return false;
 const auto i = a - r->info.base;
 v = (std::uint16_t(r->bytes[i]) << 8) | std::uint16_t(r->bytes[i + 1]);
 return true;
}

bool MemoryBus::read32be(std::uint32_t a, std::uint32_t& v) const {
 const auto* r = findRegion(a, 4, false);
 if (!r) return false;
 const auto i = a - r->info.base;
 v = (std::uint32_t(r->bytes[i]) << 24) |
     (std::uint32_t(r->bytes[i + 1]) << 16) |
     (std::uint32_t(r->bytes[i + 2]) << 8) |
     std::uint32_t(r->bytes[i + 3]);
 return true;
}

bool MemoryBus::write8(std::uint32_t a, std::uint8_t v) {
 auto* r = findRegion(a, 1, true);
 if (!r) return false;
 r->bytes[a - r->info.base] = v;
 return true;
}

bool MemoryBus::write16be(std::uint32_t a, std::uint16_t v) {
 auto* r = findRegion(a, 2, true);
 if (!r) return false;
 const auto i = a - r->info.base;
 r->bytes[i] = std::uint8_t(v >> 8);
 r->bytes[i + 1] = std::uint8_t(v);
 return true;
}

bool MemoryBus::write32be(std::uint32_t a, std::uint32_t v) {
 auto* r = findRegion(a, 4, true);
 if (!r) return false;
 const auto i = a - r->info.base;
 r->bytes[i] = std::uint8_t(v >> 24);
 r->bytes[i + 1] = std::uint8_t(v >> 16);
 r->bytes[i + 2] = std::uint8_t(v >> 8);
 r->bytes[i + 3] = std::uint8_t(v);
 return true;
}

bool MemoryBus::loadImage(std::uint32_t a, const std::vector<std::uint8_t>& image) {
 if (image.empty()) return false;
 auto* r = findRegion(a, image.size(), true);
 if (!r) return false;
 std::copy(image.begin(), image.end(), r->bytes.begin() + (a - r->info.base));
 return true;
}

std::size_t MemoryBus::size() const noexcept {
 std::size_t n = 0;
 for (const auto& r : regions_) n += r.info.size;
 return n;
}

std::vector<MemoryRegionInfo> MemoryBus::regions() const {
 std::vector<MemoryRegionInfo> out;
 out.reserve(regions_.size());
 for (const auto& r : regions_) out.push_back(r.info);
 return out;
}

void MemoryBus::clear(std::uint8_t v) {
 for (auto& r : regions_) std::fill(r.bytes.begin(), r.bytes.end(), v);
}
}
