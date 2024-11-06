#include "Bestiole.h"

#include "Milieu.h"

#include <cstdlib>
#include <cmath>

// Affectation des valeurs limite des bestioles
const double      Bestiole::AFF_SIZE = 8.;
const double      Bestiole::MAX_VITESSE = 10.;
const double      Bestiole::LIMITE_VUE = 30.;
const double      Bestiole::LIMITE_AGE = 5000.;
const double      Bestiole::LIMITE_RESISTANCE = 10.;

// init de l'itérateur pour l'identité de la bestiole
int               Bestiole::next = 0;




// Constructeur pas défaut, on ne l'utilise pas dans la simulation
Bestiole::Bestiole( void )
{

   identite = ++next;

   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;

   couleur = new T[ 3 ];
   couleur[ 0 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 1 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );
   couleur[ 2 ] = static_cast<int>( static_cast<double>( rand() )/RAND_MAX*230. );

}

// Constructeur pour mettre la couleur souhaitée 
// Dans chaque constructeur de classe fille, on l'appelle avec la couleur caractéristique du type (rouge pour grégaire par ex)
Bestiole::Bestiole( int R, int V, int B )
{

   identite = ++next;

   cout << "const Bestiole (" << identite << ") par defaut" << endl;

   x = y = 0;
   cumulX = cumulY = 0.;
   orientation = static_cast<double>( rand() )/RAND_MAX*2.*M_PI;
   vitesse = static_cast<double>( rand() )/RAND_MAX*MAX_VITESSE;   // choisit une vitesse entre 0 et MAX_VITESSE

   // tirage de l'âge max sous LIMITE_AGE (5000) (une loi normale serait mieux)
   ageMort = static_cast<double>( rand() )/RAND_MAX*LIMITE_AGE;
   resistance = static_cast<double>( rand() )/RAND_MAX*LIMITE_RESISTANCE;

   //Pas de camouflage initial, donc coef à zéro. Il changera si un camouflage = true
   coefCamouflage = 0;

   // tirage des accessoires, cette fonction affecte ensuite chaque attribut booléen 
   this->tirage();

   
   //implémentation des couleurs passées en entrée
   couleur = new T[ 3 ];
   couleur[ 0 ] = R;
   couleur[ 1 ] = V;
   couleur[ 2 ] = B;

}

// Le constructeur par copie va servir pour le clonage, on implémente le DP prototype
Bestiole::Bestiole( const Bestiole & b )
{

   identite = ++next;

   cout << "const Bestiole (" << identite << ") par copie" << endl;

   // Copie de chaque attribut passé en entrée
   x = b.x;
   y = b.y;
   cumulX = cumulY = 0.;
   orientation = M_PI + b.orientation; //On inverse l'orientation lors d'un clonage
   vitesse = b.vitesse;
   ageMort = b.ageMort;
   resistance = b.resistance;
   carapace = b.carapace;
   nageoires = b.nageoires;
   camouflage = b.camouflage;
   coefCamouflage = b.coefCamouflage;
   yeux = b.yeux;
   oreilles = b.oreilles;
   deltaO = b.deltaO;
   gammaO = b.gammaO;
   deltaY = b.deltaY;
   gammaY = b.gammaY;
   alpha = b.alpha;


   couleur = new T[ 3 ];
   memcpy( couleur, b.couleur, 3*sizeof(T) );

}

// Init des coordonnées au sein des valeurs limites de l'aquarium
void Bestiole::initCoords( int xLim, int yLim )
{

   x = rand() % xLim;
   y = rand() % yLim;

}

// Appel de la fonction bouge (passée dans chaque classe fille) avec en arguments les limites du milieu
void Bestiole::action( Milieu & monMilieu )
{

   bouge( monMilieu.getWidth(), monMilieu.getHeight(), monMilieu );

}

// Affiche la bestiole à chaque instant selon sa taille et sa position
void Bestiole::draw( UImg & support )
{

   double         xt = x + cos( orientation )*AFF_SIZE/2.1;
   double         yt = y - sin( orientation )*AFF_SIZE/2.1;


   support.draw_ellipse( x, y, AFF_SIZE, AFF_SIZE/5., -orientation/M_PI*180., couleur );
   support.draw_circle( xt, yt, AFF_SIZE/2., couleur );

}


bool operator==( const Bestiole & b1, const Bestiole & b2 )
{

   return ( b1.identite == b2.identite );

}

// retourne le booléen de si une bestiole est dans le champ de vision ou non
bool Bestiole::jeTeVois( std::shared_ptr<Bestiole> b ) const
{
   double         vecX; // coordonnées X du vecteur entre les deux bestioles
   double         vecY; // coordonnées Y
   double         dist; // distance entre les deux bestioles
   double         theta; // angle du vecteur 
   
   vecX = x - b->x;
   vecY = y - b->y;  
   theta = std::atan(-vecY/vecX);   // - car l'axe Y est orienté vers le bas
   dist = std::sqrt( (x-b->x)*(x-b->x) + (y-b->y)*(y-b->y) );

   if (dist <= deltaY && !(operator==(*this, *b))){       // condition de distance + si les bestioles sont différentes
      if (theta < fmod(orientation + alpha/2, 2*M_PI)  && theta > fmod(orientation - alpha/2, 2*M_PI && gammaY > b->camouflage)){    // condition d'angle et de camouflage
         return true;
      }
      else {return false;}
   }
   else {return false;}
}


