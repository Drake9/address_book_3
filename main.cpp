#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

void wypiszMenuLogowania(){
    system("cls");
	cout << "KSIAZKA ADRESOWA" << endl << endl;
	cout << "1. Logowanie" << endl;
	cout << "2. Rejestracja" << endl << endl;
	cout << "0. Zamknij program" << endl << endl;
}

void wypiszMenuGlowne(){
	system("cls");
	cout << "KSIAZKA ADRESOWA" << endl << endl;
	cout << "1. Dodaj adresata" << endl;
	cout << "2. Wyszukaj po imieniu" << endl;
	cout << "3. Wyszukaj po nazwisku" << endl;
	cout << "4. Wyswietl wszystkich adresatow" << endl;
	cout << "5. Usun adresata" << endl;
	cout << "6. Edytuj adresata" << endl << endl;
	cout << "8. Zmien haslo" << endl << endl;
	cout << "0. Wyloguj sie" << endl << endl;
}

int main(){
    bool zalogowany = false;
    int liczbaKontaktow = 0;
    char wybor = 0;

    while(!zalogowany){
        wypiszMenuLogowania();
        wybor = getch();
    }
    return 0;
}
