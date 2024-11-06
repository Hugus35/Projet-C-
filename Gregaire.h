#ifndef GREGAIRE
#define GREGAIRE

#include "UImg.h"
#include "Bestiole.h"
#include <iostream>

class Milieu;


using namespace std;

class Gregaire : public Bestiole {
private:

public:
	//Default constructor and destructor

	Gregaire();
	~Gregaire();
    Gregaire( const Gregaire & b );

	// Redéfinition de bouge de manière spécifique à grégaire

	void bouge(int xLim, int yLim, Milieu& monMilieu) override final;

	// Redéfinit la fonction clonage virtuelle de bestiole
	Bestiole* clone() const override;

	// Utile dans la fonction bouge
	double angleMoyen(Milieu& monMilieu);


};

#endif