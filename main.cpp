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

int wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy){
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

int wczytajAdresatowZPliku(vector<Adresat> &adresy, int idUzytkownika){
	int nrKontaktu = 0;
	Adresat kontakt;
	string linia, temp;
	fstream plik;
	vector<string> podzielonaLinia;

    plik.open("Adresaci.txt", ios::in); // wczytujemy plik
    if(plik.good()==false){
        cout << endl <<"Nie udalo sie otworzyc pliku z kontaktami. Zostanie utworzony nowy plik.";
        Sleep(1500);
        plik.open("Adresaci.txt", ios::out | ios::app);
        //exit(0);
    }
    else{
        while(getline(plik,linia)){

            podzielonaLinia.clear();
            podzielString(linia, '|', podzielonaLinia);

            kontakt.idAdresata = atoi (podzielonaLinia[0].c_str());
            kontakt.idUzytkownika = atoi(podzielonaLinia[1].c_str());
            kontakt.imie = podzielonaLinia[2];
            kontakt.nazwisko = podzielonaLinia[3];
            kontakt.adres = podzielonaLinia[4];
            kontakt.numerTelefonu = podzielonaLinia[5];
            kontakt.email = podzielonaLinia[6];

            adresy.push_back(kontakt);
            nrKontaktu++;
        }
    }
    plik.close();
    return adresy.size();
}

int zaloguj(){
    vector <Uzytkownik> uzytkownicy;

	int liczbaUzytkownikow = wczytajUzytkownikowZPliku(uzytkownicy);

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

	int liczbaUzytkownikow = wczytajUzytkownikowZPliku(uzytkownicy);

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

int dodajKontakt(int liczbaKontaktow, vector<Adresat> &adresy, int idUzytkownika){
    Adresat kontakt;
    fstream plik;
    if(liczbaKontaktow > 0)
        kontakt.idAdresata = adresy[liczbaKontaktow-1].idAdresata + 1;
    else
        kontakt.idAdresata = 1;

    kontakt.idUzytkownika = idUzytkownika;

    system("cls");
    cin.sync();
    cout << "Podaj imie: ";           getline(cin, kontakt.imie);
    cout << "Podaj nazwisko: ";       getline(cin, kontakt.nazwisko);
    cout << "Podaj adres: ";          getline(cin, kontakt.adres);
    cout << "Podaj nr telefonu: ";    getline(cin, kontakt.numerTelefonu);
    cout << "Podaj adres e-mail: ";   getline(cin, kontakt.email);

    adresy.push_back(kontakt);

    plik.open("ksiazka_adresowa_nowy_format.txt", ios::out | ios::app);
    if(plik.good())
        plik << kontakt.idAdresata << "|" << kontakt.idUzytkownika << "|" << kontakt.imie << "|" << kontakt.nazwisko << "|" << kontakt.adres << "|" << kontakt.numerTelefonu << "|" << kontakt.email << "|" << endl;
    else{
        cout << "Nie udalo sie otworzyc pliku do zapisu. Program zostanie zamkniety.";
        exit(0);
    }
    plik.close();

    return liczbaKontaktow+1;
}

void wypiszKontakt(int numerKontaktu, vector<Adresat> &adresy){
	cout << adresy[numerKontaktu].idAdresata  << endl;
	cout << adresy[numerKontaktu].imie << " ";
	cout << adresy[numerKontaktu].nazwisko << endl;
	cout << adresy[numerKontaktu].adres << endl;
	cout << adresy[numerKontaktu].numerTelefonu << endl;
	cout << adresy[numerKontaktu].email << endl << endl;
}

void wyszukajKontaktPoImieniu(int liczbaKontaktow, vector<Adresat> &adresy){
	int sprawdzono = 0;
	string imie;

	system("cls");
	cout << "Wpisz imie: ";
	cin >> imie;
	system("cls");

	for(int i=0; i<liczbaKontaktow; i++){
		if(adresy[i].imie==imie){
			wypiszKontakt(i, adresy);
		}
		else{
			sprawdzono++;
		}
	}

	if(sprawdzono==liczbaKontaktow){
		cout << "Nie znaleziono pasujacych wynikow." << endl << endl;
	}

	system("pause");
}

void wyszukajKontaktPoNazwisku(int liczbaKontaktow, vector<Adresat> &adresy){
	int sprawdzono = 0;
	string nazwisko;

	system("cls");
	cout << "Wpisz nazwisko: ";
	cin >> nazwisko;
	system("cls");

	for(int i=0; i<liczbaKontaktow; i++){
		if(adresy[i].nazwisko==nazwisko){
			wypiszKontakt(i, adresy);
		}
		else{
			sprawdzono++;
		}
	}
	if(sprawdzono==liczbaKontaktow){
		cout << "Nie znaleziono pasujacych wynikow." << endl << endl;
	}

	system("pause");
}

void wypiszWszystkieKontakty(int liczbaKontaktow, vector<Adresat> &adresy){
	system("cls");
	cout << "Liczba Kontaktow: " << liczbaKontaktow << endl << endl;
	for(int i=0; i<liczbaKontaktow; i++){
		wypiszKontakt(i, adresy);
	}
	system("pause");
}

int wyszukajKontaktPoID(int id, vector<Adresat> &adresy){
    int index = 0;
    int length = adresy.size();

    while(adresy[index].idAdresata != id && index < length){
        index++;
    }

    return index;
}

void usunAdresata(int &liczbaKontaktow, vector<Adresat> &adresy, int index, int wybraneID){
    fstream plik;

    adresy.erase(adresy.begin() + index);
    liczbaKontaktow--;

    plik.open("ksiazka_adresowa_nowy_format.txt", ios::trunc | ios::out);
    if(plik.good()==false){
        cout << "Nie udalo sie otworzyc pliku. Program zostanie zamkniety.";
        exit(0);
    }

    for(int i=0, length=adresy.size(); i<length; i++){
         plik << adresy[i].idAdresata << "|" << adresy[i].idUzytkownika << "|" << adresy[i].imie << "|" << adresy[i].nazwisko << "|" << adresy[i].adres << "|" << adresy[i].numerTelefonu << "|" << adresy[i].email << "|" << endl;
    }

    plik.close();
}

void przejdzDoUsuwaniaAdresata(int &liczbaKontaktow, vector<Adresat> &adresy){
    string wybraneIDJakoString = "";
    char wybor = '0';
    int wybraneID = 0;
    system("cls");
    cout << "Wpisz id adresata, ktorego chcesz usunac: ";
    getline(cin, wybraneIDJakoString);
    wybraneID = atoi(wybraneIDJakoString.c_str());
    int index = wyszukajKontaktPoID(wybraneID, adresy);

    if(index >= 0 && index < adresy.size()){
        cout << endl << "Czy na pewno chcesz usunac adresata: " << adresy[index].imie << " " << adresy[index].nazwisko << " ?" << endl << endl;
        cout << "Aby usunac wybranego adresata, nacisnij: t" << endl << endl;
        cout << "Aby powrocic do menu, nacisnij dowolny inny klawisz." << endl;

        wybor = getch();
        if(wybor == 't' || wybor == 'T'){
            usunAdresata(liczbaKontaktow, adresy, index, wybraneID);
        }
    }
    else{
        cout << "Nie znaleziono adresata o podanym id." << endl;
        Sleep(3000);
    }
}

void edytujAtrybutAdresata(int index, int wybraneID, vector<Adresat> &adresy, string &atrybut){
    fstream plik;

    system("cls");
    cout << "Podaj nowy atrybut adresata: " << endl;
    getline(cin, atrybut);

    plik.open("ksiazka_adresowa_nowy_format.txt", ios::trunc | ios::out);
    if(plik.good()==false){
        cout << "Nie udalo sie otworzyc pliku. Program zostanie zamkniety.";
        exit(0);
    }

    for(int i=0, length=adresy.size(); i<length; i++){
         plik << adresy[i].idAdresata << "|" << adresy[i].idUzytkownika << "|" << adresy[i].imie << "|" << adresy[i].nazwisko << "|" << adresy[i].adres << "|" << adresy[i].numerTelefonu << "|" << adresy[i].email << "|" << endl;
    }

    plik.close();
}

void edytujAdresata(int index, int id, vector<Adresat> &adresy){
    char wybor = '0';
    cout << endl << "Edycja adresata: " << endl << endl;
    wypiszKontakt(index, adresy);
    cout << "Wybierz, ktory atrybut chcesz zmienic." << endl << endl;
    cout << "1 - imie" << endl;
    cout << "2 - nazwisko" << endl;
    cout << "3 - adres" << endl;
    cout << "4 - numer telefonu" << endl;
    cout << "5 - email" << endl << endl;
    cout << "6 - powrot do menu" << endl;

    wybor = getch();

    switch(wybor){
        case '1':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].imie);
            break;

        case '2':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].nazwisko);
            break;

        case '3':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].adres);
            break;

        case '4':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].numerTelefonu);
            break;

        case '5':
            edytujAtrybutAdresata(index, id, adresy, adresy[index].email);
            break;

        case '6':
            ;
            break;

        default:
            ;
            break;
    }
}

