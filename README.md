# LegacyBaseEncoders

Codificadores Base16, Base32 e Base64 implementados em linguagem C procedural.

## Introdução

Durante os primeiros anos da internet, os protocolos de comunicação (como SMTP para e-mails e HTTP para a web) foram projetados para transmitir apenas caracteres ASCII — texto simples. Isso impossibilitava o envio direto de dados binários, como imagens ou arquivos.

Para contornar essa limitação, surgiram técnicas de codificação como **Base64** e **Base32**, que convertem dados binários em representações textuais seguras. Esses formatos foram **essenciais para o funcionamento de serviços de email, anexos e URLs**, e ainda são utilizados em diversos sistemas modernos.

Este repositório apresenta implementações manuais dessas codificações em C, permitindo que o leitor entenda a fundo como funcionam esses algoritmos fundamentais.

## Estrutura do Repositório

> Todos os códigos foram escritos em **C procedural**, compatíveis com os dialetos ANSI C, C89, C90 e C11, e compiláveis em sistemas Unix/Linux com `gcc` ou `clang`.

### 1. Programas de Teste

- Arquivos `CodificarXX.c` e `DecodificarXX.c`: pequenos programas de terminal que utilizam as funções de codificação e decodificação.
- Para compilar, é necessário também compilar o arquivo **CodificadorBase.c**.

### 2. Biblioteca Principal

- **CodificadorBase.c**: contém a implementação das seguintes funções:
  - `CodificarBase16`
  - `DecodificarBase16`
  - `CodificarBase32`
  - `DecodificarBase32`
  - `CodificarBase64`
  - `DecodificarBase64`
- Cada função é usada em seu respectivo programa de teste (ex: `CodificarBase16` em `Codificar16.c`).

### 3. Arquivo de Cabeçalho

- **CodificadorBase.h**
  - Protótipos de todas as funções
  - Definição de tipos enumerados
  - Definição do tipo `byte`

## 🔧 Compilação

Exemplo de compilação para codificar em Base64:

```bash
gcc CodificadorBase.c Codificar64.c -o cod64
./cod64
