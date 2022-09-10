/*****************************************************************
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica  
 * Departamento de Eletronica e de Computacao
 * Artor: Julio Cesar Silva Fernandes
 * Descricao: Arquivo .c com a implementacao das seguintes funcoes:
 * 1 - CodificarBase16
 * 2 - DecodificarBase16
 * 3 - CodificarBase32
 * 4 - DecodificarBase32
 * 5 - CodificarBase64
 * 6 - DecodificarBase64
 *
 *****************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aula0801.h" 

#define BASE16                              "0123546789ABCDEF" 
#define BASE32       "ABCDEFGHIJKLMNOPQRSTUVWXYZ2345670123456789ABCDEFGHIJKLMNOPQRSTUV"
                                    /*   basico      AB   estendido         */

#define BASE64       "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"

tipoErros
CodificarBase16 ( byte *ponteiroByte,               /* (E) */
                  unsigned long long numeroDeBytes, /* (E) */
                  char *pacoteBase16 )              /* (S) */
{
  unsigned int contador, pacote;
 
  if(!ponteiroByte)
    return enderecoInvalido;  

  pacote = 0;
  for ( contador = 0; contador < numeroDeBytes; contador++)
  {
    #ifdef DEPURACAO
    printf ("endereco: %p | valor : %i |",ponteiroByte, *ponteiroByte);
    #endif
    
    pacoteBase16[pacote] = BASE16[(*ponteiroByte >> 4 & 0x0F)];
    pacoteBase16[pacote + 1] = BASE16[( *ponteiroByte & 0x0F)];
    ponteiroByte += sizeof(byte);
    pacote += 2;
    
    #ifdef DEPURACAO
    printf ("  ponteiro alterado.\n");
    #endif
  }
  
  return ok;
}

tipoErros
DecodificarBase16 (char *codigoBase16,                /* (E) */
                   byte *byteEquivalente,             /* (S) */
                   unsigned long long *numeroDeBytes) /* (S) */
{
  unsigned int contador, contador2, byteObservado, compatibilidade;
  byte primeiraMetade, segundaMetade;

  if (!codigoBase16)
    return enderecoInvalido;

  byteObservado = 0;

  for (contador = 0; contador < strlen(codigoBase16); contador += 2)
  {
    #ifdef DEPURACAO
    printf ("Calculando primeiraMetade[%u] ...", byteObservado);
    #endif

    compatibilidade = 0;

    for (contador2 = 0; contador2 < 16; contador2++)
      if (codigoBase16[contador] == BASE16[contador2]) {
        primeiraMetade = ((byte)contador2 << 4 & 0xF0);
        compatibilidade++;	 
      }

    #ifdef DEPURACAO
    printf ("OK\nCalculando segundaMetade[%u] ...", byteObservado);
    #endif
    for (contador2 = 0; contador2 < 16; contador2++)
      if (codigoBase16[contador+1] == BASE16[contador2]) {
        segundaMetade = (byte)contador2;
        compatibilidade++;
      }
    byteEquivalente[byteObservado] = primeiraMetade + segundaMetade;
    byteObservado++;
    if (compatibilidade < 2)
      return codigoBase16Invalido;

    #ifdef DEPURACAO
    printf ("OK\nprimeiraMedade[%u] = %u\nsegundaMetade[%u] = %u\n", byteObservado, primeiraMetade, byteObservado, segundaMetade);
    #endif
  }

  *numeroDeBytes = byteObservado;

  return ok;
}

