/**************************************************
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Artor: Julio Cesar Silva Fernandes
 * Descricao: Programa que testa a funcao
 * DecodificarBase16 usando alocacao dinamica
 * para gerar o vetor com tamanho certo.
 *
 *************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aula0801.h"


/* -Parametros da funcao main- */
#define NUMERO_ARGUMENTOS                            2                            
#define ANSI_COLOR_RED                               "\x1b[31m"
#define ANSI_COLOR_YELLOW                            "\x1b[33m"
#define ANSI_RESET_ALL                               "\x1b[0m"

#define SUCESSO                                      0
#define QUANTIDADE_ARGUMENTO_INVALIDO                1
#define ARGUMENTO_INVALIDO                           2
#define CODIGO_BASE16_INCOMPLETO                     3
#define OPERACAO_INVALIDA                            4


int
main (int argc, char *argv[])
{	
  unsigned int contador;
  unsigned long long numeroDeBytes = 0;
  byte *bytesEquivalentes;
  tipoErros codigoRetorno = 0;

  if (argc == 1) {
    printf (ANSI_COLOR_YELLOW "\nDecodificar Base 16 (Padrao de Argumentos : WX...YZ [valores de 0 a F(15)]\n\n" ANSI_RESET_ALL);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  }
  
  if (argc < NUMERO_ARGUMENTOS) {
    printf (ANSI_COLOR_RED "\nQuantidade de argumentos invalida.  (%i/%i)\n\n" ANSI_RESET_ALL, argc-1, NUMERO_ARGUMENTOS-1);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  }
 
  if ( strlen(argv[1]) % 2 ) {
    printf (ANSI_COLOR_RED "\nCodigo Base 16 incompleto. A quanditade de caracteres deve ser PAR.\n\n" ANSI_RESET_ALL);
    exit (CODIGO_BASE16_INCOMPLETO);
  }

  #ifdef DEPURACAO 
  printf ("Alocando memoria para bytesEquivalentes ... ");
  #endif

  /* preciso do numero de bytes para alocar a memoria :( */
  bytesEquivalentes = malloc((strlen(argv[1])/2) * sizeof(byte));

  #ifdef DEPURACAO
  printf ("OK\n");
  #endif
  
  codigoRetorno = DecodificarBase16(argv[1], bytesEquivalentes, &numeroDeBytes);

  if (codigoRetorno != ok) {
    
    if (codigoRetorno == codigoBase16Invalido)
      printf (ANSI_COLOR_RED "\nErro executando (%u) funcao DecodificarBase16. Use letras maiuscolas no codigo Base 16 de entrada.\n\n" ANSI_RESET_ALL, codigoRetorno);
    
    else
      printf (ANSI_COLOR_RED "\nErro executando (%u) funcao DecodificarBase16.\n\n" ANSI_RESET_ALL, codigoRetorno);
    
    exit (ARGUMENTO_INVALIDO);
  }  

  printf ("\n>>>>> ");

  for (contador = 0; contador < numeroDeBytes; contador++)
    printf ("%i ", bytesEquivalentes[contador]);
  
  printf ("\nNumero De Bytes : %llu\n\n",numeroDeBytes);

  free (bytesEquivalentes);

  return SUCESSO;
 
} /* main */

