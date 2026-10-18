#include "foxxy_wiiu360/emulator.hpp"
#include <cstdint>
namespace foxxy_wiiu360 {
Emulator::Emulator(std::size_t memory_size) : bus_(memory_size) {}
bool Emulator::step() {
 if (cpu_.halted) return false;
 std::uint32_t word = 0;
 if (!bus_.read32be(cpu_.pc, word)) return false;
 const auto d = decodePowerPC(word);
 const std::uint32_t next_pc = cpu_.pc + 4u;
 const std::int32_t simm = static_cast<std::int16_t>(d.immediate);
 switch (d.kind) {
 case OpcodeKind::Addi: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  cpu_.gpr[d.rt] = base + static_cast<std::uint32_t>(simm);
  cpu_.pc = next_pc;
  return true;
 }
 case OpcodeKind::Addis: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  const std::int64_t shifted = static_cast<std::int64_t>(simm) * 65536;
  cpu_.gpr[d.rt] = base + static_cast<std::uint32_t>(shifted);
  cpu_.pc = next_pc;
  return true;
 }
 case OpcodeKind::Ori:
  cpu_.gpr[d.rt] = cpu_.gpr[d.ra] | d.immediate;
  cpu_.pc = next_pc;
  return true;
 case OpcodeKind::Oris:
  cpu_.gpr[d.rt] = cpu_.gpr[d.ra] | (std::uint32_t(d.immediate) << 16);
  cpu_.pc = next_pc;
  return true;
 case OpcodeKind::AndiDot: {
  const std::uint32_t value = cpu_.gpr[d.ra] & d.immediate;
  cpu_.gpr[d.rt] = value;
  std::uint32_t cr0 = (value == 0 ? 0x2u : ((value & 0x80000000u) ? 0x8u : 0x4u));
  if (cpu_.xer & 0x80000000u) cr0 |= 0x1u;
  cpu_.cr = (cpu_.cr & 0x0FFFFFFFu) | (cr0 << 28);
  cpu_.pc = next_pc;
  return true;
 }
 case OpcodeKind::Branch:
  if (d.link) cpu_.lr = next_pc;
  cpu_.pc = d.absolute ? static_cast<std::uint32_t>(d.branch_displacement)
                       : cpu_.pc + static_cast<std::uint32_t>(d.branch_displacement);
  return true;
 default:
  return false;
 }
}
}
