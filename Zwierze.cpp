#include "Zwierze.h"
#include "Swiat.h"

void Zwierze::podstawowyRuch(){
	int buforWspX = wspX;
	int buforWspY = wspY;
	bool czyPoprawnyRuch = false;
	while (czyPoprawnyRuch == false) {
		int ruch = rand() % 4;

		if (ruch == 0) 	buforWspY += 1;
		else if (ruch == 1)	buforWspX += 1;
		else if (ruch == 2) buforWspY -= 1;
		else if (ruch == 3) buforWspX -= 1;

		if (buforWspY < 0 || buforWspY > swiat->getWys() - 1 || buforWspX < 0 || buforWspX > swiat->getSzer() - 1) {
			buforWspX = wspX;
			buforWspY = wspY;
			czyPoprawnyRuch = false;
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

bool Zwierze::czyMajaOdpowiedniWiek(Organizm* a, Organizm* b) {
	if (a->wiek() > MINIMALNY_WIEK_ROZMNOZENIA && b->wiek() > MINIMALNY_WIEK_ROZMNOZENIA)
		return true;
	else
		return false;
}