tipoErros
CodificarBase32 (byte *hexaBytes,                     /* (E) */
		 unsigned long long numeroDeBytes,    /* (E) */
		 tipoAlfabetoBase32 estadoAlfabeto32, /* (E) */
		 char *pacoteBase32 )                 /* (S) */
{
  unsigned int contador, pacote, variavelAlfabeto32;
  unsigned long long copiaNumeroDeBytes;
 
  copiaNumeroDeBytes = numeroDeBytes;

  if (!hexaBytes){
    return enderecoInvalido;
  }
  #ifdef DEPURACAO
  printf ("\nestadoAlfabeto32 : %u\n",estadoAlfabeto32);
  #endif

  variavelAlfabeto32 = (estadoAlfabeto32 == estendido) ? 32 : 0;
  
  #ifdef DEPURACAO
  printf ("\nvariavelAlfabeto32 : %u\n",variavelAlfabeto32);
  #endif

  pacote = 0;
  
  #ifdef DEPURACAO
  printf ("\nCodificar Base 32\nNumero de bytes : %llu",numeroDeBytes);
  printf ("\nEndereco do primeiro hexaBytes(entrada) : %p",hexaBytes);
  printf ("\nValor do primeiro hexaBytes(entrada) : %u",hexaBytes[0]);

  printf ("\nEndereco do primeiro pacoteBase32(saida) : %p",pacoteBase32);
  printf ("\nEndereco do primeiro pacoteBase32(saida) : %p",&pacoteBase32[0]);
  printf ("\nValor do primeiro pacoteBase32(saida) : %u",pacoteBase32[0]);
  #endif

  for (contador = 0; contador < copiaNumeroDeBytes; contador+=5)
  {
    
    #ifdef DEPURACAO
    printf ("\nIniciando a escrita dos 8 pacotesBase32\n");
    #endif

    pacoteBase32[pacote] = BASE32[(hexaBytes[contador] >> 3 & 0x1F) + variavelAlfabeto32];
    pacoteBase32[pacote + 1] = BASE32[(hexaBytes[contador] << 2  & 0x1C) + variavelAlfabeto32];
    pacoteBase32[pacote + 2] = '=';
    pacoteBase32[pacote + 3] = '=';
    pacoteBase32[pacote + 4] = '=';
    pacoteBase32[pacote + 5] = '=';
    pacoteBase32[pacote + 6] = '=';
    pacoteBase32[pacote + 7] = '=';
    
    #ifdef DEPURACAO
    printf ("\n-------2-------\n");
    printf ("pacoteBase32[%u] : %c\n",pacote    , pacoteBase32[pacote]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 1, pacoteBase32[pacote + 1]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 2, pacoteBase32[pacote + 2]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 3, pacoteBase32[pacote + 3]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 4, pacoteBase32[pacote + 4]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 5, pacoteBase32[pacote + 5]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 6, pacoteBase32[pacote + 6]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 7, pacoteBase32[pacote + 7]);
    printf ("Numero de bytes : %llu",numeroDeBytes);
    #endif
    
    numeroDeBytes--;

    if(!numeroDeBytes)
      break;
    
    numeroDeBytes--;

    if(!numeroDeBytes)
    {
      pacoteBase32[pacote + 1] = BASE32[(hexaBytes[contador] << 2 & 0x1C) + (hexaBytes[contador+1] >> 6 & 0x03) + variavelAlfabeto32];
      pacoteBase32[pacote + 2] = BASE32[(hexaBytes[contador+1] >> 1 & 0x1F) + variavelAlfabeto32];
      pacoteBase32[pacote + 3] = BASE32[(hexaBytes[contador+1] << 4 & 0x10) + variavelAlfabeto32];
      #ifdef DEPURACAO
      printf ("\n-------2-------\n");
      printf ("pacoteBase32[%u] : %c\n",pacote    , pacoteBase32[pacote]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 1, pacoteBase32[pacote + 1]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 2, pacoteBase32[pacote + 2]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 3, pacoteBase32[pacote + 3]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 4, pacoteBase32[pacote + 4]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 5, pacoteBase32[pacote + 5]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 6, pacoteBase32[pacote + 6]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 7, pacoteBase32[pacote + 7]);
      printf ("Numero de bytes : %llu",numeroDeBytes);
      #endif
      break;
    }

    
    numeroDeBytes--;

    if(!numeroDeBytes)
    {
      pacoteBase32[pacote + 1] = BASE32[(hexaBytes[contador] << 2 & 0x1C) + (hexaBytes[contador+1] >> 6 & 0x03) + variavelAlfabeto32];
      pacoteBase32[pacote + 2] = BASE32[(hexaBytes[contador+1] >> 1 & 0x1F) + variavelAlfabeto32];
      pacoteBase32[pacote + 3] = BASE32[(hexaBytes[contador+1] << 4 & 0x10) + (hexaBytes[contador+2] >> 4 & 0x0F) + variavelAlfabeto32];
      pacoteBase32[pacote + 4] = BASE32[(hexaBytes[contador+2] << 1 & 0x1E) + variavelAlfabeto32];
      #ifdef DEPURACAO
      printf ("\n-------3-------\n");
      printf ("pacoteBase32[%u] : %c\n",pacote    , pacoteBase32[pacote]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 1, pacoteBase32[pacote + 1]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 2, pacoteBase32[pacote + 2]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 3, pacoteBase32[pacote + 3]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 4, pacoteBase32[pacote + 4]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 5, pacoteBase32[pacote + 5]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 6, pacoteBase32[pacote + 6]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 7, pacoteBase32[pacote + 7]);
      printf ("Numero de bytes : %llu",numeroDeBytes);
      #endif
      break;
    }
    
    numeroDeBytes--;


    if(!numeroDeBytes)
    {
      pacoteBase32[pacote + 1] = BASE32[(hexaBytes[contador] << 2 & 0x1C) + (hexaBytes[contador+1] >> 6 & 0x03) + variavelAlfabeto32];
      pacoteBase32[pacote + 2] = BASE32[(hexaBytes[contador+1] >> 1 & 0x1F) + variavelAlfabeto32];
      pacoteBase32[pacote + 3] = BASE32[(hexaBytes[contador+1] << 4 & 0x10) + (hexaBytes[contador+2] >> 4 & 0x0F) + variavelAlfabeto32];
      pacoteBase32[pacote + 4] = BASE32[(hexaBytes[contador+2] << 1 & 0x1E) + (hexaBytes[contador+3] >> 7 & 0x01) + variavelAlfabeto32];
      pacoteBase32[pacote + 5] = BASE32[(hexaBytes[contador+3] >> 2 & 0x1F) + variavelAlfabeto32];
      pacoteBase32[pacote + 6] = BASE32[(hexaBytes[contador+3] << 3 & 0x18) + variavelAlfabeto32];
      #ifdef DEPURACAO
      printf ("\n-------4-------\n");
      printf ("pacoteBase32[%u] : %c\n",pacote    , pacoteBase32[pacote]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 1, pacoteBase32[pacote + 1]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 2, pacoteBase32[pacote + 2]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 3, pacoteBase32[pacote + 3]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 4, pacoteBase32[pacote + 4]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 5, pacoteBase32[pacote + 5]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 6, pacoteBase32[pacote + 6]);
      printf ("pacoteBase32[%u] : %c\n",pacote + 7, pacoteBase32[pacote + 7]);
      printf ("Numero de bytes : %llu",numeroDeBytes);
      #endif
      break;
    }
    
    numeroDeBytes--;


    pacoteBase32[pacote + 1] = BASE32[(hexaBytes[contador] << 2 & 0x1C) + (hexaBytes[contador+1] >> 6 & 0x03) + variavelAlfabeto32];
    pacoteBase32[pacote + 2] = BASE32[(hexaBytes[contador+1] >> 1 & 0x1F) + variavelAlfabeto32];
    pacoteBase32[pacote + 3] = BASE32[(hexaBytes[contador+1] << 4 & 0x10) + (hexaBytes[contador+2] >> 4 & 0x0F) + variavelAlfabeto32];/* esta passando como se fosse 0 no byte ... X0 */
    pacoteBase32[pacote + 4] = BASE32[(hexaBytes[contador+2] << 1 & 0x1E) + (hexaBytes[contador+3] >> 7 & 0x01) + variavelAlfabeto32];
    pacoteBase32[pacote + 5] = BASE32[(hexaBytes[contador+3] >> 2 & 0x1F) + variavelAlfabeto32];
    pacoteBase32[pacote + 6] = BASE32[(hexaBytes[contador+3] << 3 & 0x18) + (hexaBytes[contador+4] >> 5 & 0x07) + variavelAlfabeto32];
    pacoteBase32[pacote + 7] = BASE32[(hexaBytes[contador+4] & 0x1F) + variavelAlfabeto32];
   
    #ifdef DEPURACAO
    printf ("\n--------5---------\n");
    printf ("pacoteBase32[%u] : %c\n",pacote    , pacoteBase32[pacote]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 1, pacoteBase32[pacote + 1]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 2, pacoteBase32[pacote + 2]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 3, pacoteBase32[pacote + 3]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 4, pacoteBase32[pacote + 4]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 5, pacoteBase32[pacote + 5]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 6, pacoteBase32[pacote + 6]);
    printf ("pacoteBase32[%u] : %c\n",pacote + 7, pacoteBase32[pacote + 7]);

    printf ("Numero de bytes : %llu\n",numeroDeBytes);
    printf ("Somou pacote\n");
    #endif
    
    pacote += 8;
    
  }

  return ok;
}

