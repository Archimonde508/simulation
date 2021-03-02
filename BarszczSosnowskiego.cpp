#include "BarszczSosnowskiego.h"
#include "Swiat.h"

void BarszczSosnowskiego::akcja() {
	Organizm* ofiaraBarszczu;

	if (wspX + 1 >= 0 && wspY < swiat->getWys() && wspX + 1 < swiat->getSzer() && wspY >= 0) {
		ofiaraBarszczu = swiat->sprawdzCoJestNaPolu(wspX + 1, wspY);
		if (ofiaraBarszczu != NULL && dynamic_cast<Roslina*>(ofiaraBarszczu) == NULL) {
			cout << symbol << " otruwa " << ofiaraBarszczu->getSymbol() << endl;
			swiat->wyczyscPole(ofiaraBarszczu->getWspX(), ofiaraBarszczu->getWspY());
			delete ofiaraBarszczu;
		}
	}
		
	if (wspX - 1 >= 0 && wspY < swiat->getWys() && wspX - 1 < swiat->getSzer() && wspY >= 0) {
		ofiaraBarszczu = swiat->sprawdzCoJestNaPolu(wspX - 1, wspY);
		if (ofiaraBarszczu != NULL && dynamic_cast<Roslina*>(ofiaraBarszczu) == NULL) {
			cout << symbol << " otruwa " << ofiaraBarszczu->getSymbol() << endl;
			swiat->wyczyscPole(ofiaraBarszczu->getWspX(), ofiaraBarszczu->getWspY());
			delete ofiaraBarszczu;
		}
	}
		
	if (wspX >= 0 && wspY + 1 < swiat->getWys() && wspX < swiat->getSzer() && wspY + 1 >= 0) {
		ofiaraBarszczu = swiat->sprawdzCoJestNaPolu(wspX, wspY + 1);
		if (ofiaraBarszczu != NULL && dynamic_cast<Roslina*>(ofiaraBarszczu) == NULL) {
			cout << symbol << " otruwa " << ofiaraBarszczu->getSymbol() << endl;
			swiat->wyczyscPole(ofiaraBarszczu->getWspX(), ofiaraBarszczu->getWspY());
			delete ofiaraBarszczu;
		}
	}
		
	if (wspX >= 0 && wspY - 1 < swiat->getWys() && wspX < swiat->getSzer() && wspY - 1 >= 0) {
		ofiaraBarszczu = swiat->sprawdzCoJestNaPolu(wspX, wspY - 1);
		if (ofiaraBarszczu != NULL && dynamic_cast<Roslina*>(ofiaraBarszczu) == NULL) {
			cout << symbol << " otruwa " << ofiaraBarszczu->getSymbol() << endl;
			swiat->wyczyscPole(ofiaraBarszczu->getWspX(), ofiaraBarszczu->getWspY());
			delete ofiaraBarszczu;
		}
	}

	int losowa = rand() % 100;
	if (losowa < SZANSA_ROZMNOZENIA_BARSZCZ)
		rozmnazanie();
}

void BarszczSosnowskiego::kolizja(Organizm* oponent) {
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

void BarszczSosnowskiego::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}

BarszczSosnowskiego::BarszczSosnowskiego() {
	setSila(10);
	setInicjatywa(0);
	setSymbol('b');
}

BarszczSosnowskiego::~BarszczSosnowskiego() {

}

Organizm* BarszczSosnowskiego::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new BarszczSosnowskiego();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* BarszczSosnowskiego::stworzSiebie()
{
	return new BarszczSosnowskiego();
}
