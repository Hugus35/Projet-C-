#ifndef PEUREUSE
#define PEUREUSE

#include "UImg.h"
#include "Bestiole.h"
#include <iostream>

class Milieu;


using namespace std;

class Peureuse : public Bestiole {
private:

public:
	//Default constructor and destructor
	Peureuse();
	~Peureuse();
    
    Peureuse( const Peureuse & b );

	// Redéfinition de bouge de manière spécifique à peureuse
	void bouge(int xLim, int yLim, Milieu& monMilieu) override final;
	
	// Utile dans bouge
	int nbVoisins( Milieu& monMilieu );

	// Redéfinition la fonction clone virtuelle de bestiole
	Bestiole* clone() const override;


};

#endif