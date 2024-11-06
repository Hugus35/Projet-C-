#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_


#include "UImg.h"

#include <iostream>

using namespace std;


class Milieu;


class Bestiole
{

private :
//Valeurs limites lors des tirages d'attributs aléatoires
   static const double     AFF_SIZE;
   static const double     MAX_VITESSE;
   static const double     LIMITE_VUE;

   static const double     LIMITE_AGE;
   static const double     LIMITE_RESISTANCE;

// itérateur pour affecter l'identité d'une bestiole
   static int              next;

protected :       //Protected pour que les classes filles aient accès à ces infos (fonction bouge etc)
   int               identite;
   int               x, y;
   double            cumulX, cumulY;
   double            orientation;
   double            vitesse;
   int               ageMort;
   double            resistance;
  
   
private:

   // Accessoires ?
   bool              carapace;
   bool              nageoires;
   bool              camouflage;
   double            coefCamouflage;

   // Capteurs ?
   bool              yeux;
   bool              oreilles;

   double            deltaO;
   double            gammaO;

   double            alpha;
   double            deltaY;
   double            gammaY;

   T               * couleur;

private :
   virtual void bouge( int xLim, int yLim, Milieu& monMilieu ) = 0;   // On va redéfinir la fonction bouge pour chaque classe fille qui bougeront à sa manière

public :                                           // Forme canonique :
   Bestiole( int R, int V, int B );        
   Bestiole( void );                               // Constructeur par defaut
   Bestiole( const Bestiole & b );                 // Constructeur de copies
   virtual ~Bestiole( void ) {};                   // Destructeur virtuel
                                                   
   void action( Milieu & monMilieu );
   void draw( UImg & support );

   bool jeTeVois( std::shared_ptr<Bestiole> b ) const;      // Vue d'une bestiole ayant des yeux
   bool jeTentends( std::shared_ptr<Bestiole> b ) const;    //Entente d'une bestiole ayant des oreilles

   void initCoords( int xLim, int yLim );

   friend bool operator==( const Bestiole & b1, const Bestiole & b2 );


   bool checkMort(Milieu & monMilieu);

   // implémentation du DP prototype : la fonction clone est redéfinie pour chaque classe fille, faisant appel au constructeur par copie de chacun

   virtual Bestiole* clone() const = 0;

   // Accessoires
   void tirage(); // Utile pour le tirage des booléens indiquant si une bestiole comporte tel accessoires, appel dans le constructeur
   

   // Si une bestiole comporte tel accesoire, ces fonctions affectent ses valeurs caractéristiques
   // Elles sont appelées successivement dans le setAccessories de la factory
   void setCarapace(int etaMax, int omegaMax);
   void setNageoires(int vMax);
   void setCamouflage(double phiMin, double phiMax);
   void setOreilles(double deltaOmin, double deltaOmax, double gammaOmin, double gammaOmax);
   void setYeux(double deltaYmin, double deltaYmax, double gammaYmin, double gammaYmax, double alphaMin, double alphaMax);

 // Getters/setters
   int getX();
   int getY();
   int getResistance();
   void setOrientation(int o);
   int getOrientation();   

};



#endif