/******************************************
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * EEL270 - Computacao II - Turma 2022/1
 * Prof. Marcelo Luiz Drumond Lanza
 * Artor: Julio Cesar Silva Fernandes
 * Descricao: Programa que testa a funcao
 * DecodificarBase64 usando alocacao dinamica
 * para gerar o vetor com tamanho certo.
 *            
 * $Author$
 * $Date$
 * $Log$
 *
 ***************************************************/
#ifdef __linux__
#define _XOPEN_SOURCE                                600
#endif

#if defined (__FreeBSD__) && defined (__STRICT_ANSI__)
#define __ISO_C_VISIBLE                              1999
#define __LONG_LONG_SUPPORTED
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aula0801.h"


/* -Parametros da funcao main- */
#define NUMERO_ARGUMENTOS                            3                            
#define ANSI_COLOR_RED                               "\x1b[31m"
#define ANSI_COLOR_YELLOW                            "\x1b[33m"
#define ANSI_RESET_ALL                               "\x1b[0m"
#define EOS                                          '\0'
#define ALFABETO_HEXADECIMAL                         "0123456789ABCDEF"

#define SUCESSO                                      0
#define QUANTIDADE_ARGUMENTO_INVALIDO                1
#define ARGUMENTO_INVALIDO                           2



int
main (int argc, char *argv[])
{	
  unsigned int contador, numeroQuebrarLinha;
  unsigned long long numeroDeBytes;
  char *verificacao;
  byte *hexaBytesEquivalentes;
  tipoFinalLinha quebrarLinha;
  tipoErros codigoRetorno;

  if (argc == 1) {
    printf (ANSI_COLOR_YELLOW "\nDecodificar Base 32 (Padrao de Argumentos : <indicador-de-final-de-linha>");
    printf (" <CODIGO-BASE-64>\n\n" ANSI_RESET_ALL);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  }
  
  if (argc != NUMERO_ARGUMENTOS) {
    printf (ANSI_COLOR_RED "\nQuantidade de argumentos invalida.  (%i/%i)\n\n" ANSI_RESET_ALL, argc-1, NUMERO_ARGUMENTOS-1);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  }

  numeroQuebrarLinha = (unsigned int)strtoll(argv[1], &verificacao, 10);
  
  if(*verificacao != EOS) {
      printf (ANSI_COLOR_RED "\nA quebra de linha apos 76 caracteres deve ser 0(DESABILITADO) ou 1(HABILITADO).\n\n" ANSI_RESET_ALL);
      exit (ARGUMENTO_INVALIDO);
  }

  #ifdef DEPURACAO 
  printf ("numeroQuebrarLinha : %u \n", numeroQuebrarLinha); 
  #endif

  if (numeroQuebrarLinha != 1 && numeroQuebrarLinha != 0){ 
      printf (ANSI_COLOR_RED "\nArgumento (1) deve ser 0(BASICO) ou 1(EXTENDIDO)\n\n" ANSI_RESET_ALL);
      exit (ARGUMENTO_INVALIDO);
  }
  
  quebrarLinha = (numeroQuebrarLinha == 0) ? desabilitado : habilitado;

  
  #ifdef DEPURACAO
  printf ("\nVerfificando quantidade que maxima sera alocado em bytesCondificadosBase64 : %llu",(long long int)(strlen(argv[2])/4) * 3);
  printf ("\nAlocando memoria para byteCodificadosBase64 ... ");
  #endif
  hexaBytesEquivalentes = malloc( (strlen(argv[2])/8) * 5 * sizeof(byte) );
  
  #ifdef DEPURACAO
  printf ("OK\n");
  #endif

  codigoRetorno = DecodificarBase64 (argv[2], quebrarLinha , hexaBytesEquivalentes, &numeroDeBytes);

  if (codigoRetorno != ok) {
    printf (ANSI_COLOR_RED "\nErro executando (%u) funcao DecodificarBase64.\n\n" ANSI_RESET_ALL, codigoRetorno);
    free (hexaBytesEquivalentes);
    exit (ARGUMENTO_INVALIDO);
  }
  
  #ifdef DEPURACAO
  printf ("Numero De Bytes : (%llu)", numeroDeBytes);
  #endif
  
  printf ("\n>>>>> ");
  
  for (contador = 0; contador < numeroDeBytes; contador++)
  {
    printf ("%c", ALFABETO_HEXADECIMAL[hexaBytesEquivalentes[contador] >> 4 & 0x0F]); 
    printf ("%c ", ALFABETO_HEXADECIMAL[hexaBytesEquivalentes[contador] & 0x0F]); 
  }

  printf ("\n\n");

  free (hexaBytesEquivalentes);

  return SUCESSO;
 
} /* main */


/* $RCSfile: aula0805.c,v $ */
