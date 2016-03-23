#ifndef _FRACTION_H_
#define _FRACTION_H_

#include <commun.h>

/*
 * DEFINITION OBJET "INDIVIDU"
 */

typedef struct fraction_s
{
  int numerateur ;
  int denominateur ;
} fraction_t ;

/*
 * VARIABLE LOCALE
 * declaration du compteur d'objets fraction_t comme variable externe
 * pour compter les references sur ces objets
 */

extern unsigned long int fraction_cpt  ;

/*
 * FONCTIONS
 */

/* Creation */
extern fraction_t * fraction_creer(const int numerateur , const int denominateur ) ;
/* Test existance */
extern booleen_t fraction_existe( fraction_t * const fraction ) ;
/* Destructions */
extern err_t fraction_detruire( fraction_t ** fraction ) ;
/* Affichages */
extern void fraction_afficher( fraction_t * const fraction ) ;
extern void fraction_afficher_2( fraction_t * const fraction );
/* Comparaisons */
extern int fraction_comparer( const fraction_t * const f1 , const fraction_t * const f2 ) ;

extern int fraction_comparer_inv( const fraction_t ** const f1 , const fraction_t ** const f2 );

extern int fraction_comparer_bis( const fraction_t ** const f1 , const fraction_t ** const f2 );

extern err_t fraction_copie(fraction_t * const source, fraction_t ** const destination);

extern err_t fraction_deref(fraction_t ** fraction);

extern err_t fraction_affect(fraction_t * const source, fraction_t ** const destination);

#endif
