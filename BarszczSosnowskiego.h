#pragma once
#include "Roslina.h"

class BarszczSosnowskiego : public Roslina {
public:

	BarszczSosnowskiego();
	~BarszczSosnowskiego();
	void akcja() override;
	void kolizja(Organizm* oponent);
	void rysowanie(char** mapa) const override;

	virtual Organizm* dodajPotomstwo(int wspX, int wspY) override;

	virtual Organizm* stworzSiebie() override;
};