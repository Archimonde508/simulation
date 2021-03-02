#pragma once
#include "Roslina.h"

class Mlecz : public Roslina {
public:

	Mlecz();
	~Mlecz();
	void akcja() override;
	void kolizja(Organizm* oponent);

	void rysowanie(char** mapa) const override;


	virtual Organizm* dodajPotomstwo(int wspX, int wspY) override;

	virtual Organizm* stworzSiebie() override;
};