# Foxxy-Wii-U-360 roadmap
Current official milestone: **v0.1b**. Do not mark a later version complete until its tests pass.

## Batch of 1,000 tracked engineering tasks
This checklist is a planning ledger, not a claim that 1,000 tasks have been implemented. Tasks are grouped into 10 workstreams of 100 tasks each.

1. Build, repository and CI (001–100): CMake, host compiler checks, warnings, CI matrix, reproducible artifacts, code quality, docs.
2. Memory bus and address map (101–200): bounds checks, endian helpers, region descriptors, access permissions, tests.
3. PowerPC/espresso CPU research and decoder (201–300): instruction catalogue, opcode tables, decoder tests, unsupported-opcode behavior.
4. CPU execution core (301–400): integer operations, branches, CR/XER/LR/CTR semantics, exceptions and timing.
5. MMU and memory protection (401–500): address translation research, TLB model, faults, mappings and test fixtures.
6. Wii U device/MMIO model (501–600): register interface, interrupt routing, DMA abstraction and device boundaries.
7. GPU/graphics research (601–700): Latte architecture research, command parsing experiments, shader feasibility and output abstraction.
8. Audio, input and system services (701–800): controller abstractions, audio interface, service boundaries and test doubles.
9. Xbox 360/Xenon feasibility (801–900): Free60/libXenon toolchain investigation, ABI and linker experiments, memory/performance constraints.
10. Integration, compatibility and release validation (901–1000): synthetic tests, diagnostics, benchmark harness, documentation, version gates.

## Version gate
- v0.1b: source foundation and host tests.
- v0.2b: configurable memory-region map and test-image loader, with tests.
- v0.3b: experimental PowerPC instruction decoder with test vectors.
- v0.4b: defined CPU state and exception behavior.
- v0.5b: first explicit MMIO device interfaces.
- Later versions must follow sequentially; no version is considered complete without evidence.

## Limitations
This repository is not a playable Wii U emulator. Wii U Espresso/PowerPC execution, Latte GPU, system services, game compatibility and Xbox 360 default.xex are not implemented by this milestone.
