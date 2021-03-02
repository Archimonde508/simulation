#include "Czlowiek.h"
#include "Swiat.h"

void Czlowiek::rysowanie(char** mapa) const {
	mapa[wspY][wspX] = symbol;
}

void Czlowiek::akcja() {
	system("cls");
	swiat->rysujSwiat();
	if (cooldown != 0) 	cooldown--;
	if (cooldown == 5) czyUmiejetnoscAktywna = false; //jesli zostalo 5 tur do odnowienia umiejetnosci, to znaczy ze 5 jej uzywania minelo. Wylaczamy.
	if (czyUmiejetnoscAktywna == true) cout << "Do konca umiejetnosci specjalnej zostalo: " << cooldown - 5 << " tur!" << endl;
	else if (czyUmiejetnoscAktywna == false) cout << "Do odnowienia umiejetnosci pozostalo: " << cooldown << " tur!" << endl;


	cout << "Rusz sie czlowiekiem: (W A S D, R - umiejetnosc specjalna) " << endl;
	int ruch = 'q';
	while (ruch != 'w' && ruch != 's' && ruch != 'a' && ruch != 'd') {
		ruch = _getch();
		if (ruch == 'r') aktywujUmiejetnosc();
	}
	cout << "Poruszono czlowiekiem" << endl;
	int buforWspX = wspX;
	int buforWspY = wspY;

	if (ruch == 'w') buforWspY--;
	else if (ruch == 'a') buforWspX--;
	else if (ruch == 's') buforWspY++;
	else if (ruch == 'd') buforWspX++;

	system("cls");

	if (buforWspY < 0 || buforWspY > swiat->getWys() - 1 || buforWspX < 0 || buforWspX > swiat->getSzer() - 1) {	
		if (ruch == 'w') swiat->wyczyscPole(wspX, wspY);
		else if (ruch == 'a') swiat->wyczyscPole(wspX, wspY);
		else if (ruch == 's') swiat->wyczyscPole(wspX, wspY);
		else if (ruch == 'd') swiat->wyczyscPole(wspX, wspY);
		cout << "X wypada poza granice wszechswiata" << endl;
		delete this;
		return;
	}

	
	Organizm* potencjalnyPrzeciwnik = swiat->sprawdzCoJestNaPolu(buforWspX, buforWspY);
	if ( potencjalnyPrzeciwnik != NULL) { //jesli na polu na ktore sie udamy ktos jest
		if (getCzyUmiejetnoscAktywna() == false) //jesli nie mamy aktywnej mocy normalna walka
			potencjalnyPrzeciwnik->kolizja(this);
		else { //jesli mamy
			if (this->getSila() >= potencjalnyPrzeciwnik->getSila()) //to i tak wygramy bitwe
				potencjalnyPrzeciwnik->kolizja(this); //wiecn ormalna walka
			else //jesli przegramy to nie wchodzimy na wrogie pole
				return;
		}
	}
	else { //zwykly ruch
		if (ruch == 'w') swiat->wyczyscPole(wspX, wspY);
		else if (ruch == 'a') swiat->wyczyscPole(wspX, wspY);
		else if (ruch == 's') swiat->wyczyscPole(wspX, wspY);
		else if (ruch == 'd') swiat->wyczyscPole(wspX, wspY);

		this->setWspX(buforWspX);
		this->setWspY(buforWspY);
		swiat->ustawPole(this); //jesli zwykly ruch to przeniesmy tu pole
	}

}

void Czlowiek::kolizja(Organizm* oponent)
{
	if (getCzyUmiejetnoscAktywna() == false) {
		podstawowaWalka(oponent);
	}
	else {
		if (oponent->getSila() >= this->getSila()) {
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
			int staryX = oponent->getWspX();
			int staryY = oponent->getWspY();
			swiat->wyczyscPole(staryX, staryY);
			delete oponent;
		}
	}
}



Czlowiek::Czlowiek() {
	setSila(5);
	setInicjatywa(4);
	setSymbol('X');	
	czyUmiejetnoscAktywna = false;
	cooldown = 0;
}

void Czlowiek::aktywujUmiejetnosc() {
	if (czyUmiejetnoscAktywna == true) {
		cout << "umiejetnosc juz jest aktywna!" << endl;
		return;
	}
	if (cooldown != 0) {
		cout << "Umiejetnosc nie jest jeszcze gotowa do uzycia" << endl;
		return;
	}
	cout << "Aktywowano umiejetnosc specjalna!" << endl;
	czyUmiejetnoscAktywna = true;
	setCooldown(10);
}

Czlowiek::~Czlowiek() {

}

Organizm* Czlowiek::dodajPotomstwo(int wspX, int wspY) {
	Organizm* dziecko = new Czlowiek();
	dziecko->setWspX(wspX);
	dziecko->setWspY(wspY);
	return dziecko;
}

void Czlowiek::setCzyUmiejetnoscAktywna(bool zdanie) {
	czyUmiejetnoscAktywna = zdanie;
}

bool Czlowiek::getCzyUmiejetnoscAktywna(){
	return czyUmiejetnoscAktywna;
}

int Czlowiek::getCooldown(){
	return cooldown;
}
void Czlowiek::setCooldown(int wartosc) {
	cooldown = wartosc;
}

void Czlowiek::zmniejszCooldown() {
	if(cooldown > 0)
		cooldown--;
}

bool Czlowiek::proba_rozmnozenia(Organizm* atakowany) {
	cout << "Blad! Czlowiek nie powinien sie nigdy rozmnozyc!" << endl;
	return false;
}

void Czlowiek::rozmnoz(int wsp1, int wsp2, int wsp3, int wsp4, Organizm* drugi) {
	cout << "Blad! Czlowiek nie moze sie rozmnozyc!" << endl;
}

Organizm* Czlowiek::stworzSiebie()
{
	return new Czlowiek();
}

void Czlowiek::setCzyUmiejetnoscAktywnaChar(char c)
{
	if (c == 'T')
		czyUmiejetnoscAktywna = true;
	else
		czyUmiejetnoscAktywna = false;
}

char Czlowiek::getCzyUmiejetnoscAktywnaChar() {
	if (czyUmiejetnoscAktywna == true)
		return 'T';
	else
		return 'F';
}
