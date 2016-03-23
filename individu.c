#include <stdlib.h>
#include <string.h>
#include <individu.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int individu_cpt = 0 ;

/*
 * FONCTIONS
 */

extern
booleen_t individu_existe( individu_t * const individu )
{
  if( individu == NULL )
    return(FAUX) ;
  else
    return(VRAI) ;
}

extern
err_t individu_detruire( individu_t ** individu )
{

  /* Liberation attributs */
  free( (*individu)->nom ) ;
  free( (*individu)->prenom ) ;
  /* Liberation memoire de l'objet */
  free( (*individu) ) ;
  /* Pour eviter les pointeurs fous */
  (*individu) = NULL ;

  individu_cpt-- ;

  return(OK) ;
}

extern
err_t individu_deref(individu_t ** individu) {
  *individu=NULL;
  return OK;
}

extern
void individu_afficher( individu_t * const individu )
{

  printf( "{" ) ;
  if(  individu_existe(individu) )
    {
      printf( "%s %s" , individu->prenom , individu->nom ) ;
    }
  printf( "}" ) ;
}

extern
void individu_afficher_2( individu_t * const individu )
{

  printf( "{" ) ;
  if(  individu_existe(individu) )
    {
      printf( "%s %s" , individu->prenom , individu->nom ) ;
    }
  printf( "}\n" ) ;
}

extern
individu_t * individu_creer( char * const prenom , char * const nom )
{
  individu_t * individu = NULL ;

  /* Creation place memoire objet individu */
  if( ( individu = malloc(sizeof(individu_t)) ) == NULL )
    {
      fprintf( stderr , "individu_creer: debordement memoire lors de la creation d'un objet de type individu_t (%lu demandes)\n",
	       (unsigned long int)sizeof(individu_t) ) ;
      return((individu_t *)NULL);
    }

  /* Affectation attributs specifiques */
  if( ( individu->nom = malloc( sizeof(char)*strlen(nom)+1) ) == NULL )
    {
      fprintf( stderr , "individu_creer: debordement memoire lors de la creation du nom d'un individu_t (%lu demandes)\n",
	       (unsigned long int)sizeof(char)*strlen(nom)+1 ) ;
      return((individu_t *)NULL);
    }

  if( ( individu->prenom = malloc( sizeof(char)*strlen(prenom)+1) ) == NULL )
    {
      fprintf( stderr , "individu_creer: debordement memoire lors de la creation du prenom d'un individu_t (%lu demandes)\n",
	       (unsigned long int)sizeof(char)*strlen(prenom)+1 ) ;
      return((individu_t *)NULL);
    }

  strcpy( individu->nom , nom );
  strcpy( individu->prenom , prenom ) ;

  individu_cpt++ ;

  return( individu ) ;
}

extern
int individu_comparer( const individu_t * const ind1 , const individu_t * const ind2 )
{
  int cmp = strcmp( ind1->nom , ind2->nom )  ;
  if( cmp ) return(cmp);
  return( strcmp( ind1->prenom , ind2->prenom ) ) ;
}

/* Inverse la fonction comparer pour faire un tri dans l'autre sens*/
extern
int individu_comparer_inv( const individu_t ** const i1 , const individu_t ** const i2 ) {
  return individu_comparer(*i2, *i1);
}

/* Fonction comparer avec doubles pointeurs */
extern
int individu_comparer_bis( const individu_t ** const i1 , const individu_t ** const i2 ) {
  return individu_comparer(*i1, *i2);
}

extern err_t individu_copie(individu_t * const source, individu_t ** const destination){

  if(((*destination)=malloc(sizeof(individu_t)))==NULL){
    printf("Debordement mémoire lors de la copie d'un individu\n");
    return ERROR;
  }

  if(((*destination)->nom=malloc(sizeof(char) * strlen(source->nom)+1))==NULL){
    printf("Debordement mémoire lors de la copie d'un individu\n");
    free(*destination);
    *destination=NULL;
    return ERROR;
  }
  strcpy((*destination)->nom, source->nom);

  if(((*destination)->prenom=malloc(sizeof(char) * strlen(source->prenom)+1))==NULL){
    printf("Debordement mémoire lors de la copie d'un individu\n");
    free((*destination)->nom);
    free(*destination);
    *destination=NULL;
    return ERROR;
  }
  strcpy((*destination)->prenom, source->prenom);
  return OK;
}

extern
err_t individu_affect(individu_t * const source, individu_t ** const destination){
  *destination=source;
  return OK;
}
