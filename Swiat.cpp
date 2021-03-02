#include "Swiat.h"
#define _CRT_SECURE_NO_WARNINGS

Swiat::Swiat(int wys, int szer) {
	if (wys > 0 && szer > 0) {
		this->wys = wys;
		this->szer = szer;
	}
	else {
		cout << "Podano niepoprawne wymiary swiata." << endl;
		this->wys = 0;
		this->szer = 0;
	}
	nrTury = 0;
	plansza = new Organizm * *[wys];
	for (int i = 0; i < wys; i++) {
		plansza[i] = new Organizm * [szer];
		for (int j = 0; j < szer; j++) {
			plansza[i][j] = NULL;
		}
	}
}

Swiat::Swiat() {
	this->wys = 0;
	this->szer = 0;
	plansza = NULL;
	nrTury = 0;
}

int Swiat::getWys() const {
	return wys;
}

int Swiat::getSzer() const {
	return szer;
}

int Swiat::getNrTury() const {
	return nrTury;
}

void Swiat::rysujSwiat() const {
	for (int i = 0; i < szer + 2; i++) {
		cout << '*' << ' ';
	}

	cout << endl;
	for (int i = 0; i < wys; i++) {
		cout << '*' << ' ';
		for (int j = 0; j < szer; j++) {
			if (plansza[i][j] != NULL)
				cout << plansza[i][j]->getSymbol() << ' ';
			else
				cout << ' ' << ' ';
		}
		cout  << '*';
		cout << endl;
	}

	for (int i = 0; i < szer + 2; i++) {
		cout << '*' << ' ';
	}
	cout << endl;

}

void Swiat::dodajOrganizm(Organizm* organizm) {
	bool czyWolne = false;
	int nowyX, nowyY;
	while (czyWolne == false) {
		nowyX = rand() % szer; //dla szer 20: zakres: 0 - 19
		nowyY = rand() % wys;

		if (czyPoleWolne(nowyX, nowyY) == true) {
			czyWolne = true;
		}
		else {
			czyWolne = false;
		}
	}
	organizm->setWspX(nowyX);
	organizm->setWspY(nowyY);
	organizm->setSwiat(this);
	int nr = getNrTury();
	organizm->setTuraKreacji(nr);
	organizmy.push_back(organizm);
	plansza[nowyY][nowyX] = organizm;
}

void Swiat::dodajPotomka(Organizm* organizm){ 
	organizm->setSwiat(this);
	int nr = getNrTury();
	organizm->setTuraKreacji(nr);
	int x = organizm->getWspX();
	int y = organizm->getWspY();
	plansza[y][x] = organizm;
	organizmy.push_back(organizm);
}


void Swiat::wyswietlOrganizmy() { //nie dzia³a
	for (Organizm* org : organizmy) {
		cout << org->getSymbol() << ' ';
	}
}

bool Swiat::czyPoleWolne(int x, int y){ //najpierw sprawdz, czy pole nie jest poza granicami mapy.
	if (x < 0 || x > getSzer() - 1 || y < 0 || y > getWys() - 1)
		return false;
			
	if (plansza[y][x] == NULL)
		return true;
	else
		return false;	
}

bool Swiat::czyMoznaDodacPotomka(int x, int y){
	bool leweWolne, praweWolne, dolneWolne, gorneWolne;	
	leweWolne = czyPoleWolne(x - 1, y);
	praweWolne = czyPoleWolne(x + 1, y);
	gorneWolne = czyPoleWolne(x, y - 1);
	dolneWolne = czyPoleWolne(x, y + 1);

	if (!leweWolne && !praweWolne && !gorneWolne && !dolneWolne)
		return false;
	else
		return true;
}

void Swiat::wszystkieAkcje(){
	nrTury++;
	int koniec = organizmy.size();
	for (int i = 0; i < koniec; i++) {	
		if (organizmy[i] != NULL) {
			organizmy[i]->akcja();
		}	
	}
}

void Swiat::ustawPole(Organizm* org) {
	int x = org->getWspX();
	int y = org->getWspY();
	plansza[y][x] = org;
}

void Swiat::wyczyscPole(int x, int y) {
	plansza[y][x] = NULL;
}

Organizm* Swiat::sprawdzCoJestNaPolu(int x, int y) {
	return plansza[y][x];
}



void Swiat::usunOrganizmZVectora(Organizm* org) {
	int licznik = 0;
	while (organizmy[licznik] != org) {
		licznik++;
	}
		

	organizmy[licznik] = NULL;
}

void Swiat::zaktualizujVector() {
	int dlugosc = organizmy.size() - 1;
	for (int i = dlugosc; i>=0 ; i--) {
		if (organizmy[i] == NULL) {
			organizmy.erase(organizmy.begin() + i);
		}
	}
}

bool porownajInicjatywe::operator()(const Organizm* a, const Organizm* b) const {
	return a->getInicjatywa() > b->getInicjatywa();
}

