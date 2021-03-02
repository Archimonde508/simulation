#include "Antylopa.h"
#include "Swiat.h"

void Antylopa::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}

void Antylopa::akcja() {
	int buforWspX = wspX;
	int buforWspY = wspY;
	bool czyPoprawnyRuch = false;
	while (czyPoprawnyRuch == false) {
		int ruch = rand() % 4;
		if (ruch == 0) { //do gory
			buforWspY += 2;
		}
		else if (ruch == 1) { //w prawo
			buforWspX += 2;
		}
		else if (ruch == 2) { //w dol
			buforWspY -= 2;
		}
		else if (ruch == 3) { //w lewo
			buforWspX -= 2;
		}

		if (buforWspY < 0 || buforWspY > swiat->getWys() - 1 || buforWspX < 0 || buforWspX > swiat->getSzer() - 1) {
			buforWspX = wspX;
			buforWspY = wspY;
		}
		else {
			if (swiat->sprawdzCoJestNaPolu(buforWspX, buforWspY) == NULL) {
				czyPoprawnyRuch = true;
				swiat->wyczyscPole(wspX, wspY);
				wspX = buforWspX;
				wspY = buforWspY;
				swiat->ustawPole(this);
			}
			else {
				czyPoprawnyRuch = true;
				Organizm* atakowany = swiat->sprawdzCoJestNaPolu(buforWspX, buforWspY);
				if (proba_rozmnozenia(atakowany) == true) {
					if (czyMajaOdpowiedniWiek(this, atakowany) == true) {
						rozmnoz(wspX, wspY, atakowany->getWspX(), atakowany->getWspY(), atakowany);
					}
					return;
				}
				atakowany->kolizja(this);
			}
		}
	}
}

void Antylopa::kolizja(Organizm* oponent){
	int losowa = rand() % 100;
	if (losowa < SZANSA_ANTYLOPY_NA_UCIECZKE) {
		cout << symbol << "ucieka przed walka!" << endl;
		int przedUcieczkaX = this->getWspX();
		int przedUcieczkaY = this->getWspY();

		if (wspX + 1 < swiat->getSzer() && swiat->sprawdzCoJestNaPolu(wspX + 1, wspY) == NULL)	
			this->setWspX(wspX + 1);
		else if (wspX - 1 >= 0 && swiat->sprawdzCoJestNaPolu(wspX - 1, wspY) == NULL) 
			this->setWspX(wspX - 1);
		else if (wspY + 1 < swiat->getWys() && swiat->sprawdzCoJestNaPolu(wspX, wspY + 1) == NULL)	
			this->setWspY(wspY + 1);
		else if (wspY - 1 >= 0 && swiat->sprawdzCoJestNaPolu(wspX, wspY - 1) == NULL)
			this->setWspY(wspY - 1);
		else {
			podstawowaWalka(oponent);
			return;
		}
		int staryX = oponent->getWspX();
		int staryY = oponent->getWspY();
		swiat->wyczyscPole(staryX, staryY);
		oponent->setWspX(przedUcieczkaX);
		oponent->setWspY(przedUcieczkaY);
		swiat->ustawPole(oponent);
		swiat->ustawPole(this);
	}
	else {
		podstawowaWalka(oponent);
	}
}

bool Antylopa::proba_rozmnozenia(Organizm* atakowany){
	if (dynamic_cast<Antylopa*>(atakowany) != NULL)
		return true;
	else
		return false;
}

void Antylopa::rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi){
	if (swiat->czyMoznaDodacPotomka(wsp1, wsp2) == true)
		rozmnazanie();
	else if (swiat->czyMoznaDodacPotomka(wsp3, wsp4) == true)
		drugi->rozmnazanie();
}



Antylopa::Antylopa() {
	setSila(4);
	setInicjatywa(4);
	setSymbol('A');
}

Antylopa::~Antylopa() {

}

Organizm* Antylopa::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Antylopa();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* Antylopa::stworzSiebie()
{
	return new Antylopa();
}
