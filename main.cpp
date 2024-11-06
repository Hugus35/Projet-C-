#include "Aquarium.h"
#include "Milieu.h"
#include "Bestiole.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Prevoyante.h"
#include "Kamikaze.h"
#include "Factory.h"

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

using namespace std;


int main()
{
   // Interface avec le client, toutes les grandeurs relatives à une simulation doivent être saisies ci-dessous

   // Durée de la simulation
   int durée = 2000;

   // Proportions de chaque espèce
   int nbGregaire = 40;
   int nbPeureuse = 40;
   int nbPrevoyante = 40;
   int nbKamikaze = 40;

   //Proba d'un clonage et d'une naissance à chaque instant de la simulation
   double probaClonage = 0.0001;
   double probaNaissance = 0.1;

   // valeurs limites capteurs et accessoires

   int etaMax = 10;      //Réduction vitesse due à une carapace
   int omegaMax = 5;    //Augmentation résistance due à une carapace

   int muMax = 5;      // Augmentation vitesse due  à des nageoires

   double phiMin = 0.1;  // Camouflage : double entre 0 et 1
   double phiMax = 0.9;

   double deltaOmin = 75;   //Distance de détection oreilles
   double deltaOmax = 150;
   double gammaOmin = 0.5;   //Capacité de détection oreilles (entre 0 et 1)
   double gammaOmax = 0.95;


   double deltaYmin = 75;   //Distance de détection yeux
   double deltaYmax = 150;
   double gammaYmin = 0.5;   //Capacité de détection yeux (entre 0 et 1)
   double gammaYmax = 0.9;
   double alphaMin = -10;     //angle de détection yeux (en radians)  
   double alphaMax = 10;






   // Construction de l'aquarium contenant l'ecosysteme
   Aquarium* ecosysteme = new Aquarium( 640, 480, 30, probaNaissance, probaClonage);

   //Construction de la factory nous permettant d'initialiser l'environnement avec les deux fonctions ci-dessous
   Factory* f1 = new Factory(nbGregaire, nbPeureuse, nbPrevoyante, nbKamikaze, etaMax, 
                              omegaMax, muMax, phiMin, phiMax, deltaOmin, deltaOmax, gammaOmin, gammaOmax,
                              deltaYmin, deltaYmax, gammaYmin, gammaYmax, alphaMin, alphaMax);
   
   f1->init(*ecosysteme);
   f1->initAccessories(*ecosysteme);

   // Appel de la boucle permettant de modéliser l'évolution des bestioles. A chaque tour, elle simule le comportement de chaque bestiole
   ecosysteme->run(durée);


   return 0;

}
