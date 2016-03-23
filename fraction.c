#include <stdlib.h>
#include <string.h>
#include <fraction.h>


/*
 * VARIABLE LOCALE
 */

unsigned long int fraction_cpt = 0 ;

/*
 * FONCTIONS
 */

extern
booleen_t fraction_existe( fraction_t * const fraction )
{
  if( fraction == NULL )
    return(FAUX) ;
  else
    return(VRAI) ;
}

extern
err_t fraction_detruire( fraction_t ** fraction )
{

  /* Liberation attributs */
  /* Liberation memoire de l'objet */
  free( (*fraction) ) ;
  /* Pour eviter les pointeurs fous */
  (*fraction) = NULL ;

  fraction_cpt-- ;

  return(OK) ;
}

extern
err_t fraction_deref(fraction_t ** fraction) {
  *fraction=NULL;
  return OK;
}

extern
void fraction_afficher( fraction_t * const fraction )
{

  printf( "{" ) ;
  if(  fraction_existe(fraction) )
    {
      printf( "%d/%d" , fraction->numerateur , fraction->denominateur ) ;
    }
  printf( "}" ) ;
}

extern
void fraction_afficher_2( fraction_t * const fraction )
{

  printf( "{" ) ;
  if(  fraction_existe(fraction) )
    {
      printf( "%d/%d" , fraction->numerateur , fraction->denominateur ) ;
    }
  printf( "}\n" ) ;
}

extern
fraction_t * fraction_creer( const int numerateur , const int denominateur )
{
  fraction_t * fraction = NULL ;

  /* Creation place memoire objet fraction */
  if( ( fraction = malloc(sizeof(fraction_t)) ) == NULL )
    {
      fprintf( stderr , "fraction_creer: debordement memoire lors de la creation d'un objet de type fraction_t (%lu demandes)\n",
	       (unsigned long int)sizeof(fraction_t) ) ;
      return((fraction_t *)NULL);
    }

  /* Affectation attributs specifiques */
  fraction->numerateur = numerateur;
  fraction->denominateur = denominateur ;

  fraction_cpt++ ;

  return( fraction ) ;
}

extern
int fraction_comparer( const fraction_t * const f1 , const fraction_t * const f2 )
{
  float r1 = (float) f1->numerateur / f1->denominateur  ;
  float r2 = (float) f2->numerateur / f2->denominateur  ;
  if( r1 == r2 ) return(0) ;
  if( r1 > r2 )  return(1) ;
  return(-1) ;
}

/* Inverse la fonction comparer pour faire un tri dans l'autre sens*/
extern
int fraction_comparer_inv( const fraction_t ** const f1 , const fraction_t ** const f2 ) {
  return fraction_comparer(*f2, *f1);
}

/* LA fonction comparer avec double pointeur */
extern
int fraction_comparer_bis( const fraction_t ** const f1 , const fraction_t ** const f2 ) {
  return fraction_comparer(*f1, *f2);
}

extern
err_t fraction_copie(fraction_t * const source, fraction_t ** const destination){

  if(((*destination)=malloc(sizeof(fraction_t)))==NULL){
    printf("Debordement mémoire lors de la copie d'un fraction\n");
    return ERROR;
  }

  (*destination)->numerateur=source->numerateur;
  (*destination)->denominateur=source->denominateur;
  return OK;
}

extern
err_t fraction_affect(fraction_t * const source, fraction_t ** const destination){
  *destination=source;
  return OK;
}
