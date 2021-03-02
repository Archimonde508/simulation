#include "Mlecz.h"
#include "Swiat.h"

void Mlecz::akcja() {
	int losowa1 = rand() % 100;
	int losowa2 = rand() % 100;
	int losowa3 = rand() % 100;
	if(losowa1 < SZANSA_ROZMNOZENIA_MLECZ)
		rozmnazanie();
	if (losowa2 < SZANSA_ROZMNOZENIA_MLECZ)
		rozmnazanie();
	if (losowa3 < SZANSA_ROZMNOZENIA_MLECZ)
		rozmnazanie();
}

void Mlecz::kolizja(Organizm* oponent)
{
	podstawowaWalka(oponent);
}


void Mlecz::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}



Mlecz::Mlecz() {
	setSila(0);
	setInicjatywa(0);
	setSymbol('m');
}

Mlecz::~Mlecz() {

}

Organizm* Mlecz::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Mlecz();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* Mlecz::stworzSiebie()
{
	return new Mlecz();
}

