/******************************************
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Artor: Julio Cesar Silva Fernandes
 * Descricao: Programa que testa a funcao
 * CodificarBase16 usando alocacao dinamica
 * para gerar o vetor com tamanho certo.
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
#define NUMERO_ARGUMENTOS_PRIMARIOS                  2                            
#define ANSI_COLOR_RED                               "\x1b[31m"
#define ANSI_COLOR_YELLOW                            "\x1b[33m"
#define ANSI_RESET_ALL                               "\x1b[0m"
#define EOS                                          '\0'

#define SUCESSO                                      0
#define QUANTIDADE_ARGUMENTO_INVALIDO                1
#define ARGUMENTO_INVALIDO                           2
#define OPERACAO_INVALIDA                            3
#define ARGUMENTO_SUPERA_BYTE                        4


int
main (int argc, char *argv[])
{	
  unsigned int contador;
  unsigned long long numeroDeBytes;
  char *verificacao;
  char *byteCodificadosBase16;
  byte *bytesEntrada;
  long numero;
  tipoErros codigoRetorno = 0;

  if (argc == 1) {
    printf (ANSI_COLOR_YELLOW "\nCodificar Base 16 (Padrao de Argumentos : <numero-de-bytes> <byte-1> ... <byte-n>\n\n" ANSI_RESET_ALL);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  }
  
  if (argc < NUMERO_ARGUMENTOS_PRIMARIOS) {
    printf (ANSI_COLOR_RED "\nQuantidade de argumentos invalida.  (%i/%i)\n\n" ANSI_RESET_ALL, argc-1, NUMERO_ARGUMENTOS_PRIMARIOS-1);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  }

  for(contador=1; contador <= NUMERO_ARGUMENTOS_PRIMARIOS - 1; contador++)
  {
    numeroDeBytes = strtoll(argv[contador], &verificacao, 10);
    
    if(*verificacao != EOS) {
      printf (ANSI_COLOR_RED "\nArgumento (%u) deve ser um inteiro sem sinal.\n\n" ANSI_RESET_ALL ,contador);
      exit (ARGUMENTO_INVALIDO);
    }
  }

  if (argc != NUMERO_ARGUMENTOS_PRIMARIOS + numeroDeBytes) {
    printf (ANSI_COLOR_RED "\nQuantidade de argumentos invalida.  (%i/%llu)\n\n" ANSI_RESET_ALL, argc-2, numeroDeBytes);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  } 
  
  #ifdef DEPURACAO 
  printf ("numero de bytes : %llu \n", numeroDeBytes); 
  printf ("Alocando memoria para bytesEntrada ... ");
  #endif

  bytesEntrada = malloc(numeroDeBytes * sizeof(byte));

  #ifdef DEPURACAO
  printf ("OK\nAlocando memoria para byteCodificadosBase16 ... ");
  #endif
  byteCodificadosBase16 = malloc(numeroDeBytes * sizeof(byte) * 2);
  
  #ifdef DEPURACAO
  printf ("OK\n");
  #endif
  

  for(contador = 0; contador < numeroDeBytes; contador++)
  {
    numero = strtol(argv[contador + 2], &verificacao, 10);
    
    if (*verificacao != EOS) {
      printf (ANSI_COLOR_RED "\nArgumento n(%u) <%s> deve ser um inteiro sem sinal.\n\n" ANSI_RESET_ALL, contador+1, argv[contador+2]);
      exit (ARGUMENTO_INVALIDO);
    }
    
    if (numero > 255) {
      printf (ANSI_COLOR_RED "\nArgumento n(%u) <%s> deve ser menor entre 0 e 255 (inclusive)\n\n" ANSI_RESET_ALL, contador+1, argv[contador+2]);
      exit (ARGUMENTO_SUPERA_BYTE);
    }
    
    #ifdef DEPURACAO
    printf ("Escrevendo (%li) em bytesEntrada[%u] ... ", numero, contador);
    #endif
    bytesEntrada[contador] = (byte) numero;
    #ifdef DEPURACAO
    printf ("OK\n");
    #endif
  } /*for*/

  #ifdef DEPURACAO
  printf ("Todos os bytesEntrada fora escritos.\n");
  #endif


  codigoRetorno = CodificarBase16(bytesEntrada, numeroDeBytes, byteCodificadosBase16);


  if (codigoRetorno != ok) {
    printf (ANSI_COLOR_RED "\nErro executando (%u) funcao CodificarBase16.\n\n" ANSI_RESET_ALL, codigoRetorno);
    exit (ARGUMENTO_INVALIDO);
  }  

  printf ("\n>>>>> \"");

  for (contador = 0; contador < numeroDeBytes * 2; contador++)
    printf ("%c", byteCodificadosBase16[contador]);
  
  printf ("\"\n\n");

  free (bytesEntrada);
  free (byteCodificadosBase16);

  return SUCESSO;
 
} /* main */



/* $RCSfile: aula0802.c,v $ */
