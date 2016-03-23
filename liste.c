#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <liste.h>

#include <stdarg.h>

/*
 * VARIABLE LOCALE
 */

unsigned long int liste_cpt = 0 ;

/*
 * Methodes d'acces
 */

/* Nombre d'elements */

extern
int liste_nb_lire( liste_t * const liste )
{
  return(liste->nb );
}

/* -- Acces individuel a un element */

extern
void * liste_elem_lire( liste_t * const liste  , const int ind )
{
  if( (ind < 0) || (ind > liste_nb_lire(liste)-1 ) )
    {
      fprintf( stderr , "liste_elem_lire: mauvais indice d'element [%d] (devrait etre dans [%d..%d])\n",
	       ind , 0 , liste_nb_lire(liste)-1 );
      return(NULL);
    }

  return( liste->liste[ind] ) ;
}

/*
 * Tests
 */

extern
booleen_t liste_existe( liste_t * const liste )
{
  if( liste == NULL )
    {
      return(FAUX) ;
     }
  else
    {
      return(VRAI) ;
    }
}

extern
booleen_t liste_vide( liste_t * const liste )
{
  if( liste->nb == 0 )
    {
      return(VRAI) ;
    }
  else
    {
      return(FAUX) ;
    }
}

/*
 * Methodes d'affectation
 */


/* -- Acces individuel a un element */
extern
err_t liste_elem_ecrire( liste_t * liste , void * const elem, const int ind ) {

#ifdef _DEBUG_
  if( (ind < 0) || (ind > liste_nb_lire(liste) ) )
    {
      fprintf( stderr , "liste_elem_ecrire: mauvais indice d'element [%d] (devrait etre dans [%d..%d]\n",
	       ind , 0 , liste_nb_lire(liste) );
      return(ERR_LISTE_IND_ELEM);
    }
#endif
  liste->affectation(elem, liste->liste+ind);

  return(OK) ;
}

/*
 * Creation d'une liste
 */
extern
liste_t * liste_creer( const int nb, const int taille, err_t (*affectation)(void * const, void * const), err_t (*destruction)(void * const))
{
  liste_t * liste ;

  if(( liste= malloc(sizeof(liste_t))) == NULL )
    {
      fprintf( stderr , "liste_creer: debordement memoire lors de la creation d'une liste\n");
      return((liste_t *)NULL);
    }

  liste->nb = nb ;
  liste->affectation=affectation;
  liste->destruction=destruction;
  liste->liste = (void**)NULL ;
  liste->taille = taille;
  if( nb > 0 )
    {
      if( ( liste->liste = malloc( sizeof(void *) * nb ) ) == NULL )
	{
	  fprintf( stderr , "liste_creer: debordement memoire lors de la creation d'une liste\n");
	  free( liste ) ;
	  return((liste_t *)NULL);
	}
    }

  liste_cpt++;

  return(liste);
}

/*
 * Destruction d'une liste
 *
 * A FAIRE
 */

extern
err_t liste_detruire( liste_t ** liste)
{
  int i;
  if(!liste_existe(*liste)){
    return ERROR;
  }
  int nb_obj=(*liste)->nb;
  for(i=0;i<nb_obj;i++){
    (*liste)->destruction((*liste)->liste+i);
  }
  free((*liste)->liste);
  free(*liste);
  *liste=NULL;
  liste_cpt--;
  return(OK) ;
}


/*
 * Affichage d'une liste sur la sortie standard
 *
 * A FAIRE
 *
 */

extern
void liste_afficher( liste_t * const liste , void (*afficher)(const void * const))
{
  int i;
  if(liste_existe(liste)){
    int nb_obj=liste->nb;
    for(i=0; i<nb_obj; i++)
      afficher(liste->liste[i]);
  }
}

/*
 * Tri d'une liste
 *
 * A FAIRE
 *
 */

static
err_t liste_trier_bulle(liste_t * const liste, int (*comparer)( const void * const, const void * const) ) {

    int i = 0 ;
    int taille = liste->taille;
    int pas_trier=1;
    void * w;
    int nb = liste->nb;
    if((w=malloc(taille))==NULL) {
        return ERROR;
    }

    while(pas_trier==1) {
      for(i=0; i<nb-1;i++) {
        if( comparer( liste->liste+i , liste->liste+i+1 ) > 0 ) {
      	  memcpy( w , liste->liste[i] , taille ) ;
      	  memcpy( liste->liste[i] , liste->liste[i+1] , taille ) ;
      	  memcpy( liste->liste[i+1] , w , taille ) ;
      	}
        else
          pas_trier=0;
      }
    }
  free(w) ;
  return OK;
 }

static
err_t liste_trier_qsort(liste_t * const liste, int (*comparer)( const void * const, const void * const)){
  qsort(liste->liste, liste->nb, sizeof(void *), comparer);
  return OK;
}

extern
err_t liste_trier( liste_t * const liste, int (*comparer)( const void * const, const void * const), int extra_arg, ...)
{
  va_list args;
	type_tri_t type;
	if (extra_arg) {
		va_start(args, extra_arg);
		type = va_arg(args, type_tri_t);
		va_end(args);
	} else {
		type = QUICK;
	}
	switch (type) {
		case QUICK:
			return liste_trier_qsort(liste, comparer);
		case PERSO:
			return liste_trier_bulle(liste, comparer);
		default:
			return ERROR;
	}
}
