#include "Lis.h"
#include "Swiat.h"

void Lis::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}


void Lis::akcja() {
	int buforWspX = wspX;
	int buforWspY = wspY;
	bool czyPoprawnyRuch = false;
	while (czyPoprawnyRuch == false) {
		int ruch = rand() % 4;
		if (ruch == 0) { //do gory
			buforWspY += 1;
		}
		else if (ruch == 1) { //w prawo
			buforWspX += 1;
		}
		else if (ruch == 2) { //w dol
			buforWspY -= 1;
		}
		else if (ruch == 3) { //w lewo
			buforWspX -= 1;
		}

		if (buforWspY < 0 || buforWspY > swiat->getWys() - 1 || buforWspX < 0 || buforWspX > swiat->getSzer() - 1) {
			buforWspX = wspX;
			buforWspY = wspY;
			czyPoprawnyRuch = false;
		}
		else {
			czyPoprawnyRuch = true;
			Organizm* naDocelowymPolu = swiat->sprawdzCoJestNaPolu(buforWspX, buforWspY);
			//Jesli sila organizmu na polu, na ktore chcemy sie udac jest wieksza (lub pole jest puste) to zostajemy lisem na obecnym polu
			if (naDocelowymPolu == NULL || naDocelowymPolu->getSila() <= this->sila) { 
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
			else {	
				return;
			}
		}
	}
}

void Lis::kolizja(Organizm* oponent){
	podstawowaWalka(oponent);
}

bool Lis::proba_rozmnozenia(Organizm* atakowany)
{
	if (dynamic_cast<Lis*>(atakowany) != NULL)
		return true;
	else
		return false;
}

Lis::Lis() {
	setSila(3);
	setInicjatywa(7);
	setSymbol('L');
}

Lis::~Lis() {

}

Organizm* Lis::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Lis();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

Organizm* Lis::stworzSiebie()
{
	return new Lis();
}

void Lis::rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi) {
	if (swiat->czyMoznaDodacPotomka(wsp1, wsp2) == true)
		rozmnazanie();
	else if (swiat->czyMoznaDodacPotomka(wsp3, wsp4) == true)
		drugi->rozmnazanie();
}