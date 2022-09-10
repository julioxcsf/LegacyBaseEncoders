/******************************************
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Artor: Julio Cesar Silva Fernandes
 * Descricao: Programa que testa a funcao
 * CodificarBase32 usando alocacao dinamica
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
#define NUMERO_ARGUMENTOS_PRIMARIOS                  3                            
#define ANSI_COLOR_RED                               "\x1b[31m"
#define ANSI_COLOR_YELLOW                            "\x1b[33m"
#define ANSI_RESET_ALL                               "\x1b[0m"
#define EOS                                          '\0'
#define ALFABETO_HEXADECIMAL                         "0123456789ABCDEF"

#define SUCESSO                                      0
#define QUANTIDADE_ARGUMENTO_INVALIDO                1
#define ARGUMENTO_INVALIDO                           2
#define OPERACAO_INVALIDA                            3
#define ARGUMENTO_SUPERA_BYTE                        4


int
main (int argc, char *argv[])
{	
  unsigned int contador, hexaContador, numeroAlfabetoBase32, compatibilidade;
  unsigned long long numeroDeBytes;
  char *verificacao;
  char *byteCodificadosBase32;
  byte *hexaBytesEntrada, nibble1, nibble2;
  tipoAlfabetoBase32 estadoAlfabeto32;
  tipoErros codigoRetorno = 0;

  if (argc == 1) {
    printf (ANSI_COLOR_YELLOW "\nCodificar Base 32 (Padrao de Argumentos : <numero-do-alfabetoBase32>");
    printf (" <numero-de-hexaBytes> <hexabyte-1> ... <hexabyte-n>\n\n" ANSI_RESET_ALL);
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
  
  numeroAlfabetoBase32 = (unsigned int)strtoll(argv[1], &verificacao, 10);
  
  #ifdef DEPURACAO 
  printf ("numeroAlfabetoBase32 : %u \n", numeroAlfabetoBase32); 
  #endif
  if (numeroAlfabetoBase32 != 1 && numeroAlfabetoBase32 != 0){ 
      printf (ANSI_COLOR_RED "\nArgumento (1) deve ser 0(BASICO) ou 1(EXTENDIDO)\n\n" ANSI_RESET_ALL);
      exit (ARGUMENTO_INVALIDO);
  }
  
  estadoAlfabeto32 = (numeroAlfabetoBase32 == 0) ? basico : estendido;

  numeroDeBytes = strtoll(argv[2], &verificacao, 10);

  if (argc != NUMERO_ARGUMENTOS_PRIMARIOS + numeroDeBytes) {
    printf (ANSI_COLOR_RED "\nQuantidade de argumentos invalida.  (%i/%llu)\n\n" ANSI_RESET_ALL, argc-3, numeroDeBytes);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  } 
  
  #ifdef DEPURACAO 
  printf ("numero de bytes : %llu \n", numeroDeBytes); 
  printf ("Alocando memoria para bytesEntrada ... ");
  #endif

  hexaBytesEntrada = malloc(numeroDeBytes * sizeof(byte));

  #ifdef DEPURACAO
  printf ("OK\nVerfificando quanto que sera alocado em bytesCondificadosBase32 : %llu",(numeroDeBytes/5 + numeroDeBytes%5) * 8);
  printf ("\nAlocando memoria para byteCodificadosBase32 ... ");
  #endif
  byteCodificadosBase32 = malloc((numeroDeBytes/5 + numeroDeBytes%5) * 8 * sizeof(byte));
  
  #ifdef DEPURACAO
  printf ("OK\n");
  #endif
  

  for(contador = 0; contador < numeroDeBytes; contador++)
  {
    if (strlen(argv[contador + 3]) != 2){
      printf (ANSI_COLOR_RED "\nArgumento (%i) invalido. (comprimento<%i>!=2)\n\n" ANSI_RESET_ALL, contador+2,(int)strlen(argv[contador+3]));
      free (hexaBytesEntrada);
      free (byteCodificadosBase32);
      exit (ARGUMENTO_INVALIDO);
    }
    
    compatibilidade = 0;
    for (hexaContador = 0; hexaContador < 16; hexaContador++)
    {
      if(argv[contador+3][0]==ALFABETO_HEXADECIMAL[hexaContador]) {
        nibble1 = hexaContador*16; /* 2 elevado a 4 */
        #ifdef DEPURACAO
        printf ("HexaByteEntrada (%s)  | valor do nibble 1 : (%u) | ",argv[contador+3], nibble1);
        #endif
	compatibilidade++;
      }

      if(argv[contador+3][1]==ALFABETO_HEXADECIMAL[hexaContador]){
        nibble2 = hexaContador;   /* 2 elevado a 0 */
        #ifdef DEPURACAO
        printf ("valor do nibble 2 : (%u) | ", nibble2);
        #endif
        compatibilidade++;
      }
    }
   
    hexaBytesEntrada[contador] = nibble1 + nibble2;

    #ifdef DEPURACAO
    printf ("valor do byte : (%u) | compatibilidade : %u\n",hexaBytesEntrada[contador], compatibilidade);
    #endif

    if(compatibilidade != 2) {
      printf (ANSI_COLOR_RED "\nArgumento (%i) invalido. (Deve ser byte hexadecimal)\n\n" ANSI_RESET_ALL, contador+3);
      free (hexaBytesEntrada);
      free (byteCodificadosBase32);
      exit (ARGUMENTO_INVALIDO);
    }
    
  } /*for*/

  #ifdef DEPURACAO
  printf ("Todos os bytesEntrada fora escritos.\n");
  #endif


  codigoRetorno = CodificarBase32(hexaBytesEntrada, numeroDeBytes, estadoAlfabeto32, byteCodificadosBase32);


  if (codigoRetorno != ok) {
    printf (ANSI_COLOR_RED "\nErro executando (%u) funcao CodificarBase32.\n\n" ANSI_RESET_ALL, codigoRetorno);
    free (hexaBytesEntrada);
    free (byteCodificadosBase32);
    exit (ARGUMENTO_INVALIDO);
  }  

  #ifdef DEPURACAO
  printf("\nNumero de prints : %llu",( (numeroDeBytes+4)/5) * 8);
  #endif
  
  printf ("\n>>>>> \"");
  
  for (contador = 0; contador < ( (numeroDeBytes+4)/5 ) * 8; contador++)
  {
    #ifdef DEPURACAO
    printf ("(%u)",contador);
    #endif

    printf ("%c", byteCodificadosBase32[contador]);
  }

  printf ("\"\n\n");

  free (hexaBytesEntrada);
  free (byteCodificadosBase32);

  return SUCESSO;
 
} /* main */


