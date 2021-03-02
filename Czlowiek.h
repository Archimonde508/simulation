#pragma once
#include "Zwierze.h"

class Czlowiek : public Zwierze {
private:
	bool czyUmiejetnoscAktywna;
	int cooldown;
public:
	Czlowiek();
	~Czlowiek();
	void akcja() override;
	void kolizja(Organizm* oponent);

	void rysowanie(char** mapa) const override;

	void setCzyUmiejetnoscAktywna(bool zdanie);
	bool getCzyUmiejetnoscAktywna();

	int getCooldown() override;
	char getCzyUmiejetnoscAktywnaChar() override;
	void setCooldown(int wartosc) override;
	void zmniejszCooldown();
	void aktywujUmiejetnosc();

	virtual Organizm* dodajPotomstwo(int wspX, int wspY) override;

	bool proba_rozmnozenia(Organizm* atakowany) override;
	void rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi) override;

	virtual Organizm* stworzSiebie() override;

	virtual void setCzyUmiejetnoscAktywnaChar(char c) override;
};