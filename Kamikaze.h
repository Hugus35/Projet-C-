#ifndef KAMIKAZE
#define KAMIKAZE

#include "UImg.h"
#include "Bestiole.h"
#include <iostream>

class Milieu;


using namespace std;

class Kamikaze : public Bestiole {
private:

public:
	//Default constructor and destructor
	Kamikaze();
	~Kamikaze();
    Kamikaze( const Kamikaze & b );

	// Redéfinition de bouge de manière spécifique à kamikaze
	void bouge(int xLim, int yLim, Milieu& monMilieu) override final;

	// Redéfinition la fonction clone virtuelle de bestiole
	Bestiole* clone() const override;

	// Utile dans bouge
	double plusProche(Milieu& monMilieu);

};

#endif