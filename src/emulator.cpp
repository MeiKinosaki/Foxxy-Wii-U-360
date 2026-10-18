#include "foxxy_wiiu360/emulator.hpp"
#include <cstdint>
namespace foxxy_wiiu360 {
Emulator::Emulator(std::size_t memory_size) : bus_(memory_size) {}
bool Emulator::step() {
 if (cpu_.halted) return false;
 cpu_.exception_pc = cpu_.pc;
 cpu_.exception_code = 0;
 std::uint32_t word = 0;
 if (!bus_.read32be(cpu_.pc, word)) { cpu_.exception_code = 1; return false; }
 const auto d = decodePowerPC(word);
 const std::uint32_t next_pc = cpu_.pc + 4u;
 const std::int32_t simm = static_cast<std::int16_t>(d.immediate);
 switch (d.kind) {
 case OpcodeKind::Addi: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  cpu_.gpr[d.rt] = base + static_cast<std::uint32_t>(simm);
  cpu_.pc = next_pc;
  ++cpu_.instructions_executed;
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
  ++cpu_.instructions_executed;
  return true;
 case OpcodeKind::BranchConditional: {
  const std::uint8_t bo = d.branch_options;
  bool ctr_ok = true;
  if ((bo & 0x04u) == 0) {
   --cpu_.ctr;
   ctr_ok = ((cpu_.ctr != 0) != ((bo & 0x02u) != 0));
  }
  bool cond_ok = true;
  if ((bo & 0x10u) == 0) {
   const bool cr_bit = ((cpu_.cr >> (31u - d.condition_bit)) & 1u) != 0;
   cond_ok = cr_bit == ((bo & 0x08u) != 0);
  }
  if (d.link) cpu_.lr = next_pc;
  cpu_.pc = (ctr_ok && cond_ok)
    ? (d.absolute ? static_cast<std::uint32_t>(d.branch_displacement)
                  : cpu_.pc + static_cast<std::uint32_t>(d.branch_displacement))
    : next_pc;
  ++cpu_.instructions_executed;
  return true;
 }
 default:
  cpu_.exception_code = 2;
  return false;
 }
}
}
