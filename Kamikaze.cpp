#include "Kamikaze.h"
#include "Milieu.h"
#include <iostream>

#include <cstdlib>
#include <cmath>
#include <list>
#include <memory>


//Le constructeur de kamikaze appelle simplement le constructeur définit dans "bestiole", avec la couleur correspondant à cette espèce
Kamikaze::Kamikaze() : Bestiole(0, 0, 200) {}   //Kamikaze bleues

// Constructeur par copie : il est appelé dans la fonction clonage et fais appel au constructeur par copie de bestiole, prenant en entrée une kamikaze
Kamikaze::Kamikaze(const Kamikaze & b ) : Bestiole(b) {}

Kamikaze::~Kamikaze(){
    cout << "Dest Kamikaze" << endl;
}
// Fonction bouge de la kamikaze : on redéfinit celle de bestiole avec le comportement spécifique de la kamikaze

void Kamikaze::bouge( int xLim, int yLim, Milieu& monMilieu )
{

   double         nx, ny;

   // Spécifique à kamikaze
   orientation = plusProche(monMilieu);   // changement de l'orientation pour se diriger vers la bestiole la plus proche

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

// clonage d'une kamikaze : on redéfinit le clone de bestiole, et on retourne un pointeur vers une kamikaze.
// Pour ce, on appelle simplement le constructeur par copie de kamikaze
Bestiole* Kamikaze::clone() const{
   return new Kamikaze(*this);
}

// utile dans bouge, définit l'angle nécessaire pour s'orienter vers la bestiole la plus proche
double Kamikaze::plusProche(Milieu& monMilieu){
   
   std::list<std::shared_ptr<Bestiole>> listeBestioles = monMilieu.getBestioles();
   double distMin = 1000;  //grande distance pour commencer

   int XpProche = 0;
   int YpProche = 0;           // abscisse et ordonnées de la bestiole la plus proche

   for ( std::list<std::shared_ptr<Bestiole>>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){
      
      double  dist = std::sqrt( (x-(*it)->getX())*(x-(*it)->getX()) + (y-(*it)->getY())*(y-(*it)->getY()));   // distance entre notre bestiole et celle de la liste

      if (this->jeTentends((*it)) || this->jeTeVois((*it))){
         if (dist < distMin) {  // si une bestiole est plus proche que la précédente plus proche, 
            dist = distMin;    //remplacement de la distance et pointage de "plusProche" sur cette bestiole
            XpProche = (*it)->getX();
            YpProche = (*it)->getY();
         }
      }
   }
   
   double angle = std::atan(-(y - YpProche)/ (0.0001 + x - XpProche));  // angle entre notre bestiole et la plus proche, pour qu'elle se dirige vers elle
   return angle;
}