#include "Trawa.h"
#include "Swiat.h"

void Trawa::akcja() {
	int losowa = rand() % 100;
	if(losowa<SZANSA_ROZMNOZENIA_TRAWA)
		rozmnazanie();
}

void Trawa::kolizja(Organizm* oponent){
	podstawowaWalka(oponent);
}

void Trawa::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}



Trawa::Trawa() {
	setSila(0);
	setInicjatywa(0);
	setSymbol('t');
}

Trawa::~Trawa() {

}

Organizm* Trawa::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Trawa();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* Trawa::stworzSiebie()
{
	return new Trawa();
}
