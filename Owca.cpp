#include "Owca.h"
#include "Swiat.h"

void Owca::akcja() {
	podstawowyRuch();
}

void Owca::kolizja(Organizm* oponent){
	podstawowaWalka(oponent);
}

bool Owca::proba_rozmnozenia(Organizm* atakowany)
{
	if (dynamic_cast<Owca*>(atakowany) != NULL)
		return true;
	else
		return false;
}



void Owca::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}




Owca::Owca() {
	setSila(4);
	setInicjatywa(4);
	setSymbol('O');
}

Owca::~Owca() {

}

Organizm* Owca::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Owca();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* Owca::stworzSiebie()
{
	return new Owca();
}

void Owca::rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi) {
	if (swiat->czyMoznaDodacPotomka(wsp1, wsp2) == true)
		rozmnazanie();
	else if (swiat->czyMoznaDodacPotomka(wsp3, wsp4) == true)
		drugi->rozmnazanie();
}