tipoErros
DecodificarBase32 (char *codigoBase32,               /* (E) */
		tipoAlfabetoBase32 estadoAlfabeto32, /* (E) */
		byte *hexaByteEquivalente,           /* (S) */
		unsigned long long *numeroDeBytes)   /* (S) */
{
  unsigned int contador, contador2, contadorBase32, compatibilidade;
  unsigned int variavelAlfabeto32 = 0;
  unsigned int numeroDePad = 0;
  unsigned long long copiaNumeroDeBytes;
  byte octetoDeCaracteres[8];

	  #ifdef DEPURACAO
  printf ("\nDecodificarBase32\n");
  #endif

  if (!codigoBase32)
    return enderecoInvalido;

  if ( strlen(codigoBase32) % 8 )
    return codigoBase32Invalido;

  for (contador = 0; contador < strlen(codigoBase32); contador++)
    if ( codigoBase32[contador] == '=' )
      numeroDePad++;

  if (numeroDePad == 6)
    numeroDePad = 4;

  else if (numeroDePad == 4)
    numeroDePad = 3;

  else if (numeroDePad == 3)
    numeroDePad = 2;
  
  else; /*numeroDePad == 1 permanece*/

  copiaNumeroDeBytes = (strlen(codigoBase32)/8) * 5 - numeroDePad;
  
  #ifdef DEPURACAO
  printf ("Numero de Bytes : (%llu)\n", copiaNumeroDeBytes);
  #endif

  *numeroDeBytes = copiaNumeroDeBytes;

  if (estadoAlfabeto32 == estendido)
    variavelAlfabeto32 = 32;

  #ifdef DEPURACAO
  printf ("\nvariavelAlfabeto32 : %u\n",variavelAlfabeto32);
  #endif
  
  for (contador = 0; contador < strlen(codigoBase32); contador += 8) /* For principal */
  {
    for (contador2 = 0; contador2 < 8; contador2++) 
    {
      #ifdef DEPURACAO
      printf ("\nContador : (%u)\n",contador);
      #endif

      compatibilidade = 0;
      
      if ( codigoBase32[contador2] == '=') break;

      else	    
        for ( contadorBase32 = 0; contadorBase32 < 32; contadorBase32++)
          if ( codigoBase32[contador2 + contador] == BASE32[contadorBase32 + variavelAlfabeto32] ) {
            octetoDeCaracteres[contador2] = contadorBase32;
            compatibilidade++;
	  }

          if (!compatibilidade)
            return codigoBase32Invalido;
          
          #ifdef DEPURACAO
          printf ("Octeto[%u] = ContadorBase32 : (%u)\n", contador2 ,octetoDeCaracteres[contador2]);
          #endif
    }
    
    contador *= 5;
    contador /= 8; /* sempre mantem multiplo de 5 para escrever no local correto */ 
    #ifdef DEPURACAO
    printf ("\nContador antes da escrita: (%u)\n",contador);
    #endif

    hexaByteEquivalente[contador + 0] = (octetoDeCaracteres[0] << 3 & 0xF8) + (octetoDeCaracteres[1] >> 2 & 0x07);
    #ifdef DEPURACAO
    printf ("HexaByteEquivalente[%u] : (%u)\n",contador+0, hexaByteEquivalente[contador+0]);
    #endif
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    hexaByteEquivalente[contador + 1] = (octetoDeCaracteres[1] << 6 & 0xC0) + (octetoDeCaracteres[2] << 1 & 0x3E) + (octetoDeCaracteres[3] >> 4 & 0x01);
    #ifdef DEPURACAO
    printf ("HexaByteEquivalente[%u] : (%u)\n",contador+1, hexaByteEquivalente[contador+1]);
    #endif
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    hexaByteEquivalente[contador + 2] = (octetoDeCaracteres[3] << 4 & 0xF0) + (octetoDeCaracteres[4] >> 1 & 0x0F);
    #ifdef DEPURACAO
    printf ("HexaByteEquivalente[%u] : (%u)\n",contador+2, hexaByteEquivalente[contador+2]);
    #endif
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    hexaByteEquivalente[contador + 3] = (octetoDeCaracteres[4] << 7 & 0x80) + (octetoDeCaracteres[5] << 2 & 0x7C) + (octetoDeCaracteres[6] >> 3 & 0x03);
    #ifdef DEPURACAO
    printf ("HexaByteEquivalente[%u] : (%u)\n",contador+3, hexaByteEquivalente[contador+3]);
    #endif
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    hexaByteEquivalente[contador + 4] = (octetoDeCaracteres[6] << 5 & 0xE0) + (octetoDeCaracteres[7] & 0x1F);
    #ifdef DEPURACAO
    printf ("HexaByteEquivalente[%u] : (%u)\n",contador+4, hexaByteEquivalente[contador+4]);
    #endif
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;
    
    contador *= 8;
    contador /= 5; /* retornando ao valor que sera usado na identificacao dos octetos */

  } /* For principal */
  
  #ifdef DEPURACAO
  printf ("Todos os bytes quivalentes foram calculados | ");
  #endif

  return ok;  
}

