# C-codes
(Todos os códigos foram escritos com a linguagem C procedural)

Estão neste repositório:

1 - Códigos-fonte de programas de testes para terminal  (CodificarXX.c e DecodificarXX.c)
compilaveis usando do gcc ou clang , os dialetos ANSI, C89, C90 e C11 em sistema operacional Linux ou Unix.
(Obs: a linkedição desses programas exige a compilação do CodificadorBase.c)

2 - Código-fonte "CodificadorBase.c" com a implementação das funções :
    2.1 - CodificarBase16;
    2.2 - DecodificarBase16;
    2.3 - CodificarBase32;
    2.4 - DecodificarBase32;
    2.5 - CodificarBase64;
    2.6 - DecodificarBase64;
 Cada função foi usada em seu respectivo programa. Ex:
 CodificarBase16 usada em Codificar16.c
    
 3 - Arquivo de cabeçalho "CodificadorBase.h" com o protóripo de todas as funções implementadas em CodificadorBase.c,
 definição de tipos enumerados e a definição do tipo byte.
