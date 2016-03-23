#include <stdlib.h>
#include <string.h>
#include <mystring.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int string_cpt = 0 ;

/*
 * FONCTIONS
 */

extern
booleen_t string_existe( string_t * const string )
{
  if( string == NULL )
    return(FAUX) ;
  else
    return(VRAI) ;
}

extern
err_t string_detruire( string_t ** string )
{

  /* Liberation attributs */
  free( (*string)->string ) ;
  /* Liberation memoire de l'objet */
  free( (*string) ) ;
  /* Pour eviter les pointeurs fous */
  (*string) = NULL ;

  string_cpt-- ;

  return(OK) ;
}

extern
err_t string_deref(string_t ** string) {
  *string=NULL;
  return OK;
}

extern
void string_afficher( string_t * const string )
{

  printf( "{" ) ;
  if(  string_existe(string) )
    {
      printf( "%s" , string->string) ;
    }
  printf( "}" ) ;
}

extern
void string_afficher_2( string_t * const string )
{

  printf( "{" ) ;
  if(  string_existe(string) )
    {
      printf( "%s" , string->string) ;
    }
  printf( "}\n" ) ;
}

extern
string_t * string_creer( char * const chaine )
{
  string_t * string = NULL ;

  /* Creation place memoire objet string */
  if( ( string = malloc(sizeof(string_t)) ) == NULL )
    {
      fprintf( stderr , "string_creer: debordement memoire lors de la creation d'un objet de type string_t (%lu demandes)\n",
	       (unsigned long int)sizeof(string_t) ) ;
      return((string_t *)NULL);
    }

  /* Affectation attributs specifiques */
  if( ( string->string = malloc(sizeof(char)*strlen(chaine)+1) ) == NULL )
    {
      fprintf( stderr , "string_creer: debordement memoire lors de la creation d'un objet de type string_t (%lu demandes)\n",
	       (unsigned long int)strlen(chaine)+1 ) ;
      return((string_t *)NULL);
    }
  strcpy( string->string , chaine ) ;

  string_cpt++ ;

  return( string ) ;
}

extern
int string_comparer( const string_t * const str1 , const string_t * const str2 )
{
  return(strcmp( str1->string , str2->string) ) ;
}

/* Inverse la fonction comparer pour faire un tri dans l'autre sens*/
extern
int string_comparer_inv( const string_t ** const s1 , const string_t ** const s2 ) {
  return string_comparer(*s2, *s1);
}

/* Fonction comparer avec doubles pointeurs */
extern
int string_comparer_bis( const string_t ** const s1 , const string_t ** const s2 ) {
  return string_comparer(*s1, *s2);
}

extern
err_t string_copie(string_t * const source, string_t ** const destination){

  if(((*destination)=malloc(sizeof(string_t)))==NULL){
    printf("Debordement mémoire lors de la copie d'un string\n");
    return ERROR;
  }

  if(((*destination)->string=malloc(sizeof(char) * strlen(source->string)+1))==NULL){
    printf("Debordement mémoire lors de la copie d'un string\n");
    free(*destination);
    *destination=NULL;
    return ERROR;
  }
  strcpy((*destination)->string, source->string);

  return OK;
}

extern
err_t string_affect(string_t * const source, string_t ** const destination){
  *destination=source;
  return OK;
}
