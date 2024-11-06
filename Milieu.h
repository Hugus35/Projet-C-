#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"
#include "Factory.h"

#include <iostream>
#include <vector>
#include <list>
#include <memory>

using namespace std;


class Milieu : public UImg
{

private :
   static const T          white[];

   int                     width, height;       //Taille du milieu

   int                     temps;               //Temps de la simulation, iter à chaque pas
   double                  probaNaissance;      // Proba de naissance d'une bestiole à chaque instant 
   double                  probaClonage;        // Proba de clonage d'une bestiole à chaque instant 
   int                     nbMort;              //nb total de mort
   //Factory*                Factory;

   
   std::list<std::shared_ptr<Bestiole>>   listeBestioles;  // La liste de bestiole du milieu est une liste de shared_ptr afin de faciliter la gestion de la mémoire
                                                            // Principalement lors des destruction

public :
   Milieu( int _width, int _height, double probaNaissance, double probaClonage);
   ~Milieu( void );

   void step( void );  // Gestion d'un pas de simulation

   void addMember2( std::shared_ptr<Bestiole> b) { listeBestioles.push_back(b); listeBestioles.back()->initCoords(width, height); } // Ajout d'une bestiole

   bool checkCollision( std::shared_ptr<Bestiole> b1, std::shared_ptr<Bestiole> b2 );  // true si 2 bestioles se rencontrent, false sinon

   void fight(std::list<std::shared_ptr<Bestiole>>::iterator& it, std::list<std::shared_ptr<Bestiole>>& liste);  // Résultat d'une collision

   // getters / setters

   int getWidth( void ) const { return width; };
   int getHeight( void ) const { return height; };

   int getTime();
   void iterTime();
   std::list<std::shared_ptr<Bestiole>> getBestioles();
   int getNbMort();


};


#endif
