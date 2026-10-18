# Foxxy-Wii-U-360

Projeto experimental para pesquisar a viabilidade de um emulador de Nintendo Wii U no Xbox 360 RGH/JTAG.

## Estado do desenvolvimento

A branch `main` contém memória configurável, carregador de imagens, decodificador PowerPC experimental e execução inicial de `ADDI`, `ADDIS`, `ORI`, `ORIS`, `ANDI.`, desvios `B`/`BC` e operações inteiras `LWZ`, `LBZ`, `LHZ`, `STW`, `STB` e `STH`. O barramento oferece leitura/escrita big-endian de 8, 16 e 32 bits. A CPU registra instruções executadas e códigos diagnósticos: busca inválida (1), opcode não suportado (2), falha de leitura (3) e falha de escrita (4).

Uma falha de compilação anterior foi rastreada a declarações duplicadas nos testes do decodificador e corrigida. O workflow host-side do commit de correção dos testes passou: compilação e 2/2 conjuntos de testes verdes. Isso valida somente o subconjunto experimental no host, não a execução no Xbox 360.

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
- **v0.2b:** memória configurável, permissões e carregador — testes host-side aprovados.
- **v0.3b:** decodificador e executor PowerPC experimentais, desvios e subconjunto de cargas/armazenamentos — testes host-side aprovados; marco atual.
- **v0.4b:** ampliar semântica de instruções, exceções e falhas controladas.
- **v0.5b:** interfaces de dispositivos e MMIO.

`docs/ROADMAP.md` contém 1.000 tarefas planejadas em dez áreas. Isso é um plano, não uma afirmação de que todas foram concluídas. A versão oficial só avança após implementação, testes aprovados e revisão do marco.