void Swiat::sortujOrganizmyWedlugInicjatywy() {
	stable_sort(organizmy.begin(), organizmy.end(), porownajInicjatywe());
}

Swiat::~Swiat() {
	for (int i = 0; i < wys; i++) {
		delete[] plansza[i];
	}
	delete[] plansza;

	int dlugosc = organizmy.size() - 1;
	for (int i = dlugosc; i >= 0; i--) {
		if (organizmy[i] != NULL) {
			delete organizmy[i];
		}
	}
}

void Swiat::zapiszGre() {
#define _CRT_SECURE_NO_WARNINGS
	FILE* plik = fopen("zapisanaGra.txt", "w");
	if (plik == NULL) {
		cout << "Zapis skonczony niepowodzeniem!" << endl;
		cout << "Nie mozemy utworzyc pliku do zapisania gry!" << endl;
		return;
	}
	fprintf(plik, "%d %d\n", wys, szer);
	fprintf(plik, "%d\n", nrTury);
	int ileOrganizmow = organizmy.size();
	fprintf(plik, "%d\n", ileOrganizmow);
	for (int i = 0; i < ileOrganizmow; i++) {
		fprintf(plik, "%c %d %d " , organizmy[i]->getSymbol(), organizmy[i]->getWspX(), organizmy[i]->getWspY());
		fprintf(plik, "%d %d %d ", organizmy[i]->getSila(), organizmy[i]->getInicjatywa(), organizmy[i]->getTuraKreacji());
		if (organizmy[i]->getSymbol() == 'X') {		
			char um = organizmy[i]->getCzyUmiejetnoscAktywnaChar();
			int cd = organizmy[i]->getCooldown();
			fprintf(plik, "%c %d\n", um, cd);
		}
		else{
			fprintf(plik, "\n");
		}
	}
	fclose(plik);
	cout << "Pomyslnie dokonano zapisu rozgrywki" << endl;
}


void Swiat::wczytajSwiat() {
	FILE* plik = fopen("zapisanaGra.txt", "r");
	if (plik == NULL) {
		cout << "Nie istnieje taki plik, wczytanie nieudane!" << endl;
		return;
	}
	int wysR = 0, szerR = 0, nrTuryR = 0, ileOrganizmow = 0;
	fscanf(plik, "%d %d %d %d", &wysR, &szerR, &nrTuryR, &ileOrganizmow);
	cout << wysR << ' ' <<szerR << endl;;
	wys = wysR;
	szer = szerR;
	nrTury = nrTuryR;
	plansza = new Organizm * *[wys];
	for (int i = 0; i < wys; i++) {
		plansza[i] = new Organizm * [szer];
		for (int j = 0; j < szer; j++) {
			plansza[i][j] = NULL;
		}
	}
	char typ[5] = "";
	int xR = 0, yR = 0, silaR = 0, inicjatywaR = 0, turaKreacjiR = 0;
	cout << "!!!! " << ileOrganizmow << endl;
	for (int i = 0; i < ileOrganizmow; i++) {
		Organizm* org = NULL;
		cout << "Pobieramy nowi organizm! " << endl;
		fscanf(plik, "%s %d %d %d %d %d", &typ, &xR, &yR, &silaR, &inicjatywaR, &turaKreacjiR);

		if (typ[0] == 'L') org = new Lis();
		else if (typ[0] == 'W') org = new Wilk();
		else if (typ[0] == 'A') org = new Antylopa();
		else if (typ[0] == 'Z') org = new Zolw();
		else if (typ[0] == 'O') org = new Owca();
		else if (typ[0] == 'b') org = new BarszczSosnowskiego();
		else if (typ[0] == 'g') org = new Guarana();
		else if (typ[0] == 'j') org = new WilczeJagody();
		else if (typ[0] == 't') org = new Trawa();
		else if (typ[0] == 'm') org = new Mlecz();
		else if (typ[0] == 'X') org = new Czlowiek();

		cout << typ[0] << endl;
		cout << xR << endl;

		cout << yR << endl;
		cout << silaR << endl;
		cout << inicjatywaR << endl;
		cout << turaKreacjiR << endl;

		if (typ[0] == 'X') {
			char czyUmiejetnoscAktywnaR[5] = "";
			int cooldownR = 0;
			fscanf(plik, "%s %d", &czyUmiejetnoscAktywnaR, &cooldownR);
			org->setCzyUmiejetnoscAktywnaChar(czyUmiejetnoscAktywnaR[0]);
			cout << czyUmiejetnoscAktywnaR[0] << endl;
			org->setCooldown(cooldownR);
			cout << cooldownR << endl;
		}
		


		org->setSila(silaR);
	
		org->setInicjatywa(inicjatywaR);
		
		org->setWspX(xR);
		org->setWspY(yR);
		
		org->setTuraKreacji(turaKreacjiR);
	
		org->setSwiat(this);
		plansza[yR][xR] = org;
		organizmy.push_back(org);
	}
	fclose(plik);
	cout << organizmy.size() << endl;
	cout << "Zakonczono wczytywanie swiata" << endl;
}
