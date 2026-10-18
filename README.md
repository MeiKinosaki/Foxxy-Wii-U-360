# Foxxy-Wii-U-360

Projeto experimental para pesquisar a viabilidade de um emulador de Nintendo Wii U no Xbox 360 RGH/JTAG.

## Estado atual — v0.1b

Este repositório está na fase inicial. O código atual ainda não executa jogos de Wii U, não implementa uma CPU Espresso funcional, não emula a GPU Latte e não produz um `default.xex` validado para Xbox 360.

## Plano de desenvolvimento sequencial

- **v0.1b:** estrutura inicial, barramento de memória experimental e testes básicos.
- **v0.2b:** mapa de memória configurável e carregador de imagens de teste.
- **v0.3b:** decodificador PowerPC experimental com testes unitários.
- **v0.4b:** estado da CPU, exceções e interrupções.
- **v0.5b:** dispositivos e interfaces MMIO.
- **Etapas posteriores:** investigar GPU Latte, áudio, controles, serviços do sistema e viabilidade da toolchain Xenon.

## Testes

Quando o código-fonte estiver presente, os testes host-side podem ser executados com:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Esses comandos verificam uma compilação para computador e não comprovam compatibilidade com o Xbox 360.

O projeto não inclui jogos, chaves nem firmware proprietários. Use apenas materiais obtidos legalmente.
