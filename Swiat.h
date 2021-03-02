#pragma once
#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm> 
#include <windows.h>
#include <conio.h>
using namespace std;
#include "Organizm.h"
#include "Lis.h"
#include "Zwierze.h"
#include "Wilk.h"
#include "Zolw.h"
#include "Owca.h"
#include "Lis.h"
#include "Antylopa.h"
#include "Roslina.h"
#include "Trawa.h"
#include "Mlecz.h"
#include "Guarana.h"
#include "WilczeJagody.h"
#include "BarszczSosnowskiego.h"
#include "Czlowiek.h"
#define NO_KEY 0x00
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

class Organizm;
class Lis;
class Czlowiek;
class Wilk;
class Owca;
class antylopa;
class Zolw;
class BarszczSosnowskiego;
class Guarana;
class Trawa;
class WilczeJagody;

struct porownajInicjatywe {
	bool operator()(const Organizm* a, const Organizm* b) const;
};

class Swiat {
private:
	int wys;
	int szer;
	int nrTury;
	vector<Organizm*> organizmy;
	Organizm*** plansza;

public:
	Swiat();
	Swiat(int wys, int szer);
	void wszystkieAkcje();
	void rysujSwiat() const;

	int getWys() const;
	int getSzer() const;
	int getNrTury() const;

	void dodajOrganizm(Organizm* organizm);
	void dodajPotomka(Organizm* organizm);
	void wyswietlOrganizmy();

	bool czyPoleWolne(int x, int y);
	bool czyMoznaDodacPotomka(int x, int y);

	void ustawPole(Organizm* org);
	void wyczyscPole(int x, int y);

	Organizm* sprawdzCoJestNaPolu(int x, int y);


	void usunOrganizmZVectora(Organizm* org);
	void zaktualizujVector();

	void sortujOrganizmyWedlugInicjatywy();
	~Swiat();

	void zapiszGre();
	void wczytajSwiat();
};