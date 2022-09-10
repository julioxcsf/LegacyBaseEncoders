/***************************************************
 *
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 * Artor: Julio Cesar Silva Fernandes
 * Descricao: Programa que testa a funcao
 * CodificarBase64 usando alocacao dinamica
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
  unsigned int contador, hexaContador, numeroQuebrarLinha, compatibilidade;
  unsigned long long numeroDeBytes;
  unsigned long long tamanhoDoCodigoBase64 = 0;
  char *verificacao;
  char *codigoBase64;
  byte *hexaBytes, nibble1, nibble2;
  tipoFinalLinha quebrarLinha;
  tipoErros codigoRetorno;

  if (argc == 1) {
    printf (ANSI_COLOR_YELLOW "\nCodificar Base 64 (Padrao de Argumentos : <indicador-de-final-de-linha>");
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
  
  numeroQuebrarLinha = (unsigned int)strtoll(argv[1], &verificacao, 10);
  
  #ifdef DEPURACAO 
  printf ("numeroQuebrarlinha : (%u) \n", numeroQuebrarLinha); 
  #endif
  if (numeroQuebrarLinha != 1 && numeroQuebrarLinha != 0) { 
      printf (ANSI_COLOR_RED "\nArgumento 1 (quebra de linha) deve ser 0(desabilitado) ou 1(habilitado)\n\n" ANSI_RESET_ALL);
      exit (ARGUMENTO_INVALIDO);
  }
  
  quebrarLinha = (numeroQuebrarLinha == 0) ? desabilitado : habilitado;

  numeroDeBytes = strtoll(argv[2], &verificacao, 10);
  
  if (argc != NUMERO_ARGUMENTOS_PRIMARIOS + numeroDeBytes) {
    printf (ANSI_COLOR_RED "\nQuantidade de argumentos invalida.  (%i/%llu)\n\n" ANSI_RESET_ALL, argc-3, numeroDeBytes);
    exit (QUANTIDADE_ARGUMENTO_INVALIDO);
  } 
  
  
  #ifdef DEPURACAO 
  printf ("numero de bytes : %llu \n", numeroDeBytes); 
  printf ("Alocando memoria para hexaBytes ... ");
  #endif

  hexaBytes = malloc(numeroDeBytes * sizeof(byte));

  if (quebrarLinha == habilitado)
    tamanhoDoCodigoBase64 = (numeroDeBytes/4 + 1) * 4 + (numeroDeBytes/76 * 2); 
    /* (numeroDeBytes/76) * 2 => espaco adicionado para receber '\n' e '\t' */
  
  #ifdef DEPURACAO
  printf ("OK\nVerfificando quanto que sera alocado em codigoBase64 : %llu",tamanhoDoCodigoBase64);
  printf ("\nAlocando memoria para byteCodificadosBase32 ... ");
  #endif
  codigoBase64 = malloc( tamanhoDoCodigoBase64 * sizeof(byte) );
  
  #ifdef DEPURACAO
  printf ("OK\n");
  #endif
  

  for(contador = 0; contador < numeroDeBytes; contador++)
  {
    if (strlen(argv[contador + 3]) != 2){
      printf (ANSI_COLOR_RED "\nArgumento (%i) invalido. (comprimento<%i>!=2)\n\n" ANSI_RESET_ALL, contador+2,(int)strlen(argv[contador+3]));
      free (hexaBytes);
      free (codigoBase64);
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
   
    hexaBytes[contador] = nibble1 + nibble2;

    #ifdef DEPURACAO
    printf ("valor do byte : (%u) | compatibilidade : %u\n",hexaBytes[contador], compatibilidade);
    #endif

    if(compatibilidade != 2) {
      printf (ANSI_COLOR_RED "\nArgumento (%i) invalido. (Deve ser byte hexadecimal)\n\n" ANSI_RESET_ALL, contador+3);
      free (hexaBytes);
      free (codigoBase64);
      exit (ARGUMENTO_INVALIDO);
    }
    
  } /*for*/

  #ifdef DEPURACAO
  printf ("Todos os bytesEntrada fora escritos.\n");
  #endif


  codigoRetorno = CodificarBase64(hexaBytes, numeroDeBytes, quebrarLinha, codigoBase64);


  if (codigoRetorno != ok) {
    printf (ANSI_COLOR_RED "\nErro executando (%u) funcao CodificarBase64.\n\n" ANSI_RESET_ALL, codigoRetorno);
    free (hexaBytes);
    free (codigoBase64);
    exit (ARGUMENTO_INVALIDO);
  }  

  #ifdef DEPURACAO
  printf("\nNumero de prints : %llu", (long long unsigned)strlen(codigoBase64));
  #endif
  
  printf ("\n>>>>>> \"");
  
  for (contador = 0; contador < strlen(codigoBase64); contador++)
  {
    #ifdef DEPURACAO
    printf ("(%u)",contador);
    #endif

    printf ("%c", codigoBase64[contador]);
  }

  printf ("\"\n\n");

  free (hexaBytes);
  free (codigoBase64);

  return SUCESSO;
 
} /* main */