void przejdzdoEdycjiAdresata(int liczbaKontaktow, vector<Adresat> &adresy){
    string wybraneIDJakoString = "";
    int wybraneID = 0;

    system("cls");
    cout << "Wpisz id adresata, ktorego chcesz edytowac: ";

    getline(cin, wybraneIDJakoString);
    wybraneID = atoi(wybraneIDJakoString.c_str());
    int index = wyszukajKontaktPoID(wybraneID, adresy);

    if(index >= 0 && index < adresy.size()){
        edytujAdresata(index, wybraneID, adresy);
    }
    else{
        cout << "Nie znaleziono adresata o podanym id." << endl;
        Sleep(3000);
    }
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
                    liczbaKontaktow = wczytajAdresatowZPliku(adresaci, idUzytkownika);
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
				liczbaKontaktow = dodajKontakt(liczbaKontaktow, adresaci, idUzytkownika);
				break;

			case '2':
				wyszukajKontaktPoImieniu(liczbaKontaktow, adresaci);
				break;

            case '3':
				wyszukajKontaktPoNazwisku(liczbaKontaktow, adresaci);
				break;

			case '4':
				wypiszWszystkieKontakty(liczbaKontaktow, adresaci);
				break;

            case '5':
				przejdzDoUsuwaniaAdresata(liczbaKontaktow, adresaci);
				break;

            case '6':
				przejdzdoEdycjiAdresata(liczbaKontaktow, adresaci);
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
