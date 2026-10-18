# Foxxy-Wii-U-360

Projeto experimental para pesquisar a viabilidade de um emulador de Nintendo Wii U no Xbox 360 RGH/JTAG.

## Estado do desenvolvimento — v0.1b

A base C++ está no repositório. O barramento agora permite regiões configuráveis, permissões de leitura/escrita e carregamento de imagens de teste; os testes cobrem limites, sobreposição, permissões e imagens. A implementação correspondente passou uma compilação e execução de testes host-side localmente. O estado do GitHub Actions ainda não foi confirmado, então a versão oficial permanece v0.1b enquanto o marco v0.2b aguarda essa verificação.

A função Emulator::step() ainda não executa instruções. Não há CPU Espresso funcional, GPU Latte, serviços Wii U, compatibilidade com jogos ou default.xex validado para Xbox 360.

## Testes host-side

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Uma compilação host-side não comprova compatibilidade com Xbox 360.

## Progressão sequencial

- **v0.1b:** base C++ e testes iniciais.
- **v0.2b (validação final pendente):** mapa de memória configurável, permissões e carregador de imagens de teste.
- **v0.3b:** decodificador PowerPC experimental com vetores de teste.
- **v0.4b:** semântica inicial da CPU, exceções e interrupções.
- **v0.5b:** interfaces de dispositivos e MMIO.

O arquivo docs/ROADMAP.md organiza 1.000 tarefas planejadas em dez áreas. Isso não significa que as 1.000 tarefas já foram implementadas. A numeração de versão só avança após implementação e validação do marco correspondente.

O projeto não inclui jogos, chaves nem firmware proprietários. Use apenas materiais obtidos legalmente.
