#include "Organizm.h"
#include "Swiat.h"
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


#define PRZERWA_PO_KAZDEJ_TURZE

int main(){
    srand(time(NULL));
    cout << "Czy chcesz wczytac projekt z pliku?" << endl;
    cout << "Wpisanie czegokolwiek innego niz 'T' spowoduje automatyczne wygenerowanie swiata." << endl;
    string start;
    Swiat* argus = new Swiat(5, 5);
    cin >> start;
    if (start == "T") {
        argus->wczytajSwiat();
    }
    else {
        argus = new Swiat(20, 20);
        argus->dodajOrganizm(new Wilk());
        argus->dodajOrganizm(new Wilk());
        argus->dodajOrganizm(new Wilk());
        argus->dodajOrganizm(new Antylopa());
        argus->dodajOrganizm(new Antylopa());
        argus->dodajOrganizm(new Owca());
        argus->dodajOrganizm(new Owca());
        argus->dodajOrganizm(new Owca());
        argus->dodajOrganizm(new Zolw());
        argus->dodajOrganizm(new Zolw());
        argus->dodajOrganizm(new BarszczSosnowskiego());
        argus->dodajOrganizm(new Lis());
        argus->dodajOrganizm(new Lis());
        argus->dodajOrganizm(new Lis());
        argus->dodajOrganizm(new Trawa());
        argus->dodajOrganizm(new Trawa());
        argus->dodajOrganizm(new Mlecz());
        argus->dodajOrganizm(new Mlecz());
        argus->dodajOrganizm(new Guarana());
        argus->dodajOrganizm(new Guarana());
        argus->dodajOrganizm(new Guarana());
        argus->dodajOrganizm(new WilczeJagody());
        argus->dodajOrganizm(new WilczeJagody());
        argus->dodajOrganizm(new Czlowiek());

    }
     
  

    int ileTur = 300;
    string polecenie = "";
    //argus->rysujSwiat();
    while (argus->getNrTury() < ileTur) {
        argus->sortujOrganizmyWedlugInicjatywy();
        system("cls");
        argus->wszystkieAkcje();
        argus->zaktualizujVector(); 
        argus->rysujSwiat();
        cout << argus->getNrTury() << endl;
#ifdef PRZERWA_PO_KAZDEJ_TURZE
        cout << "Wprowadz cokolwiek, by kontynuowac symulacje. " << endl;
        cout << "Wprowadzenie \"p\" zakonczy symulacje, wprowadzenie s zapisze stan gry" << endl;
        int polecenie = _getch();
        if (polecenie == 's') {
            argus->zapiszGre();
        }
        if (polecenie == 'p') {
            break;
        }
#endif
    }  

    delete argus;
    return 0;
}