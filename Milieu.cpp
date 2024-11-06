#include "Milieu.h"
#include "Factory.h"

#include <cstdlib>
#include <ctime>
#include <memory>
#include <vector>



const T    Milieu::white[] = { (T)255, (T)255, (T)255 };


Milieu::Milieu( int _width, int _height, double pNaissance, double pClonage ) : UImg( _width, _height, 1, 3 ),
                                            width(_width), height(_height)
{

   cout << "const Milieu" << endl;
   std::srand( time(NULL) );

   // init du temps qui va défiler, itération à chaque boucle dans le Aquarium::run
   temps = 0;
   //Affectation des attributs de proban initialisation du nb de mort
   probaNaissance = pNaissance;
   probaClonage = pClonage;
   nbMort = 0;
}

Milieu::~Milieu( void )
{

   cout << "dest Milieu" << endl;

}

// Implémente une pas de simulation en simulant le comportement de chaque bestiole de la liste
void Milieu::step( void )
{

   cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
   for ( std::list<std::shared_ptr<Bestiole>>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it )
   {
      // Gestion de la mort de vieillesse
      if ((*it)->checkMort( *this )){
         if (it == std::prev(listeBestioles.end())){  // Si c'est le dernier élément de la liste, on le supprime et on repasse au premier
            listeBestioles.erase(it);
            it = listeBestioles.begin();}

         else { it = listeBestioles.erase(it);}  // sinon on le supprime et on passe au suivant
         nbMort++;      // On itère le nombre de mort
      }

      //Clonage : tirage d'un nb entre 0 et 1
      double random = static_cast<double>(std::rand()) / RAND_MAX;

      // comparaison de ce nombre avec probaClone 
      
      if (random < probaClonage){
         //Clonage de la bestiole et ajout dans la liste
         std::shared_ptr<Bestiole> sharedPtr((*it)->clone());
         listeBestioles.push_back(sharedPtr);
      }
/*
      // Naissance : même principe
      random = static_cast<double>(std::rand()) / RAND_MAX;
      if (random < probaNaissance) { 
         std::shared_ptr<Bestiole> sharedPtr2 (f.naissance());
            listeBestioles.push_back(sharedPtr2);
      }

*/
      // Gestion de la confrontation
      fight(it, listeBestioles);

      // appels des fonction faisant bouger et affichant la bestiole
      (*it)->action( *this );
      (*it)->draw( *this );


   }

}


// True si la distance entre les centres de 2 bestioles est inférieure à 2 rayons
bool Milieu::checkCollision( std::shared_ptr<Bestiole> b1, std::shared_ptr<Bestiole> b2)
{
   if (b1 == b2) { return false; }   // Si bestioles identiques, pas de collision
   else {
      int X1 = b1->getX();
      int X2 = b2->getX();
      int Y1 = b1->getY();
      int Y2 = b2->getY();

      return (std::sqrt((X1 - X2)*(X1 - X2) + (Y1 - Y2)*(Y1 - Y2)) < 8.) ;  // 8 est le rayon d'affiche des bestioles
      }
}


// Si 2 bestioles se rencontrent, calcul de celle qui remporte la collision
void Milieu::fight(std::list<std::shared_ptr<Bestiole>>::iterator& it, std::list<std::shared_ptr<Bestiole>>& liste){
   
   for ( std::list<std::shared_ptr<Bestiole>>::iterator it2 = liste.begin() ; it2 != liste.end() ; ++it2 ){
      if (checkCollision(*it, *it2)){

         int R1 = (*it)->getResistance();
         int R2 = (*it2)->getResistance();
         int O1 = (*it)->getOrientation();
         int O2 = (*it2)->getOrientation();

            // 1 gagne
         if (R1 > R2) {
            if (it2 == std::prev(liste.end())) {    // évite les problèmes de fuite si suppression du dernier élément
               listeBestioles.erase(it2);
               it2 = liste.begin(); }

            else {
               it2 = listeBestioles.erase(it2);   // Si élément quelconque, suppression et passage au prochain
            }

            (*it)->setOrientation(M_PI + O1);      // orientation inversée pour la gagnante 
            nbMort++;                              // Itération du nombre de mort
            
         }

            //2 gagne
         else if (R1 < R2) {
            if (it == std::prev(liste.end())) {    // évite les problèmes de fuite si suppression du dernier élément
               listeBestioles.erase(it);
               it = liste.begin(); }
               
            else {
               it = listeBestioles.erase(it);      // Si élément quelconque, suppression et passage au prochain
            }

            (*it2)->setOrientation(M_PI + O2);     // orientation inversée pour la gagnante 
            nbMort++;                              // Itération du nombre de mort
            
         }
            //égalité
         else if (R1 == R2) {
            (*it)->setOrientation( M_PI + O1);
            (*it2)->setOrientation(M_PI + O2);
         }
      }
   }

}

// Itération du temps du milieu, appel dans la fonction Aquarium::run
void Milieu::iterTime(){
   temps = temps +1;
}


int Milieu::getTime(){
   return temps;
}

std::list<std::shared_ptr<Bestiole>> Milieu::getBestioles(){
   return listeBestioles;
}
int Milieu::getNbMort(){
   return nbMort;
}
