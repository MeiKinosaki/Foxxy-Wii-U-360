#include "foxxy_wiiu360/powerpc_decoder.hpp"
namespace foxxy_wiiu360 {
DecodedInstruction decodePowerPC(std::uint32_t word) {
 DecodedInstruction d;
 d.raw = word;
 d.primary = static_cast<std::uint8_t>(word >> 26);
 d.rt = static_cast<std::uint8_t>((word >> 21) & 31u);
 d.ra = static_cast<std::uint8_t>((word >> 16) & 31u);
 d.immediate = static_cast<std::uint16_t>(word & 0xFFFFu);
 switch (d.primary) {
 case 14: d.kind = OpcodeKind::Addi; break;
 case 15: d.kind = OpcodeKind::Addis; break;
 case 24: d.kind = OpcodeKind::Ori; break;
 case 25: d.kind = OpcodeKind::Oris; break;
 case 28: d.kind = OpcodeKind::AndiDot; break;
 case 18: {
  d.kind = OpcodeKind::Branch;
  std::int32_t disp = static_cast<std::int32_t>(word & 0x03FFFFFCu);
  if (disp & 0x02000000) disp |= static_cast<std::int32_t>(0xFC000000u);
  d.branch_displacement = disp;
  d.absolute = (word & 2u) != 0;
  d.link = (word & 1u) != 0;
  break;
 }
 case 16: {
  d.kind = OpcodeKind::BranchConditional;
  d.branch_options = static_cast<std::uint8_t>((word >> 21) & 31u);
  d.condition_bit = static_cast<std::uint8_t>((word >> 16) & 31u);
  std::int32_t disp = static_cast<std::int32_t>(word & 0x0000FFFCu);
  if (disp & 0x00008000) disp |= static_cast<std::int32_t>(0xFFFF0000u);
  d.branch_displacement = disp;
  d.absolute = (word & 2u) != 0;
  d.link = (word & 1u) != 0;
  break;
 }
 case 17: d.kind = OpcodeKind::Sc; break;
 default: break;
 }
 return d;
}
}
