#pragma once
#include "Roslina.h"

class WilczeJagody : public Roslina {
public:
	WilczeJagody();
	~WilczeJagody();
	void akcja() override;
	void kolizja(Organizm* oponent);

	void rysowanie(char** mapa) const override;

	virtual Organizm* dodajPotomstwo(int wspX, int wspY) override;

	virtual Organizm* stworzSiebie() override;
};