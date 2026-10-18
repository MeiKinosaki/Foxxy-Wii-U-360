# Foxxy-Wii-U-360 roadmap
Current official milestone: **v0.1b**. The v0.2b memory work is implemented in the repository and passed a local host-side build/test run of the corresponding source. GitHub Actions status has not yet been confirmed, so the release gate remains open.

## 1,000 tracked engineering tasks
This is a plan, not a claim that 1,000 tasks are implemented. Ten workstreams contain 100 tasks each.
1. Build, repository and CI (001–100): host build, warnings, CI and reproducibility.
2. Memory bus and address map (101–200): configurable regions, permissions, bounds, image loading and tests.
3. Espresso/PowerPC decoder research (201–300): instruction catalogue and decoder vectors.
4. CPU execution core (301–400): integer operations, branches, CR/XER/LR/CTR and exceptions.
5. MMU and memory protection (401–500): translation research, TLB and faults.
6. Wii U device/MMIO model (501–600): register interfaces, interrupt routing and DMA abstraction.
7. GPU/graphics research (601–700): Latte command parsing, shader feasibility and output abstraction.
8. Audio, input and system services (701–800): controller, audio and service interfaces.
9. Xbox 360/Xenon feasibility (801–900): toolchain, ABI, linker and resource constraints.
10. Integration and release validation (901–1000): synthetic tests, diagnostics, benchmarks and compatibility.

## Version gates
- v0.1b: initial C++ foundation and memory tests.
- v0.2b: configurable memory regions, read/write permissions, test-image loading and expanded tests. Local host-side build/tests passed; GitHub Actions still needs confirmation before release.
- v0.3b: experimental PowerPC decoder with instruction test vectors.
- v0.4b: initial CPU semantics and exception behavior.
- v0.5b: explicit MMIO device interfaces.

## Remaining limitations
This is not a playable Wii U emulator. Espresso execution, Latte GPU, system services, game compatibility and a validated Xbox 360 default.xex remain unimplemented. Host tests do not demonstrate Xbox 360 compatibility.
