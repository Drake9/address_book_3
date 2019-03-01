#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

struct Adresat{
    int idAdresata = 0, idUzytkownika = 0;
    string imie = "", nazwisko = "", adres = "", numerTelefonu = "", email = "";
};

struct Uzytkownik{
    int id;
    string login, haslo;
};

void podzielString(string linia, char znak, vector<string> &wyrazy){

    for(int i=0, j=0, dlugosc=linia.length(); j<=dlugosc; j++){
        if(linia[j] == znak){
            wyrazy.push_back(linia.substr(i,j-i));
            i = j+1;
        }
    }
}

int wczytajZPlikuDaneUzytkownikow(vector<Uzytkownik> &uzytkownicy){
    Uzytkownik uzytkownik;
    int liczbaUzytkownikow = 0;
    string linia, temp;
	fstream plik;
	vector<string> podzielonaLinia;

	plik.open("Uzytkownicy.txt", ios::in);
    if(plik.good()==false){
        cout << "Nie udalo sie otworzyc pliku Uzytkownicy.txt. Zostanie utworzony nowy plik.";
        Sleep(1500);
        plik.open("Uzytkownicy.txt", ios::out | ios::app);
        //exit(0);
    }
    else{
        while(getline(plik,linia)){

            podzielonaLinia.clear();
            podzielString(linia, '|', podzielonaLinia);

            uzytkownik.id = atoi (podzielonaLinia[0].c_str());
            uzytkownik.login = podzielonaLinia[1];
            uzytkownik.haslo = podzielonaLinia[2];

            uzytkownicy.push_back(uzytkownik);
            liczbaUzytkownikow++;
        }
    }
    plik.close();

    return liczbaUzytkownikow;
}

int zaloguj(){
    vector <Uzytkownik> uzytkownicy;

	int liczbaUzytkownikow = wczytajZPlikuDaneUzytkownikow(uzytkownicy);

    string login, haslo;

    system("cls");
    cout << "Podaj login: " << endl;
    cin >> login;

    int i=0;
    while(i < liczbaUzytkownikow){
        if(uzytkownicy[i].login == login){

            for(int j=0; j<3; j++){
                system("cls");
                cout << "Podaj haslo. Pozostalo prob: " << 3-j << endl;
                cin >> haslo;

                if(uzytkownicy[i].haslo == haslo){

                    cout << "Zalogowales sie.";
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
                cout << "Podane haslo jest nieprawidlowe.";
                Sleep(2000);
            }
            cout << "Podales 3 razy bledne haslo.";
            Sleep(1500);
            return 0;
        }
        i++;
    }
    cout << "Brak w bazie uzytkownika o podanym loginie.";
    Sleep(1500);
    return 0;
}

void zarejestrujUzytkownika(){
    fstream plik;
    vector <Uzytkownik> uzytkownicy;
    string login, haslo;
    int noweID;

	int liczbaUzytkownikow = wczytajZPlikuDaneUzytkownikow(uzytkownicy);

    if(liczbaUzytkownikow > 0)
        noweID = uzytkownicy[liczbaUzytkownikow-1].id + 1;
    else
        noweID = 1;

    system("cls");
    cout << "Podaj nazwe uzytkownika: " << endl;
    cin >> login;

    int i=0;
    while(i < liczbaUzytkownikow){
        if(uzytkownicy[i].login == login){
            cout << endl << "Istnieje juz uzytkownik o podanej nazwie. Podaj inna nazwe: " << endl;
            cin >> login;
            i=0;
        }
        else{
            i++;
        }
    }

    cout << "Podaj haslo uzytkownika: " << endl;
    cin >> haslo;

    plik.open("Uzytkownicy.txt", ios::out | ios::app);
    if(plik.good())
        plik << noweID << "|" << login << "|" << haslo << "|" << endl;
    else{
        cout << "Nie udalo sie otworzyc pliku do zapisu. Program zostanie zamkniety.";
        exit(0);
    }
    plik.close();

    cout << "Nowy uzytkownik zostal zarejestrowany.";
    Sleep(1500);

}

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
    int idUzytkownika = 0;
    int liczbaKontaktow = 0;
    char wybor = '0';

    vector <Adresat> adresaci;

    while(true){
        if(idUzytkownika == 0){
            wypiszMenuLogowania();
            wybor = getch();

            switch(wybor){
                case '1':
                    idUzytkownika = zaloguj();
                    break;

                case '2':
                    zarejestrujUzytkownika();
                    break;

                case '0':
                    return 0;

                default:
                    cout << "Nie ma takiej opcji. Wybierz jeszcze raz." << endl;
                    Sleep(1500);
                    break;
            }

		}else{
            wypiszMenuGlowne();
            wybor = getch();

            switch(wybor){
			case '1':
				//liczbaKontaktow = dodajKontakt(liczbaKontaktow, adresaci);
				break;

			case '2':
				//wyszukajKontaktPoImieniu(liczbaKontaktow, adresaci);
				break;

            case '3':
				//wyszukajKontaktPoNazwisku(liczbaKontaktow, adresaci);
				break;

			case '4':
				//wypiszWszystkieKontakty(liczbaKontaktow, adresaci);
				break;

            case '5':
				//przejdzDoUsuwaniaAdresata(liczbaKontaktow, adresaci);
				break;

            case '6':
				//przejdzdoEdycjiAdresata(liczbaKontaktow, adresaci);
				break;

            case '8':
				;//zmien haslo uzytkownika
				break;

			case '0':
				idUzytkownika = 0;
                system("cls");
                cout << "Wylogowales sie.";
                Sleep(1500);
				break;

			default:
				cout << "Nie ma takiej opcji. Wybierz jeszcze raz." << endl;
				Sleep(1500);
				break;
            }
        }
    }
    return 0;
}
