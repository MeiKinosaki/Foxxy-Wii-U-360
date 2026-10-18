# Foxxy-Wii-U-360 roadmap

Current official milestone: **v0.1b**. Recent CI failures exposed test assumptions about unmapped instruction fetches; the test was corrected to place PC outside mapped memory. The experimental core now includes LWZ/LBZ/LHZ/STW/STB/STH and big-endian 8/16/32-bit bus access, with diagnostics for fetch (1), unsupported opcode (2), read fault (3), and write fault (4). The expanded CI run is pending; do not mark the milestone validated until it passes.

## 1,000 tracked engineering tasks
This is a plan, not a claim that 1,000 tasks are implemented. Ten workstreams contain 100 tasks each.
1. Build, repository and CI (001–100): host build, warnings, CI and reproducibility.
2. Memory bus and address map (101–200): configurable regions, permissions, bounds, image loading and tests.
3. Espresso/PowerPC decoder research (201–300): opcode tables, field extraction, signed branch displacements and test vectors.
4. CPU execution core (301–400): supported integer instructions, conditional/unconditional branches, LWZ/LBZ/LHZ/STW/STB/STH, CR/XER/LR/CTR, instruction accounting and controlled failure diagnostics.
5. MMU and memory protection (401–500): translation research, TLB and faults.
6. Wii U device/MMIO model (501–600): register interfaces, interrupt routing and DMA abstraction.
7. GPU/graphics research (601–700): Latte command parsing, shader feasibility and output abstraction.
8. Audio, input and system services (701–800): controller, audio and service interfaces.
9. Xbox 360/Xenon feasibility (801–900): toolchain, ABI, linker and resource constraints.
10. Integration and release validation (901–1000): synthetic tests, diagnostics, benchmarks and compatibility.

## Version gates
- v0.1b: initial foundation.
- v0.2b: configurable memory, permissions, image loading and tests; release validation pending.
- v0.3b: experimental decoder and partial instruction executor; current expanded test run must pass before claiming validation.
- v0.4b: broaden instruction semantics and controlled exception handling.
- v0.5b: device/MMIO interfaces.

## Limitations
Not a playable Wii U emulator. The supported interpreter subset is incomplete; full Espresso, MMU/TLB, Latte GPU, system services, game compatibility and a validated Xbox 360 default.xex remain unimplemented. Host CI success is not Xbox 360 compatibility evidence.
