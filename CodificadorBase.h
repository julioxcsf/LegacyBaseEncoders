/**************************************************
 *
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e Computacao
 * Autor: Julio Cesar Silva Fernandes
 * Descricao: arquivo .h que possui o prototipo das
 * seguntes funcoes:
 * 1 - CodificarBase16
 * 2 - DecodificarBase16
 * 3 - CodificarBase32
 * 4 - DecofificarBase32
 * 5 - CodificarBase64
 * 6 - DecodificarBase64
 *
 **************************************************/

typedef enum
{
  ok,
  enderecoInvalido,
  codigoBase16Invalido,
  codigoBase32Invalido,
  codigoBase64Invalido,
  erro
}
tipoErros;

typedef enum
{
  basico,
  estendido
}
tipoAlfabetoBase32;

typedef enum
{
  desabilitado,
  habilitado
}
tipoFinalLinha;

typedef unsigned char byte;

tipoErros
CodificarBase16 ( byte * ,                 /* (E) */
                  unsigned long long,      /* (E) */
                  char * );                /* (S) */

tipoErros
DecodificarBase16 (char * ,                /* (E) */
                   byte * ,                /* (S) */
                   unsigned long long * ); /* (S) */

tipoErros
CodificarBase32 (byte *,                   /* (E) */
		 unsigned long long,               /* (E) */
		 tipoAlfabetoBase32,               /* (E) */
		 char * );                         /* (S) */

tipoErros
DecodificarBase32 (char *,                 /* (E) */
		   tipoAlfabetoBase32,             /* (E) */
		   byte *,                         /* (S) */
		   unsigned long long *);          /* (S) */

tipoErros
CodificarBase64 (byte *,                   /* (E) */
		unsigned long long,                /* (E) */
		tipoFinalLinha,                    /* (E) */
		char *);                           /* (S) */

tipoErros
DecodificarBase64 (char *,                 /* (E) */
		   tipoFinalLinha,                 /* (E) */
		   byte *,                         /* (S) */
		   unsigned long long *);          /* (S) */


#endif

