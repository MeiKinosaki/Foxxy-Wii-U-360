#include "foxxy_wiiu360/emulator.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace foxxy_wiiu360;
static void check(bool ok, const char* msg) {
 if (!ok) { std::cerr << "FAIL: " << msg << '\n'; std::exit(1); }
}
int main() {
 MemoryBus bus(16);
 check(bus.size()==16, "initial region size");
 check(bus.write8(0,0xAB), "write8 in bounds");
 std::uint8_t b=0;
 check(bus.read8(0,b)&&b==0xAB, "read8 round trip");
 check(bus.write32be(4,0x12345678), "write32be");
 std::uint32_t w=0;
 check(bus.read32be(4,w)&&w==0x12345678, "big endian round trip");
 check(!bus.read8(16,b), "out of bounds read");
 check(!bus.write8(16,1), "out of bounds write");
 check(!bus.read32be(14,w), "truncated read");
 check(!bus.mapRegion(8,8), "overlapping region rejected");
 check(!bus.mapRegion(0xFFFFFFF0u,32), "address overflow rejected");
 check(bus.mapRegion(0x1000,32,true,false), "read-only region mapped");
 check(bus.read8(0x1000,b)&&b==0, "mapped region reads");
 check(!bus.write8(0x1000,0x55), "read-only write rejected");
 check(bus.mapRegion(0x2000,8), "second region mapped");
 check(!bus.read8(0x1800,b), "unmapped address rejected");
 check(!bus.mapRegion(0x2004,8), "overlap with mapped region rejected");
 check(bus.loadImage(0x2000,std::vector<std::uint8_t>{0xDE,0xAD,0xBE,0xEF}), "test image loads");
 check(bus.read32be(0x2000,w)&&w==0xDEADBEEF, "loaded image bytes match");
 check(!bus.loadImage(0x2006,std::vector<std::uint8_t>{1,2,3}), "image crossing region rejected");
 check(!bus.loadImage(0x2000,std::vector<std::uint8_t>{}), "empty image rejected");
 bus.clear(0x5A);
 check(bus.read8(0x2000,b)&&b==0x5A, "clear resets all mapped regions");
 MemoryBus permissions(0);
 check(permissions.mapRegion(0x3000,16,false,true), "write-only region mapped");
 check(!permissions.read8(0x3000,b), "read permission enforced");
 check(permissions.write8(0x3000,0x42), "write permission allowed");
 check(permissions.regions().size()==1, "region metadata available");
 Emulator emu(64);
 check(emu.cpu().pc==0&&!emu.cpu().halted, "CPU initial state");
 check(!emu.step(), "unmapped fetch fails safely");
 Emulator cpu(64);
 check(cpu.bus().write32be(0, 0x38600001u), "write addi instruction");
 check(cpu.bus().write32be(4, 0x606300FFu), "write ori instruction");
 check(cpu.bus().write32be(8, 0x48000008u), "write branch instruction");
 check(cpu.step() && cpu.cpu().gpr[3] == 1 && cpu.cpu().pc == 4, "execute addi");
 check(cpu.step() && cpu.cpu().gpr[3] == 0xFF && cpu.cpu().pc == 8, "execute ori");
 check(cpu.step() && cpu.cpu().pc == 16, "execute unconditional branch");
 check(!cpu.step(), "unmapped instruction fetch fails");
 Emulator linked(64);
 check(linked.bus().write32be(0, 0x48000009u), "write branch-and-link");
 check(linked.step() && linked.cpu().pc == 8 && linked.cpu().lr == 4, "branch-and-link updates LR");
 Emulator conditional(64);
 const std::uint32_t bc_if_cr0_lt = (16u << 26) | (12u << 21) | 8u;
 check(conditional.bus().write32be(0, bc_if_cr0_lt), "write conditional branch");
 conditional.cpu().cr = 0x80000000u;
 check(conditional.step() && conditional.cpu().pc == 8, "conditional branch taken from CR bit");
 Emulator not_taken(64);
 check(not_taken.bus().write32be(0, bc_if_cr0_lt), "write conditional branch not-taken case");
 not_taken.cpu().cr = 0;
 check(not_taken.step() && not_taken.cpu().pc == 4, "conditional branch not taken");
 Emulator ctr_branch(64);
 const std::uint32_t bc_ctr_nonzero = (16u << 26) | (16u << 21) | 8u;
 check(ctr_branch.bus().write32be(0, bc_ctr_nonzero), "write CTR conditional branch");
 ctr_branch.cpu().ctr = 2;
 check(ctr_branch.step() && ctr_branch.cpu().pc == 8 && ctr_branch.cpu().ctr == 1, "CTR decremented and branch taken");
 Emulator addis(64);
 check(addis.bus().write32be(0, 0x3C600001u), "write addis");
 check(addis.step() && addis.cpu().gpr[3] == 0x00010000u, "execute addis");
 Emulator negative_addi(64);
 check(negative_addi.bus().write32be(0, 0x3860FFFFu), "write negative addi");
 check(negative_addi.step() && negative_addi.cpu().gpr[3] == 0xFFFFFFFFu, "sign extend addi immediate");
 std::cout << "Foxxy-Wii-U-360 memory tests passed.\n";
}
