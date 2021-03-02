#include "Zolw.h"
#include "Swiat.h"

void Zolw::akcja() {
	int los = rand() % 100; //wylosuj 0, 1, 2 lub 3
	if (los < SZANSA_ZOLWIA_NA_RUCH) { //jesli wylosowano 0 (25 procent szansy) to rusz sie
		podstawowyRuch();
	}
}



void Zolw::kolizja(Organizm* oponent){
	if (oponent->getSila() < 5) {
		cout << symbol << "odpiera atak " << oponent->getSymbol() << endl;
		return;
	}
	else {
	podstawowaWalka(oponent);
	}
	
}

bool Zolw::proba_rozmnozenia(Organizm* atakowany)
{
	if (dynamic_cast<Zolw*>(atakowany) != NULL)
		return true;
	else
		return false;
}

void Zolw::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}


Zolw::Zolw() {
	setSila(2);
	setInicjatywa(1);
	setSymbol('Z');
}

Zolw::~Zolw() {

}

Organizm* Zolw::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Zolw();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* Zolw::stworzSiebie()
{
	return new Zolw();
}

void Zolw::rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi) {
	if (swiat->czyMoznaDodacPotomka(wsp1, wsp2) == true)
		rozmnazanie();
	else if (swiat->czyMoznaDodacPotomka(wsp3, wsp4) == true)
		drugi->rozmnazanie();
}