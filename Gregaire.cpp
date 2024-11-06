#include "Gregaire.h"
#include "Milieu.h"
#include <iostream>

#include <cstdlib>
#include <cmath>
#include <list>
#include<memory>

//Le constructeur de grégaire appelle simplement le constructeur définit dans "bestiole", avec la couleur correspondant à cette espèce

Gregaire::Gregaire() : Bestiole(200, 0, 0) {} // gregaire rouge 

// Constructeur par copie : il est appelé dans la fonction clonage et fais appel au constructeur par copie de bestiole, prenant en entrée une gregaire

Gregaire::Gregaire(const Gregaire & b ) : Bestiole(b) {}

// Destructeur grégaire
Gregaire::~Gregaire(){
    cout << "Dest gregaire" << endl;
    //nbMortGreg++;
};

// Fonction bouge de la grégaire : on redéfinit celle de bestiole avec le comportement spécifique de la grégaire
void Gregaire::bouge( int xLim, int yLim, Milieu& monMilieu )
{

   double         nx, ny;

   // caractère spécifique aux grégaires
   orientation = this->angleMoyen(monMilieu);  // moyenne environnante

   double         dx = cos( orientation )*vitesse;
   double         dy = -sin( orientation )*vitesse;
   int            cx, cy;

   //cout << orientation << endl;
   cx = static_cast<int>( cumulX ); cumulX -= cx;  // cx est la partie fractionnaire accumulée
   cy = static_cast<int>( cumulY ); cumulY -= cy;

   nx = x + dx + cx;   //nx est la nouvelle position
   ny = y + dy + cy;

// Cas de collision avec un bord

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

// clonage d'une grégaire : on redéfinit le clone de bestiole, et on retourne un pointeur vers une grégaire.
// Pour ce, on appelle simplement le constructeur par copie de grégaire

Bestiole* Gregaire::clone() const{
   return new Gregaire(*this);
}


//Calcule la direction moyenne des bestioles vues et entendues par la bestiole en question
double Gregaire::angleMoyen(Milieu& monMilieu){
   std::list<std::shared_ptr<Bestiole>> listeBestioles = monMilieu.getBestioles();
   double total = 0;
   double cpt = 0;
   
   for ( std::list<std::shared_ptr<Bestiole>>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){

      if (this->jeTentends((*it)) || this->jeTeVois((*it))){   // Si la bestiole voit ou entend une autre bestiole, elle la prend en compte dans son estimation
         total+= (*it)->getOrientation();
         cpt += 1;
      }
    }

   if (cpt != 0) {return total/cpt;}  // retourne l'orientation moyenne autour
   else {return orientation;}    // si pas de voisins, la bestiole continue sa trajectoire
}
