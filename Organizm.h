#pragma once
//#include "Swiat.h"
#define SZANSA_ROZMNOZENIA_GUARANA 4
#define SZANSA_ROZMNOZENIA_WILCZEJAGODY 3
#define SZANSA_ROZMNOZENIA_TRAWA 2
#define SZANSA_ROZMNOZENIA_MLECZ 1
#define SZANSA_ANTYLOPY_NA_UCIECZKE 50
#define SZANSA_ZOLWIA_NA_RUCH 25
#define MINIMALNY_WIEK_ROZMNOZENIA 15
#define SZANSA_ROZMNOZENIA_BARSZCZ 1

class Swiat;

class Organizm {
protected:
	int sila;
	int inicjatywa;
	int wspX;
	int wspY;
	int turaKreacji;
	char symbol;
	Swiat* swiat;
public:


	~Organizm();

	virtual void akcja() = 0;
	virtual void kolizja(Organizm* oponent) = 0;
	virtual void rysowanie(char** mapa) const = 0;

	virtual int getSila() const;
	virtual int getInicjatywa() const;
	virtual int getWspX()  const;
	virtual int getWspY() const;
	virtual char getSymbol() const;
	virtual int getTuraKreacji() const;

	virtual void setSila(int wartosc);
	virtual void setInicjatywa(int wartosc);
	virtual void setWspX(int wartosc);
	virtual void setWspY(int wartosc);
	virtual void setSymbol(char znak);

	virtual Organizm* dodajPotomstwo(int wspX, int wspY) = 0;

	void setSwiat(Swiat* swiat);

	virtual void rozmnazanie();

	virtual int wiek();
	virtual void setTuraKreacji(int wartosc);

	virtual void podstawowaWalka(Organizm* oponent);
	virtual char getCzyUmiejetnoscAktywnaChar();
	virtual int getCooldown();
	virtual void setCzyUmiejetnoscAktywnaChar(char c);
	virtual void setCooldown(int wartosc);

	virtual Organizm* stworzSiebie() = 0; 
};