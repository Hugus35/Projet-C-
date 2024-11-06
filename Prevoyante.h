#ifndef PREVOYANTE
#define PREVOYANTE

#include "UImg.h"
#include "Bestiole.h"
#include <iostream>

class Milieu;


using namespace std;

class Prevoyante : public Bestiole {
private:

public:
	//Default constructor and destructor
	Prevoyante();
	~Prevoyante();
    
    Prevoyante( const Prevoyante & b );

	// Redéfinition de bouge de manière spécifique à prevoyante
	void bouge(int xLim, int yLim, Milieu& monMilieu) override final;

	// Redéfinition la fonction clone virtuelle de bestiole
	Bestiole* clone() const override;

	// Utile dans bouge
	double angleMoyen (Milieu& monMilieu);

};

#endif