tipoErros
CodificarBase64 (byte * hexaBytes,                /* (E) */
		unsigned long long numeroDeBytes, /* (E) */
		tipoFinalLinha quebrarLinha,      /* (E) */
		char *codigoBase64)               /* (S) */
{
  unsigned int contador, contadorDeQuebra, pacote;
  unsigned long long copiaNumeroDeBytes;

  if (!hexaBytes){
    return enderecoInvalido;
  }

  copiaNumeroDeBytes = numeroDeBytes;
  pacote = 0;
  contadorDeQuebra = 0;

  for (contador = 0; contador < numeroDeBytes; contador += 3)
  {
    codigoBase64[pacote + 2] = '=';
    codigoBase64[pacote + 3] = '=';

    codigoBase64[pacote + 0] = BASE64[ hexaBytes[contador + 0] >> 2 & 0x3F ];
    codigoBase64[pacote + 1] = BASE64[ hexaBytes[contador + 0] << 4 & 0x30 ];
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    codigoBase64[pacote + 1] = BASE64[(hexaBytes[contador + 0] << 4 & 0x30) + (hexaBytes[contador + 1] >> 4 & 0x0F)];
    codigoBase64[pacote + 2] = BASE64[ hexaBytes[contador + 1] << 2 & 0x3C ];
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;
    
    codigoBase64[pacote + 2] = BASE64[(hexaBytes[contador + 1] << 2 & 0x3C) + (hexaBytes[contador + 2] >> 6 & 0x03)];
    codigoBase64[pacote + 3] = BASE64[ hexaBytes[contador + 2]      & 0x3F ];
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    pacote += 4;
    contadorDeQuebra += 4;

    if (quebrarLinha)
      if ( !(contadorDeQuebra%76) ) {
        codigoBase64[pacote + 0] = '\n';
	codigoBase64[pacote + 1] = '\t';
        pacote += 2;
      }

  }

  return ok;
}


