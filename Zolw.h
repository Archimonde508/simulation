#pragma once
#include "Zwierze.h"


class Zolw : public Zwierze {
public:
	Zolw();
	~Zolw();

	void akcja() override;
	void kolizja(Organizm* oponent);
	bool proba_rozmnozenia(Organizm* atakowany) override;
	void rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi) override;

	void rysowanie(char** mapa) const override;

	virtual Organizm* dodajPotomstwo(int wspX, int wspY) override;

	virtual Organizm* stworzSiebie() override;
};