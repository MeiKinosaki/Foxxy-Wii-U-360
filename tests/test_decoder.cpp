#include "foxxy_wiiu360/powerpc_decoder.hpp"
#include <cstdlib>
#include <iostream>
using namespace foxxy_wiiu360;
static void check(bool ok, const char* m) { if (!ok) { std::cerr << "FAIL: " << m << '\n'; std::exit(1); } }
int main() {
 auto addi = decodePowerPC(0x38600001u); // addi r3,r0,1
 check(addi.kind == OpcodeKind::Addi, "addi primary opcode");
 check(addi.rt == 3 && addi.ra == 0 && addi.immediate == 1, "addi fields");
 auto ori = decodePowerPC(0x606300FFu); // ori r3,r3,0xff
 check(ori.kind == OpcodeKind::Ori && ori.rt == 3 && ori.ra == 3 && ori.immediate == 0x00FF, "ori fields");
 auto branch = decodePowerPC(0x48000009u); // bl +8
 check(branch.kind == OpcodeKind::Branch && branch.branch_displacement == 8 && branch.link, "branch displacement and link");
 auto negative = decodePowerPC(0x4BFFFFFCu);
 check(negative.kind == OpcodeKind::Branch && negative.branch_displacement == -4, "negative branch displacement");
 auto unknown = decodePowerPC(0xFFFFFFFFu);
 check(unknown.kind == OpcodeKind::Unknown, "unknown instruction safely classified");
 std::cout << "Foxxy-Wii-U-360 decoder tests passed.\n";
}
