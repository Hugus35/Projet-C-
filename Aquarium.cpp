#include "Aquarium.h"
//#include "Factory.h"

#include "Milieu.h"

// Construction de l'aquarium avec sa taille, le délai entre 2 pas, et les probas de naissance et clonage
Aquarium::Aquarium( int width, int height, int _delay, double pNaissance, double pClonage) : CImgDisplay(), delay( _delay )
{

   int         screenWidth = 1280; //screen_width();
   int         screenHeight = 1024; //screen_height();


   cout << "const Aquarium" << endl;
   
   flotte = new Milieu( width, height, pNaissance, pClonage);  // Les valeurs sont prises en arguments pas le constructeur du milieu contenu par l'aquarium
   assign( *flotte, "Simulation d'ecosysteme" );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2) );

}

// Destructeur de l'aquarium
Aquarium::~Aquarium( void )
{

   delete flotte;

   cout << "dest Aquarium" << endl;

}

// Fonctionmment de la simulation : appel de Milieu::step à chaque pas de simulation, tant que l'interface n'est pas fermée
void Aquarium::run( int durée)
{

   cout << "running Aquarium" << endl;

   while ( ! is_closed() && flotte->getTime() < durée)
   {

      //cout << "iteration de la simulation" << endl;

      if ( is_key() ) {
         cout << "Vous avez presse la touche " << static_cast<unsigned char>( key() );
         cout << " (" << key() << ")" << endl;
         if ( is_keyESC() ) close();
      }

   // Appel de step qui va simuler le comportement de chaque bestiole du mileu, affiche ces bestioles et iter le temps du milieu

      flotte->step();
      display( *flotte );
      flotte->iterTime();

   // Affiche le temps
      cout << flotte->getTime() << endl;

      wait( delay );

   } // while

   cout << "Fin de la simulation" << endl;
   cout << "Nombre de mort : " << flotte->getNbMort() << endl;
   //cout << "Dont " << getMort()
   close();
}
