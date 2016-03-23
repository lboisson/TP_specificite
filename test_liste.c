#include <stdio.h>
#include <stdlib.h>

#include <individu.h>
#include <fraction.h>
#include <mystring.h>
#include <liste.h>

#include <string.h>
#include <getopt.h>
#include <stdbool.h>

/* ------------------------------ */
/* ----- long options array ----- */
/* ------------------------------ */

static struct option longopts[] =
{
  {"verbose", no_argument, NULL, (int)'v'},
  {"tri", required_argument, NULL, (int)'t'},
  {"help", no_argument, NULL, (int)'h'},
  {0, 0, 0, 0}
};

/*
 * Usage
 */
static
void usage( char * nomprog )
{
      fprintf( stdout , "usage : %s [nombre d'objets] [options]\n" , nomprog );
      fprintf( stdout , "Options:\n");
      fprintf( stdout , " --verbose        niveau de la trace de l'execution\n");
      fprintf( stdout , " --tri=0          tri de type qsort\n");
      fprintf( stdout , " --tri=1          tri de type perso\n");
      fprintf( stdout , " --help           ouvre l'aide\n");
}

int
main(int argc, char * argv[])
{
  err_t noerr = OK;

  individu_t ** individus = NULL  ;
  fraction_t ** fractions = NULL  ;
  string_t ** strings = NULL  ;

  liste_t * liste = NULL ;
  int i=0;

  int opt;
  char nomprog[512] ;
  bool verbose=false; /* booleen qu'on met à vrai si l'option verbose est activée */
  type_tri_t tri = QUICK;
  int sort = 0;

  /* Section parametre */
  if(argc<2 || argc>4){
    fprintf( stderr , "Erreur sur le nombre de parametres: 1, 2 ou 3 attendus au lieu de %d\n" , argc-1 );
    usage(nomprog) ;
    exit(0) ;
  }

  /* Section options */
  strcpy( nomprog , argv[0] ) ;
  while ((opt = getopt_long(argc, argv, "vt:h", longopts, NULL)) != -1 ) {
      switch(opt){
      	case 'v': /* --verbose */
      	  verbose=true; break;

        case 't': /* --tri */
          sort = atoi(optarg);
          switch (sort) {
            case 0 :
              tri = QUICK; break;
            case 1 :
              tri = PERSO; break;
            default :
              fprintf( stderr, "Erreur de la valeur de tri\n");
              usage(nomprog); exit(0);
          }
          break;


        case 'h': /* --help */
  	      usage(nomprog) ;
  	      exit(0);
  	      break;

      	default:
      	  usage(nomprog) ;
      	  exit(0);
      	  break;
	      }
      }
  argc -= optind ;
  argv += optind ;
  /* argc == nb de parametres sans le nom de la commande */
  /* argv[0] --> 1er parametre */

  if(argc==0){
    usage(nomprog);
    exit(0);
  }

  const int N = atoi(argv[0]);
  if(N<=0){
    fprintf( stderr , "Erreur sur le paramètre du nombre d'objets, \"%s\" invalide\n", argv[0]);
    usage(nomprog);
    exit(0);
  }

  individus = malloc( sizeof(individu_t *) * N )  ;
  fractions = malloc( sizeof(fraction_t *) * N )  ;
  strings = malloc( sizeof(string_t *) * N )   ;

  printf( "Debut du programme des test sur les listes de %d objets homogenes\n" , N ) ;

  if(verbose){
    printf( "\nTest creation d'une liste de %d individus \n" , N );
  }

  char prenom[128] ;
  char nom[128] ;
  liste = liste_creer(N, sizeof(individu_t), (err_t (*)(void * const, void * const))individu_affect, (err_t (*)(void * const))individu_deref) ;
  for( i=0 ; i<N ; i++ )
    {
      sprintf( nom , "nom_%d" , N-i ) ;
      sprintf( prenom , "prenom_%d" , N-i ) ;
      individus[i] = individu_creer( prenom , nom ) ;
      liste_elem_ecrire( liste , individus[i] , i ) ;
    }

  if(verbose) {
    printf( "Test affichage liste d'individus AVANT tri \n" ) ;
    liste_afficher( liste , (void (*)(const void * const))individu_afficher ) ;
    printf( "\n");

    printf( "Test Tri de la liste des individus\n" );
  }
  liste_trier(liste, (int (*)(const void * const, const void * const)) individu_comparer_bis, 1, tri) ;

  if(verbose) {
    printf( "Test affichage liste d'individus APRES tri\n" ) ;
    liste_afficher( liste , (void (*)(const void * const))individu_afficher ) ;
    printf( "\n");

    printf( "Test destruction liste d'individus\n" ) ;
  }

  if( ( noerr = liste_detruire( &liste ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }
  if(verbose) {
    printf( "\nTest creation d'une liste de %d fractions \n" , N ) ;
  }
  liste = liste_creer(N, sizeof(fraction_t), (err_t (*)(void * const, void * const))fraction_copie, (err_t (*)(void * const))fraction_detruire) ;
  for( i=0 ; i<N ; i++ )
    {
      fractions[i] = fraction_creer( N-i , N-i+1 ) ;
      liste_elem_ecrire( liste , fractions[i] , i ) ;
    }

  if(verbose) {
    printf( "Test affichage liste de fractions AVANT tri\n" ) ;
    liste_afficher( liste , (void (*)(const void * const))fraction_afficher_2 ) ;
    printf( "\n");

    printf( "Test Tri de la liste des fractions\n" );
  }

  liste_trier(liste, (int (*)(const void * const, const void * const)) fraction_comparer_bis, 1, tri) ;

  if(verbose) {
    printf( "Test affichage liste des fractions APRES tri\n" ) ;
    liste_afficher( liste , (void (*)(const void * const))fraction_afficher_2 ) ;
    printf( "\n");

    printf( "Test destruction liste de fractions\n" ) ;
  }

  if( ( noerr = liste_detruire( &liste ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }

  if(verbose){
    printf( "\nTest creation d'une liste de %d strings \n" , N ) ;
  }

  char string[128] ;
  liste = liste_creer(N, sizeof(string_t), (err_t (*)(void * const, void * const))string_copie, (err_t (*)(void * const))string_detruire) ;
  for( i=0 ; i<N ; i++ )
    {
      sprintf( string , "string_%d" , N-i ) ;
      strings[i] = string_creer( string ) ;
      liste_elem_ecrire( liste , strings[i] , i ) ;
    }

  if(verbose) {
    printf( "Test affichage liste de strings AVANT tri\n" ) ;
    liste_afficher( liste , (void (*)(const void * const))string_afficher ) ;
    printf( "\n");

    printf( "Test Tri bulle de la liste des strings\n" );
  }

  liste_trier(liste, (int (*)(const void * const, const void * const)) string_comparer_bis, 1, tri ) ;

  if(verbose){
    printf( "Test affichage liste des strings APRES tri\n" ) ;
    liste_afficher( liste , (void (*)(const void * const))string_afficher ) ;
    printf( "\n");

    printf( "Test destruction liste de strings\n" ) ;
  }

  if( ( noerr = liste_detruire( &liste  ) ) )
    {
      printf("Sortie avec code erreur = %d\n" , noerr ) ;
      return(noerr) ;
    }

  /* Destructions des éléments d'origine que l'on a copié dans les listes */
  for(i=0;i<N;i++) {
    individu_detruire(individus + i);
  }
  free( individus ) ;
  for(i=0;i<N;i++) {
    fraction_detruire(fractions + i);
  }
  free( fractions ) ;
  for(i=0;i<N;i++) {
    string_detruire(strings + i);
  }
  free( strings ) ;

  printf( "\nFin du programme des test sur la lste d'objets homogenes\n" ) ;

  if(verbose){
    printf( "Nombre de liste_t  = %lu\n" , liste_cpt ) ;
  }

  return(0) ;
}
