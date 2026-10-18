#include "foxxy_wiiu360/emulator.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
using namespace foxxy_wiiu360;
static void check(bool ok,const char*msg){if(!ok){std::cerr<<"FAIL: "<<msg<<'\n';std::exit(1);}}
int main(){
 MemoryBus bus(16); check(bus.write8(0,0xAB),"write8 in bounds"); std::uint8_t b=0; check(bus.read8(0,b)&&b==0xAB,"read8 round trip");
 check(bus.write32be(4,0x12345678),"write32be"); std::uint32_t w=0; check(bus.read32be(4,w)&&w==0x12345678,"big endian round trip");
 check(!bus.read8(16,b),"out of bounds read"); check(!bus.write8(16,1),"out of bounds write"); check(!bus.read32be(14,w),"truncated read");
 check(!bus.mapRegion(8,8),"overlap rejected"); check(bus.mapRegion(0x1000,32,true,false),"read-only region mapped");
 check(bus.read8(0x1000,b)&&b==0,"mapped region reads"); check(!bus.write8(0x1000,0x55),"read-only write rejected");
 check(bus.mapRegion(0x2000,8),"second region mapped"); check(!bus.read8(0x1800,b),"unmapped address rejected"); check(!bus.mapRegion(0x2004,8),"overlap rejected");
 check(bus.loadImage(0x2000,std::vector<std::uint8_t>{0xDE,0xAD,0xBE,0xEF}),"test image loaded");
 check(bus.read32be(0x2000,w)&&w==0xDEADBEEF,"image bytes match"); check(!bus.loadImage(0x2006,std::vector<std::uint8_t>{1,2,3}),"image crossing region rejected");
 Emulator emu(64); check(emu.cpu().pc==0&&!emu.cpu().halted,"CPU initial state"); check(!emu.step(),"instruction execution not implemented");
 std::cout<<"Foxxy-Wii-U-360 memory tests passed.\n";
}
