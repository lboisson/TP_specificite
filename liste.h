#ifndef _LISTE_H_
#define _LISTE_H_

#include <commun.h>

#define LISTE_NULL NULL
#define LISTE_ID_NULL -1


typedef struct liste_s
{
  int nb ;		/* Nombre d'objets dans la liste  */
  void ** liste ;	/* liste  des objets */
  int taille; /* Taille d'une élément */
  err_t (*affectation)(void * const, void * const); /* Pointeur vers la fonction d'affectation */
  err_t (*destruction)(void * const);
} liste_t ;

typedef enum type_tri_s {
	QUICK,
	PERSO
} type_tri_t;

extern unsigned long int liste_cpt  ;

/*
 * FONCTIONS
 */

/*!
 * \name Methodes d'acces
 * @{
 */

/*! Acces au nombre d'objets */
extern int liste_nb_lire( liste_t * const liste );

/*! Acces a un objets de la liste */
extern void * liste_elem_lire( liste_t * const liste , const int ind );

/*!
 * @}
 * \name Tests
 * @{
 */

/*! Teste si la liste existe */
extern booleen_t liste_existe( liste_t * const liste) ;

/*! Teste si la liste est vide (aucun &eacute;l&eacute;ment dedans) */
extern booleen_t liste_vide( liste_t * const liste) ;

/*!
 * @}
 * \name Methodes d'affectations
 * @{
 */

/*! Affectation d'un objet */
extern err_t liste_elem_ecrire( liste_t * liste,
				void * const elem ,
				const int ind ) ;

/*!
 * @}
 * \name Primitives
 * @{
 */

/*!
 * Creation d'une liste
 */
 extern liste_t * liste_creer( const int nb,
              const int taille,
              err_t (*affectation)(void * const, void * const),
              err_t (*destruction)(void * const));
/*!
 * Destruction d'une liste
 */

extern err_t liste_detruire( liste_t ** liste) ;


/*!
 * \name Affichage
 * @{
 */

/*!
 * Affichage d'une liste sur la sortie standard
 */

extern void liste_afficher( liste_t * const liste , void (*afficher)(const void * const));

/*!
 * @}
 */


/*!
 * tri d'une liste
 */
extern err_t liste_trier( liste_t * const liste, int (*comparer)( const void * const, const void * const), int extra_arg, ...);

/*! @} */
#endif