// détection de A sur B à l'aide de ses oreilles : B doit être dans le champ de A, et sa capacité de camouflage inférieure à la capacité de détection
bool Bestiole::jeTentends( std::shared_ptr<Bestiole> b ) const
{

   double         dist;
   //Bestiole* ptr = this;

   dist = std::sqrt( (x-b->x)*(x-b->x) + (y-b->y)*(y-b->y) );
   return ( dist <= deltaO && gammaO > b->camouflage && !(operator==(*this, *b)));

}

// retourne si une bestiole du milieu est morte
bool Bestiole::checkMort(Milieu & monMilieu){
   if (monMilieu.getTime() > ageMort){
      return true;
   }
   else {return false;}
}


// tire un bool pour déterminer si la bestiole aura tel accessoire/capteur ou non
void Bestiole::tirage(){
   
   //tirage 0 ou 1
   int random_number = std::rand() % 2;

   // Conversion du nombre en true ou false
   this->carapace = (random_number == 1) ? true : false;

   random_number = std::rand() % 2;
   this->nageoires = (random_number == 1) ? true : false;

   random_number = std::rand() % 2;
   this->camouflage = (random_number == 1) ? true : false;

   random_number = std::rand() % 2;
   this->yeux = (random_number == 1) ? true : false;

   random_number = std::rand() % 2;
   this->oreilles = (random_number == 1) ? true : false;

}

   // Si une bestiole comporte tel accesoire, les fonctions suivantes affectent ses valeurs caractéristiques
   // Elles sont appelées successivement dans le setAccessories de la factory

void Bestiole::setCarapace (int etaMax, int omegaMax){
   if (carapace) {
   //tirage entre 1 et etaMax puis 1 et omegaMax
   double coef = ((std::rand() / static_cast<double>(RAND_MAX)) * (etaMax - 1)) + 1;
   //cout << "carapace :" << coef << endl;
   this->vitesse = vitesse/coef;
   coef = ((std::rand() / static_cast<double>(RAND_MAX)) * (omegaMax - 1)) + 1;
   this->resistance = resistance*coef; 
   }

}

void Bestiole::setNageoires (int vMax){
   if (nageoires) {
   //tirage entre 1 et vMax
   double coef = ((std::rand() / static_cast<double>(RAND_MAX)) * (vMax - 1)) + 1;
   //cout << "nageoires :" << coef << endl;
   this->vitesse = vitesse*coef;
   }
}


void Bestiole::setCamouflage(double phiMin, double phiMax){
   if (camouflage) {
   //tirage entre phiMin et phiMax
   double coef = phiMin + static_cast<double>(rand()) / RAND_MAX * (phiMax - phiMin);;
   //cout << "camouflage :" << coef << endl;
   this->coefCamouflage = coef;
   }
}


void Bestiole::setOreilles(double deltaOmin, double deltaOmax, double gammaOmin, double gammaOmax){
   if (oreilles) {
   //tirage entre phiMin et phiMax
   double coef = deltaOmin + static_cast<double>(rand()) / RAND_MAX * (deltaOmax - deltaOmin);;
   //cout << "camouflage :" << coef << endl;
   this->deltaO = coef;

   coef = gammaOmin + static_cast<double>(rand()) / RAND_MAX * (gammaOmax - gammaOmin);;
   //cout << "gamma :" << coef << endl;
   this->gammaO = coef;
   }
}

void Bestiole::setYeux(double deltaYmin, double deltaYmax, double gammaYmin, double gammaYmax, double alphaMin, double alphaMax){
   if (yeux) {
   //tirage entre phiMin et phiMax
   double coef = deltaYmin + static_cast<double>(rand()) / RAND_MAX * (deltaYmax - deltaYmin);;
   //cout << "delta :" << coef << endl;
   this->deltaY = coef;

   coef = gammaYmin + static_cast<double>(rand()) / RAND_MAX * (gammaYmax - gammaYmin);;
   //cout << "gamma :" << coef << endl;
   this->gammaY = coef;

   coef = alphaMin + static_cast<double>(rand()) / RAND_MAX * (alphaMax - alphaMin);;
   //cout << "alpha :" << coef << endl;
   this->alpha = coef;
   }
}

// Getters/setters

int Bestiole::getX(){
   return x;
}

int Bestiole::getY(){
   return y;
}

int Bestiole::getResistance(){
   return resistance;
}

int Bestiole::getOrientation(){
   return orientation;
}

void Bestiole::setOrientation(int o){
   orientation = o;
}
