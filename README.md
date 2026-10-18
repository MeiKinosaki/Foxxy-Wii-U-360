# Foxxy-Wii-U-360

Projeto experimental para pesquisar a viabilidade de um emulador de Nintendo Wii U no Xbox 360 RGH/JTAG.

## Estado do desenvolvimento

A branch `main` contém barramento de memória configurável, carregador de imagens, decodificador PowerPC experimental e execução inicial de `ADDI`, `ADDIS`, `ORI`, `ORIS`, `ANDI.` e `B`. Foi adicionada lógica experimental para `BC`, com testes para condições do CR, contador CTR e imediatos com sinal.

Os testes anteriores do executor passaram no GitHub Actions. Os testes ampliados de branches condicionais e decodificação foram enviados agora e ainda precisam de resultado verde para validar esse avanço.

**Limitações:** não é um emulador jogável. A CPU Espresso completa, MMU/TLB, GPU Latte, serviços do sistema Wii U, áudio, compatibilidade com jogos e `default.xex` validado para Xbox 360 continuam por implementar. Instruções não suportadas não são executadas.

## Testes host-side

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

O teste host-side não comprova compatibilidade com Xbox 360.

## Versões sequenciais

- **v0.1b:** base inicial do projeto.
- **v0.2b:** memória configurável, permissões e carregador; validação do marco pendente.
- **v0.3b:** decodificador e executor PowerPC experimentais, incluindo `BC`; validação dos testes ampliados pendente.
- **v0.4b:** ampliar semântica de instruções, exceções e falhas controladas.
- **v0.5b:** interfaces de dispositivos e MMIO.

`docs/ROADMAP.md` contém 1.000 tarefas planejadas em dez áreas. Isso não significa que todas estejam concluídas. A versão oficial só avança após implementação, testes aprovados e revisão do marco.
