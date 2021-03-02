#include "Guarana.h"
#include "Swiat.h"

void Guarana::akcja() {
	int losowa = rand() % 100;
	if(losowa < SZANSA_ROZMNOZENIA_GUARANA)
		rozmnazanie();
}

void Guarana::kolizja(Organizm* oponent){
	int silaJedzacego = oponent->getSila();
	oponent->setSila(silaJedzacego + 3);
	
	podstawowaWalka(oponent);
}

void Guarana::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}

Guarana::Guarana() {
	setSila(0);
	setInicjatywa(0);
	setSymbol('g');
}

Guarana::~Guarana() {

}

Organizm* Guarana::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Guarana();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* Guarana::stworzSiebie()
{
	return new Guarana();
}
