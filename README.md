# Foxxy-Wii-U-360

Projeto experimental para pesquisar a viabilidade de um emulador de Nintendo Wii U no Xbox 360 RGH/JTAG.

## Estado do desenvolvimento — v0.1b

A base C++ e o barramento de memória configurável estão no repositório. Também foi adicionado um decodificador PowerPC experimental que identifica um conjunto pequeno de opcodes (ADDI, ADDIS, ORI, ORIS, ANDI., B, BC e SC) e um alvo de testes separado. Esses componentes ainda precisam passar pela compilação e execução dos testes no CI antes de serem considerados validados.

A função `Emulator::step()` ainda não executa instruções. O decodificador apenas classifica campos básicos; não é um núcleo Espresso funcional. Não há GPU Latte, serviços Wii U, compatibilidade com jogos ou `default.xex` validado para Xbox 360.

## Testes host-side

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

O workflow em `.github/workflows/host-tests.yml` executa estes passos em push e pull request. O resultado remoto ainda precisa ser verificado. Uma compilação host-side não comprova compatibilidade com Xbox 360.

## Progressão sequencial

- **v0.1b:** base C++ inicial.
- **v0.2b (validação pendente):** mapa de memória configurável, permissões e carregador de imagens de teste.
- **v0.3b (trabalho experimental adicionado, validação pendente):** decodificador PowerPC e vetores de teste.
- **v0.4b:** semântica inicial da CPU, exceções e interrupções.
- **v0.5b:** interfaces de dispositivos e MMIO.

O arquivo `docs/ROADMAP.md` organiza 1.000 tarefas planejadas em dez áreas. Isso não significa que as 1.000 tarefas já foram implementadas. A numeração de versão só avança após implementação e validação do marco correspondente.

O projeto não inclui jogos, chaves nem firmware proprietários. Use apenas materiais obtidos legalmente.
