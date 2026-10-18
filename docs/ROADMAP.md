# Foxxy-Wii-U-360 roadmap

Current official milestone: **v0.1b**. The configurable memory work and an initial experimental PowerPC decoder have been added to the repository. Do not mark v0.2b or v0.3b complete until the build and all tests are run and their results verified.

## 1,000 tracked engineering tasks
This is a plan, not a claim that 1,000 tasks are implemented. Ten workstreams contain 100 tasks each.
1. Build, repository and CI (001–100): host build, warnings, CI and reproducibility.
2. Memory bus and address map (101–200): configurable regions, permissions, bounds, image loading and tests.
3. Espresso/PowerPC decoder research (201–300): instruction catalogue, opcode tables and decoder vectors; initial experimental decoder now added.
4. CPU execution core (301–400): integer operations, branches, CR/XER/LR/CTR and exceptions.
5. MMU and memory protection (401–500): translation research, TLB and faults.
6. Wii U device/MMIO model (501–600): register interfaces, interrupt routing and DMA abstraction.
7. GPU/graphics research (601–700): Latte command parsing, shader feasibility and output abstraction.
8. Audio, input and system services (701–800): controller, audio and service interfaces.
9. Xbox 360/Xenon feasibility (801–900): toolchain, ABI, linker and resource constraints.
10. Integration and release validation (901–1000): synthetic tests, diagnostics, benchmarks and compatibility.

## Version gates
- v0.1b: initial C++ foundation and memory tests.
- v0.2b: configurable memory regions, read/write permissions, test-image loading and expanded tests; requires host and CI validation.
- v0.3b: experimental PowerPC decoder and test vectors; decoder source and test target have been added, but need compilation and test validation.
- v0.4b: initial CPU semantics and exception behavior.
- v0.5b: explicit MMIO device interfaces.

## Limitations
This is not a playable Wii U emulator. Espresso instruction execution, Latte GPU, system services, game compatibility and a validated Xbox 360 default.xex remain unimplemented. Host tests do not demonstrate Xbox 360 compatibility.