tipoErros
DecodificarBase64 (char *codigoBase64,                /* (E) */
		   tipoFinalLinha quebrarLinha,       /* (E) */
		   byte *byteEquivalente,             /* (S) */
		   unsigned long long *numeroDeBytes) /* (S) */
{
  unsigned int contador, contador2, contadorBase64, compatibilidade;
  unsigned int numeroDePad = 0;
  unsigned long long copiaNumeroDeBytes;
  byte quartetoDeCaracteres[4];

  #ifdef DEPURACAO
  printf ("\nDecodificarBase64\n");
  #endif

  if ( !codigoBase64 )
    return enderecoInvalido;
  #ifdef DEPURACAO
  printf ("\nEnderecoInvalido.\n");
  #endif

  if ( strlen(codigoBase64) % 4 ){
    return codigoBase64Invalido;
    #ifdef DEPURACAO
    printf ("\nCodigo nao eh multiplo de 4.\n");
    #endif
  }

  for (contador = 0; contador < strlen(codigoBase64); contador++)
    if ( codigoBase64[contador] == '=' ) {
      numeroDePad++;
  }

  copiaNumeroDeBytes = (strlen(codigoBase64)/4) * 3 - numeroDePad;
  
  if ( quebrarLinha == habilitado )
    copiaNumeroDeBytes -= (strlen(codigoBase64)/76) * 2;
  

  #ifdef DEPURACAO
  printf ("Numero de Bytes : (%llu)\n", copiaNumeroDeBytes);
  #endif

  *numeroDeBytes = copiaNumeroDeBytes;

  for (contador = 0; contador < strlen(codigoBase64); contador += 4) /* For principal */
  {
    for (contador2 = 0; contador2 < 4; contador2++) 
    {
      #ifdef DEPURACAO
      printf ("\nContador : (%u)\n",contador);
      #endif
      
      compatibilidade = 0;

      if ( quebrarLinha == habilitado )
        if ( codigoBase64[contador2] == '\n' )
          contador2 += 2;	
      
      if ( codigoBase64[contador2] == '=') break;
      
      else	    
        for ( contadorBase64 = 0; contadorBase64 < 64; contadorBase64++)
          if ( codigoBase64[contador2 + contador] == BASE64[contadorBase64] ) {
            quartetoDeCaracteres[contador2] = contadorBase64;
            compatibilidade++;
	  }
          
          if (!compatibilidade){
            return codigoBase64Invalido;
            #ifdef DEPURACAO
            printf ("ERRO (Incompativel) | contador (%u) | contador2 (%u) | Quarteto[%u] = ContadorBase64 : (%u)\n",contador, contador2 , contador2 ,quartetoDeCaracteres[contador2]);
            #endif
	  }
  
          #ifdef DEPURACAO
          printf ("Quarteto[%u] = ContadorBase64 : (%u)\n", contador2 ,quartetoDeCaracteres[contador2]);
          #endif
    }
    
    contador *= 3;
    contador /= 4; /* sempre mantem multiplo de 3 para escrever no local correto */ 
    #ifdef DEPURACAO
    printf ("\nContador antes da escrita: (%u)\n",contador);
    #endif

    byteEquivalente[contador + 0] = (quartetoDeCaracteres[0] << 2 & 0xFC) + (quartetoDeCaracteres[1] >> 4 & 0x03);
    #ifdef DEPURACAO
    printf ("ByteEquivalente[%u] : (%u)\n",contador+0, byteEquivalente[contador+0]);
    #endif
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    byteEquivalente[contador + 1] = (quartetoDeCaracteres[1] << 4 & 0xF0) + (quartetoDeCaracteres[2] >> 2 & 0x0F);
    #ifdef DEPURACAO
    printf ("ByteEquivalente[%u] : (%u)\n",contador+1, byteEquivalente[contador+1]);
    #endif
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    byteEquivalente[contador + 2] = (quartetoDeCaracteres[2] << 6 & 0xC0) + (quartetoDeCaracteres[3]);
    #ifdef DEPURACAO
    printf ("ByteEquivalente[%u] : (%u)\n",contador+2, byteEquivalente[contador+2]);
    #endif
    copiaNumeroDeBytes--;
    if (!copiaNumeroDeBytes) break;

    contador *= 4;
    contador /= 3; /* retornando ao valor que sera usado na identificacao dos quartetos */

  } /* For principal */
  
  #ifdef DEPURACAO
  printf ("Todos os bytes quivalentes foram calculados | ");
  #endif


  return ok;
}

