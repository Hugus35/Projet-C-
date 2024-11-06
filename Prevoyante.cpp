#include "Prevoyante.h"
#include "Milieu.h"
#include <iostream>

#include <cstdlib>
#include <cmath>


//Le constructeur de prevoyante appelle simplement le constructeur définit dans "bestiole", avec la couleur correspondant à cette espèce
Prevoyante::Prevoyante() : Bestiole(200, 200, 200) {} //Prevoyante Blanche

// Constructeur par copie : il est appelé dans la fonction clonage et fais appel au constructeur par copie de bestiole, prenant en entrée une prevoyante
Prevoyante::Prevoyante(const Prevoyante & b ) : Bestiole(b) {}

Prevoyante::~Prevoyante(){
    cout << "Dest prevoyante" << endl;
}

// Fonction bouge de la prevoyante : on redéfinit celle de bestiole avec le comportement spécifique de la prevoyante
void Prevoyante::bouge( int xLim, int yLim, Milieu& monMilieu )
{
   double         nx, ny;

   // Comportement spécifique
   orientation = angleMoyen(monMilieu);
   
   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;


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

// clonage d'une prevoyante : on redéfinit le clone de bestiole, et on retourne un pointeur vers une prevoyante.
// Pour ce, on appelle simplement le constructeur par copie de prevoyante
Bestiole* Prevoyante::clone() const{
   return new Prevoyante(*this);
}


//Calcule la direction moyenne des bestioles vues et entendues par la bestiole en question, retourne l'angle opposé à cette direction
double Prevoyante::angleMoyen(Milieu& monMilieu){

   std::list<std::shared_ptr<Bestiole>> listeBestioles = monMilieu.getBestioles();
   double total = 0;
   double cpt = 0;
   
   for ( std::list<std::shared_ptr<Bestiole>>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){

      if (this->jeTentends((*it)) || this->jeTeVois((*it))){  // Si la bestiole voit ou entend une autre bestiole, elle la prend en compte dans son estimation
         total+= (*it)->getOrientation();
         cpt += 1;
      }
    }

   if (cpt != 0) {return total/cpt + M_PI;}
   else {return orientation;}    // si pas de voisins, la bestiole continue sa trajectoire
}