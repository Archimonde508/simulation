#include "Organizm.h"
#include "Swiat.h"

int Organizm::wiek() {
	return swiat->getNrTury() - turaKreacji;
}

void Organizm::setTuraKreacji(int wartosc){
	turaKreacji = wartosc;
}

void Organizm::setSwiat(Swiat* swiat) {
	this->swiat = swiat;
}

int Organizm::getSila() const {
	return sila;
}
int Organizm::getInicjatywa() const {
	return inicjatywa;
}
int Organizm::getWspX()  const {
	return wspX;
}
int Organizm::getWspY() const {
	return wspY;
}
char Organizm::getSymbol() const {
	return symbol;
}

void Organizm::setSila(int wartosc) {
	sila = wartosc;
}
void Organizm::setInicjatywa(int wartosc) {
	inicjatywa = wartosc;
}
void Organizm::setWspX(int wartosc) {
	wspX = wartosc;
}
void Organizm::setWspY(int wartosc) {
	wspY = wartosc;
}
void Organizm::setSymbol(char znak) {
	symbol = znak;
}

Organizm::~Organizm() {
	swiat->usunOrganizmZVectora(this);
}

void Organizm::rozmnazanie() {
	if (swiat->czyMoznaDodacPotomka(wspX, wspY) == false) {
		return;
	}
	cout << symbol << " rozmnaza sie o powstaje malutki " << symbol << "!" << endl;
	int buforWspX = wspX;
	int buforWspY = wspY;
	bool czyPoprawnyRuch = false;
	while (czyPoprawnyRuch == false) {
		int ruch = rand() % 4;

		if (ruch == 0) 	buforWspY += 1;
		else if (ruch == 1)	buforWspX += 1;
		else if (ruch == 2) buforWspY -= 1;
		else if (ruch == 3) buforWspX -= 1;

		if (swiat->czyPoleWolne(buforWspX, buforWspY) == false) {
			buforWspX = wspX;
			buforWspY = wspY;
			czyPoprawnyRuch = false;
		}
		else {
			czyPoprawnyRuch = true;
			Organizm* dziecko = dodajPotomstwo(buforWspX, buforWspY);
			swiat->dodajPotomka(dziecko);
		}
	}
}

void Organizm::podstawowaWalka(Organizm* oponent) {
	if (oponent->getSila() >= this->getSila()) {
		cout << oponent->getSymbol() << " (sila: " << oponent->getSila() << " ) pozera " << symbol << " (sila: " << sila << " )" << endl;
		int staryX = oponent->getWspX();
		int staryY = oponent->getWspY();
		int nowyX = this->getWspX();
		int nowyY = this->getWspY();


		oponent->setWspX(nowyX);
		oponent->setWspY(nowyY);
		swiat->ustawPole(oponent);
		swiat->wyczyscPole(staryX, staryY);	
		delete this; //USUNIECIE Z VEKTORA
	}
	else {
		cout << symbol << " (sila: " << sila << " ) pozera " << oponent->getSymbol() << " (sila: " << oponent->getSila() << " )" << endl;
		int staryX = oponent->getWspX();
		int staryY = oponent->getWspY();
		swiat->wyczyscPole(staryX, staryY);
		delete oponent;
	}
}


char Organizm::getCzyUmiejetnoscAktywnaChar() {
	return 'F';
}
int Organizm::getCooldown() {
	return 0;
}

void Organizm::setCzyUmiejetnoscAktywnaChar(char c) {
}
void Organizm::setCooldown(int wartosc) {
}

int Organizm::getTuraKreacji() const{
	return turaKreacji;
}