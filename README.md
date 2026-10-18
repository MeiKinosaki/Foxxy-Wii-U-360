# Foxxy-Wii-U-360

Projeto experimental para pesquisar a viabilidade de um emulador de Nintendo Wii U no Xbox 360 RGH/JTAG.

## Estado do desenvolvimento — v0.1b

A base C++ está no repositório, com barramento de memória, estado inicial de CPU, testes host-side e workflow do GitHub Actions. Foi iniciado o trabalho previsto para v0.2b: regiões de memória configuráveis, permissões de leitura/escrita e carregamento de imagens de teste.

**A v0.2b ainda não está declarada concluída:** os testes e a compilação precisam ser validados antes de avançar a versão. A função `Emulator::step()` ainda não executa instruções. Não há CPU Espresso funcional, GPU Latte, serviços Wii U, compatibilidade com jogos ou `default.xex` validado para Xbox 360.

## Testes host-side

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

O workflow em `.github/workflows/host-tests.yml` executa estes passos em push e pull request. Uma compilação host-side não comprova compatibilidade com Xbox 360.

## Progressão sequencial

- **v0.1b:** base C++ e testes iniciais.
- **v0.2b (em desenvolvimento):** mapa de memória configurável, permissões e carregador de imagens de teste.
- **v0.3b:** decodificador PowerPC experimental com vetores de teste.
- **v0.4b:** semântica inicial da CPU, exceções e interrupções.
- **v0.5b:** interfaces de dispositivos e MMIO.

O arquivo `docs/ROADMAP.md` organiza 1.000 tarefas planejadas em dez áreas. Isso não significa que as 1.000 tarefas já foram implementadas. A numeração de versão só avança após implementação e validação do marco correspondente.

O projeto não inclui jogos, chaves nem firmware proprietários. Use apenas materiais obtidos legalmente.
