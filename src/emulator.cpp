#include "foxxy_wiiu360/emulator.hpp"
#include <cstdint>
namespace foxxy_wiiu360 {
Emulator::Emulator(std::size_t memory_size) : bus_(memory_size) {}
bool Emulator::step() {
 if (cpu_.halted) return false;
 cpu_.exception_pc = cpu_.pc;
 cpu_.exception_code = 0;
 std::uint32_t word = 0;
 if (!bus_.read32be(cpu_.pc, word)) {
  cpu_.exception_code = 1; // instruction fetch fault
  return false;
 }
 const auto d = decodePowerPC(word);
 const std::uint32_t old_pc = cpu_.pc;
 const std::uint32_t next_pc = old_pc + 4u;
 const std::int32_t simm = static_cast<std::int16_t>(d.immediate);
 switch (d.kind) {
 case OpcodeKind::Addi: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  cpu_.gpr[d.rt] = base + static_cast<std::uint32_t>(simm);
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::Addis: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  cpu_.gpr[d.rt] = base + (static_cast<std::uint32_t>(simm) << 16);
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::Ori:
  cpu_.gpr[d.rt] = cpu_.gpr[d.ra] | d.immediate;
  cpu_.pc = next_pc;
  break;
 case OpcodeKind::Oris:
  cpu_.gpr[d.rt] = cpu_.gpr[d.ra] | (std::uint32_t(d.immediate) << 16);
  cpu_.pc = next_pc;
  break;
 case OpcodeKind::AndiDot: {
  const std::uint32_t value = cpu_.gpr[d.ra] & d.immediate;
  cpu_.gpr[d.rt] = value;
  const std::uint32_t cr0 = value == 0 ? 0x2u :
    ((value & 0x80000000u) ? 0x8u : 0x4u);
  cpu_.cr = (cpu_.cr & 0x0FFFFFFFu) | ((cr0 | ((cpu_.xer >> 31) & 1u)) << 28);
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::LoadByte: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  const std::uint32_t address = base + static_cast<std::uint32_t>(simm);
  std::uint8_t value = 0;
  if (!bus_.read8(address, value)) { cpu_.exception_code = 3; return false; }
  cpu_.gpr[d.rt] = value;
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::LoadHalf: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  const std::uint32_t address = base + static_cast<std::uint32_t>(simm);
  std::uint16_t value = 0;
  if (!bus_.read16be(address, value)) { cpu_.exception_code = 3; return false; }
  cpu_.gpr[d.rt] = value;
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::LoadWord: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  const std::uint32_t address = base + static_cast<std::uint32_t>(simm);
  std::uint32_t value = 0;
  if (!bus_.read32be(address, value)) { cpu_.exception_code = 3; return false; }
  cpu_.gpr[d.rt] = value;
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::StoreByte: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  const std::uint32_t address = base + static_cast<std::uint32_t>(simm);
  if (!bus_.write8(address, static_cast<std::uint8_t>(cpu_.gpr[d.rt]))) { cpu_.exception_code = 4; return false; }
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::StoreHalf: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  const std::uint32_t address = base + static_cast<std::uint32_t>(simm);
  if (!bus_.write16be(address, static_cast<std::uint16_t>(cpu_.gpr[d.rt]))) { cpu_.exception_code = 4; return false; }
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::StoreWord: {
  const std::uint32_t base = d.ra == 0 ? 0u : cpu_.gpr[d.ra];
  const std::uint32_t address = base + static_cast<std::uint32_t>(simm);
  if (!bus_.write32be(address, cpu_.gpr[d.rt])) { cpu_.exception_code = 4; return false; }
  cpu_.pc = next_pc;
  break;
 }
 case OpcodeKind::Branch:
  if (d.link) cpu_.lr = next_pc;
  cpu_.pc = d.absolute ? static_cast<std::uint32_t>(d.branch_displacement)
                       : old_pc + static_cast<std::uint32_t>(d.branch_displacement);
  break;
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
                  : old_pc + static_cast<std::uint32_t>(d.branch_displacement))
    : next_pc;
  break;
 }
 default:
  cpu_.exception_code = 2; // unsupported opcode; no architectural exception vector yet
  return false;
 }
 ++cpu_.instructions_executed;
 return true;
}
}
