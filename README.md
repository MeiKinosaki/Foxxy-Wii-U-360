# Foxxy-Wii-U-360

Projeto experimental para pesquisar a viabilidade de um emulador de Nintendo Wii U no Xbox 360 RGH/JTAG.

## Estado atual

A branch `main` contém um barramento de memória configurável, carregamento de imagens de teste, decodificador PowerPC experimental e um primeiro executor de um subconjunto de instruções inteiras: `ADDI`, `ADDIS`, `ORI`, `ORIS`, `ANDI.` e desvio incondicional `B`. Foram adicionados testes para execução, PC e LR.

**Validação:** os testes de memória/decodificação passaram em execução anterior do GitHub Actions. O workflow do commit mais recente, que inclui execução de instruções, ainda está em andamento; não declarar esta mudança validada até ele terminar.

Este é apenas um núcleo experimental inicial. Não há implementação completa da CPU Espresso, MMU/TLB, GPU Latte, serviços Wii U, áudio, compatibilidade com jogos ou `default.xex` validado para Xbox 360. Instruções não suportadas retornam falha; chamadas de sistema ainda não estão implementadas.

## Testes host-side

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Uma compilação host-side não comprova compatibilidade com Xbox 360.

## Próximas versões sequenciais

- **v0.1b:** base inicial.
- **v0.2b:** memória configurável e carregamento de imagens; aguarda validação completa do marco.
- **v0.3b:** decodificador PowerPC e primeiro executor experimental; testes do commit mais recente pendentes.
- **v0.4b:** completar semântica de instruções, branches condicionais, CR/XER/LR/CTR e falhas controladas.
- **v0.5b:** interfaces de dispositivos e MMIO.

`docs/ROADMAP.md` contém 1.000 tarefas planejadas em dez áreas. Isso é um plano, não uma afirmação de que todas foram concluídas. A versão oficial só avança depois de testes aprovados e revisão do marco.
