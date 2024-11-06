#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_

//#include "Factory.h"
#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


class Milieu;


class Aquarium : public CImgDisplay
{

private :
// L'aquarium contient le milieu, modélise par un pointeur "flotte"
   Milieu       * flotte;
   int            delay;

public :
   Aquarium( int width, int height, int _delay, double pNaissance, double pClonage );
   ~Aquarium( void );

   Milieu & getMilieu( void ) { return *flotte; }

   void run( int durée );

};


#endif
