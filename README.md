# Foxxy-Wii-U-360

Projeto experimental para pesquisar a viabilidade de um emulador de Nintendo Wii U no Xbox 360 RGH/JTAG.

## Estado atual — v0.1b

A base C++ foi adicionada ao repositório: barramento de memória com acesso de 8/32 bits em big-endian, estado inicial de CPU, testes host-side e workflow de integração contínua. A função `Emulator::step()` ainda não executa instruções; portanto, isto **não é um emulador jogável**.

Ainda não há CPU Espresso funcional, GPU Latte, serviços Wii U, compatibilidade com jogos nem `default.xex` validado para Xbox 360.

## Testes host-side

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

O workflow GitHub Actions executa estes passos em push e pull request. Um teste host-side não comprova compatibilidade com o Xbox 360; os resultados do workflow devem ser consultados após a execução.

## Progressão sequencial

- **v0.1b (atual):** base C++, barramento inicial, testes e CI.
- **v0.2b:** mapa de memória configurável e carregador de imagens de teste.
- **v0.3b:** decodificador PowerPC experimental com vetores de teste.
- **v0.4b:** semântica inicial da CPU, exceções e interrupções.
- **v0.5b:** interfaces para dispositivos e MMIO.
- **Etapas posteriores:** pesquisa da GPU Latte, áudio, controles, serviços de sistema, toolchain Xenon e validação de desempenho.

A lista de 1.000 tarefas em `docs/ROADMAP.md` é um plano de trabalho organizado em dez áreas. Ela não significa que mil tarefas já foram implementadas. A numeração de versão só avança depois que o marco correspondente estiver codificado e testado.

O projeto não inclui jogos, chaves nem firmware proprietários. Use apenas materiais obtidos legalmente.
