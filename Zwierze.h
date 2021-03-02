
#pragma once
#include "Organizm.h"
#include <time.h>
#include <cstdlib>


class Zwierze : public Organizm {
public:
	virtual void podstawowyRuch();
	void atakuj(Organizm* atakowany);
	virtual bool proba_rozmnozenia(Organizm* atakowany) = 0;
	virtual void rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi) = 0;
	virtual bool czyMajaOdpowiedniWiek(Organizm* a, Organizm* b);
	
};