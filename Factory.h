#ifndef FACTORY
#define FACTORY

#include "UImg.h"
#include "Bestiole.h"
#include <iostream>
#include <Aquarium.h>
//#include <memory>


//class Milieu;
using namespace std;


class Factory{

private:

// Nombres de chaque espèce
int nbGregaire;
int nbPeureuse;
int nbPrevoyante;
int nbKamikaze;


//valeurs limites capteurs & accessoires

//carapace
int etaMax;  // Coef de ralentissement
int omegaMax; // Coef de résistance

//nageoires
int muMax;      // Coef de vitesse

//Camouflage
double phiMin;  //Valeur min du coef camouflage (entre 0 et 1)
double phiMax;  // Valeur max

//Oreilles
double deltaOmin;  //Plage de distance
double deltaOmax;
double gammaOmin;  // plage de capacité de détection
double gammaOmax;

//Yeux
double deltaYmin;   //Plage de distance
double deltaYmax;
double gammaYmin;   //Plage de perception
double gammaYmax;
double alphaMin;    // Plage d'angle de vue
double alphaMax;

public:

    Factory(int nbG, int nbPeur, int nbPrev, int nbK, int eMax, int oMax, 
            int muMax, double pMin, double pMax, double dOmin, double dOmax, double gOmin, double gOmax,
            double dYmin, double dYmax, double gYmin, double gYmax, double aMin, double aMax) ;
    ~Factory();


    void init(Aquarium& ecosysteme);        // création des bestioles présentes à l'origine
    void initAccessories(Aquarium& ecosysteme);     //affectation des accessoires
    Bestiole* naissance();                      // naissance individuelle




};




#endif
