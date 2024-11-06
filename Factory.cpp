#include "Factory.h"
#include "Gregaire.h"
#include "Peureuse.h"
#include "Prevoyante.h"
#include "Kamikaze.h"
#include "Bestiole.h"
#include "Milieu.h"
#include "Aquarium.h"

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <memory>

// constructeur de la factory, affectation de chaque attribut à l'aide des paramètres du constructeur
Factory::Factory(int nbG, int nbPeur, int nbPrev, int nbK, int eMax, int oMax, int vMax, double pMin, 
double pMax, double dOmin, double dOmax, double gOmin, double gOmax, double dYmin, double dYmax, double gYmin, 
double gYmax, double aMin, double aMax ){
    nbGregaire = nbG;
    nbPeureuse = nbPeur;
    nbPrevoyante = nbPrev;
    nbKamikaze = nbK;
    etaMax = eMax;
    omegaMax = oMax;
    muMax = vMax;
    phiMin = pMin;
    phiMax = pMax;
    deltaOmin = dOmin;
    deltaOmax = dOmax;
    gammaOmin = gOmin;
    gammaOmax = gOmax;
    deltaYmin = dYmin;
    deltaYmax = dYmax;
    gammaYmin = gYmin;
    gammaYmax = gYmax;
    alphaMin = aMin;
    alphaMax = aMax;

}

// Destructeur
Factory::~Factory(){
    std::cout << "Factory destroyed" << std::endl;
}


// Initialisation : ajout des bestioles dans le milieu
void Factory::init(Aquarium& ecosysteme){
    
    for (int i = 0; i < nbGregaire; ++i) {
        ecosysteme.getMilieu().addMember2(std::make_shared<Gregaire>());
    }

    for (int i = 0; i < nbPeureuse; ++i) {
        ecosysteme.getMilieu().addMember2(std::make_shared<Peureuse>());
    }

    for (int i = 0; i < nbPrevoyante; ++i) {
        ecosysteme.getMilieu().addMember2(std::make_shared<Prevoyante>());
    }

    for (int i = 0; i < nbKamikaze; ++i) {
        ecosysteme.getMilieu().addMember2(std::make_shared<Kamikaze>());
    } 
    
}



// Fonction qui va ajouter chaque accessoire à chaque bestiole, si elle en possède
// Pour cela, appels successifs de chaque fonction set pour chaque bestiole
void Factory::initAccessories(Aquarium& ecosysteme){

    std::list<std::shared_ptr<Bestiole>> listeBestioles = ecosysteme.getMilieu().getBestioles();

     for ( std::list<std::shared_ptr<Bestiole>>::iterator it = listeBestioles.begin() ; it != listeBestioles.end() ; ++it ){
        (*it)->setCarapace(etaMax, omegaMax);
        (*it)->setNageoires(muMax);
        (*it)->setCamouflage(phiMin, phiMax);
        (*it)->setOreilles(deltaOmin, deltaOmax, gammaOmin, gammaOmax);
        (*it)->setYeux(deltaYmin, deltaYmax, gammaYmin, gammaYmax, alphaMin, alphaMax);
        
     }

}

// Naissance d'une bestiole, la probabilité du type est proportionnel au nombre de bestiole dans le milieu
Bestiole* Factory::naissance(){
    int total = nbGregaire + nbPeureuse + nbPrevoyante + nbKamikaze;
    //quel type ?  tirage d'un nb entre 0 et 1
    double random = static_cast<double>(std::rand()) / RAND_MAX;
    
    if (random <= nbGregaire/total) {return new Gregaire(); }
    else if (random > nbGregaire/total && random <= (nbGregaire + nbPeureuse)/total ) {return new Peureuse();}
    else if (random > (nbGregaire + nbPeureuse)/total && random <= (nbGregaire + nbPeureuse + nbPrevoyante)/total) {return new Prevoyante();}
    else {return new Kamikaze(); } 

}
