#pragma once
#include <cstdint>
namespace foxxy_wiiu360 {
enum class OpcodeKind { Unknown, Addi, Addis, Ori, Oris, AndiDot, Branch, BranchConditional, Sc };
struct DecodedInstruction {
 OpcodeKind kind = OpcodeKind::Unknown;
 std::uint32_t raw = 0;
 std::uint8_t primary = 0;
 std::uint8_t rt = 0;
 std::uint8_t ra = 0;
 std::uint16_t immediate = 0;
 std::uint8_t branch_options = 0;
 std::uint8_t condition_bit = 0;
 std::int32_t branch_displacement = 0;
 bool absolute = false;
 bool link = false;
};
DecodedInstruction decodePowerPC(std::uint32_t instruction);
}
