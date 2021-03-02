#include "WilczeJagody.h"
#include "Swiat.h"

void WilczeJagody::akcja() {
	int losowa = rand() % 100;
	if(losowa < SZANSA_ROZMNOZENIA_WILCZEJAGODY)
		rozmnazanie();
}

void WilczeJagody::kolizja(Organizm* oponent){
	cout << oponent->getSymbol() << " zjada " << symbol << " i na skutek tego umiera" << endl;
	int staryX = oponent->getWspX();
	int staryY = oponent->getWspY();
	swiat->wyczyscPole(staryX, staryY);
	delete oponent;

	staryX = this->getWspX();
	staryY = this->getWspY();
	swiat->wyczyscPole(staryX, staryY);
	delete this;
}

void WilczeJagody::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}




WilczeJagody::WilczeJagody() {
	setSila(99);
	setInicjatywa(0);
	setSymbol('j');
}

WilczeJagody::~WilczeJagody() {

}

Organizm* WilczeJagody::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new WilczeJagody();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* WilczeJagody::stworzSiebie()
{
	return new WilczeJagody();
}
