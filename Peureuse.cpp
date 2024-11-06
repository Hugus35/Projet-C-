#include "Peureuse.h"
#include "Milieu.h"
#include <iostream>

#include <cstdlib>
#include <cmath>
#include <list>
#include <memory>

//Le constructeur de peureuse appelle simplement le constructeur définit dans "bestiole", avec la couleur correspondant à cette espèce
Peureuse::Peureuse() : Bestiole(0, 200, 0) {} //Peureuses vertes

// Constructeur par copie : il est appelé dans la fonction clonage et fais appel au constructeur par copie de bestiole, prenant en entrée une peureuse
Peureuse::Peureuse(const Peureuse & b ) : Bestiole(b) {}

// Destructeur peureuse
Peureuse::~Peureuse(){
    cout << "Dest peureuse" << endl;
}

// Fonction bouge de la peureuse : on redéfinit celle de bestiole avec le comportement spécifique de la peureuse
void Peureuse::bouge( int xLim, int yLim, Milieu& monMilieu )
{

   double         nx, ny;
   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;

   // caractère spécifique aux peureuses
   if (nbVoisins(monMilieu) >= 3){
      orientation = M_PI + orientation;
      dx = 5*dx;
      dy = 5*dy;

      //cout << "fuite d'une peureuse" << endl; 
   }

   //cout << orientation << endl;
   cx = static_cast<int>( cumulX ); cumulX -= cx;  // cx est la partie fractionnaire accumulée
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = x + dx + cx;   //nx est la nouvelle position
   ny = y + dy + cy;

   if ( (nx < 0) || (nx > xLim - 1) ) {
      orientation = M_PI - orientation;
      cumulX = 0.;
   }
   else {
      x = static_cast<int>( nx );
      cumulX += nx - x;
   }

   if ( (ny < 0) || (ny > yLim - 1) ) {
      orientation = -orientation;
      cumulY = 0.;
   }
   else {
      y = static_cast<int>( ny );
      cumulY += ny - y;
   }
}

// calcule le nombre de voisins de la peureuse pour qu'elle fuit si elle dépasse un seuil
int Peureuse::nbVoisins(Milieu& monMilieu)
{

   int         nb = 0;
   std::list<std::shared_ptr<Bestiole>> listeBestioles = monMilieu.getBestioles();

   for ( std::list<std::shared_ptr<Bestiole>>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
      if ( this->jeTeVois(*it) && this->jeTentends(*it) ){
         ++nb;
      }

   return nb;

}

// clonage d'une peureuse : on redéfinit le clone de bestiole, et on retourne un pointeur vers une peureuse.
// Pour ce, on appelle simplement le constructeur par copie de peureuse
Bestiole* Peureuse::clone() const{
   return new Peureuse(*this);
}