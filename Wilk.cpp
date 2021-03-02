#include "Wilk.h"
#include "Swiat.h"

void Wilk::akcja() {
	podstawowyRuch();
}

void Wilk::kolizja(Organizm* oponent)
{
	podstawowaWalka(oponent);
}

bool Wilk::proba_rozmnozenia(Organizm* atakowany)
{
	if (dynamic_cast<Wilk*>(atakowany) != NULL)
		return true;
	else
		return false;
}



void Wilk::rysowanie(char** mapa) const{
	mapa[wspY][wspX] = symbol;
}



Wilk::Wilk() {
	setSila(9);
	setInicjatywa(5);
	setSymbol('W');
}

Wilk::~Wilk() {

}

Organizm* Wilk::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Wilk();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* Wilk::stworzSiebie()
{
	return new Wilk();
}

void Wilk::rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi) {
	if (swiat->czyMoznaDodacPotomka(wsp1, wsp2) == true)
		rozmnazanie();
	else if (swiat->czyMoznaDodacPotomka(wsp3, wsp4) == true)
		drugi->rozmnazanie();
}
