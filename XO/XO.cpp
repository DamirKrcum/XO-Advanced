#include <iostream>
#include <iomanip>
using namespace std;
char* AlocirajIKopiraj(const char* tekst) {
	if (tekst == nullptr)
		return nullptr;
	int vel = strlen(tekst) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, tekst);
	return temp;
}
const int redova = 3;
const int kolona = 3;
int _igracNaPotezu = 0;
int _brojacPoteza = 0;
class igrac {
private:
	const char* _ime;
	int pobjede;
	int brojpoteza;
public:
	igrac() {
		_ime = nullptr;
		pobjede = 0;
		brojpoteza = 0;
	}
	~igrac() {
		delete[] _ime;
		_ime = nullptr;
	}
	igrac(const char* ime) {
		_ime = AlocirajIKopiraj(ime);
		pobjede = 0;
		brojpoteza = 0;
	}

	int const GetBrojPoteza() {
		return brojpoteza;
	}
	int const GetBrojPobjeda() {
		return pobjede;
	}
	const char* GetIme() {
		return _ime;
	}
	void SetIme() {
		char temp[20];
		cout << "Ime igraca ";
		cin.getline(temp, 20);
		_ime = AlocirajIKopiraj(temp);
	}
	void dodajPotez() {
		brojpoteza++;
	}
	void dodajPobjedu() {
		pobjede++;
	}


	void oduzmiPotez() {
		brojpoteza--;
	}
	char simbol(char s) {
		return s;
	}
	int odigraj() {
		int lok;
		cin >> lok;

		return lok;
	}
};

class xo {

private:
	char _niz[redova][kolona];
	bool _krajIgre;

	void PozicijaIzLokacije(int lokacija, int& r, int& k) {
		switch (lokacija) {
		case 1: r = 0, k = 0;
			break;
		case 2: r = 0, k = 1;
			break;
		case 3: r = 0, k = 2;
			break;
		case 4: r = 1, k = 0;
			break;
		case 5: r = 1, k = 1;
			break;
		case 6: r = 1, k = 2;
			break;
		case 7: r = 2, k = 0;
			break;
		case 8: r = 2, k = 1;
			break;
		case 9: r = 2, k = 2;
			break;
		}


	}
	igrac X;
	igrac O;

public:
	xo() {
		_igracNaPotezu = 0;
		_krajIgre = false;
		OcistiMatricu();
	}
	void OcistiMatricu() {
		for (int i = 0; i < redova; i++)
			for (int j = 0; j < kolona; j++)
				_niz[i][j] = ' ';
	}
	void DodajIgrace() {
		cout << " X:";
		X.SetIme();
		cout << " O:";
		O.SetIme();

	}
	void Ispis() {
		cout << "Rezultat: " << "(X)" << X.GetIme() << " -> " << X.GetBrojPobjeda() << "  :  " << O.GetBrojPobjeda() << " <- " << O.GetIme() << "(O)" << endl;
		cout << "BROJ POTEZA:" << "(X)" << X.GetIme() << " -> " << X.GetBrojPoteza() << "  :  " << O.GetBrojPoteza() << " <- " << O.GetIme() << "(O)" << endl;

		for (int i = 0; i < redova; i++) {
			for (int j = 0; j < kolona; j++)
				cout << "+---";
			cout << "+" << endl;

			for (int j = 0; j < kolona; j++)
				cout << "|" << setw(3) << _niz[i][j];
			cout << "|" << endl;
		}
		for (int j = 0; j < kolona; j++)
			cout << "+---";
		cout << "+" << endl;

	}
	void Igraj(int lokacija) {

		int r = 0, k = 0;
		PozicijaIzLokacije(lokacija, r, k);
		if (_niz[r][k] == ' ') {
			if (_igracNaPotezu % 2 == 0) {
				_niz[r][k] = X.simbol('X');
				_igracNaPotezu++;
				X.dodajPotez();
			}
			else {
				_niz[r][k] = O.simbol('O');
				_igracNaPotezu++;
				O.dodajPotez();
			}
			if (ProvjeriKolone() || ProvjeriRedove() || ProvjeriDijagonalu1() || ProvjeriDijagonalu2()) {

				_krajIgre = true;
			}
		}
		else {
			cout << "Lokacija zauzeta" << endl;

		}
	}
	bool getKrajIgre() {
		char odabir;
		if (_krajIgre == true) {
			system("cls");
			Ispis();
			cout << "(N)ova partija / Bilo koje slovo za izlaz: ";
			cin >> odabir;
			if (odabir == 'N' || odabir == 'n') {
				system("cls");
				OcistiMatricu();
				_brojacPoteza = 0;
				_krajIgre = false;
			}



		}
		return _krajIgre;

	}
	void setKraj() {
		_krajIgre = true;
		_brojacPoteza = 0;
	}
	bool ProvjeriKolone() {
		char PrviZnak;
		int brojac;
		for (int j = 0; j < kolona; j++)
		{
			PrviZnak = _niz[0][j];
			brojac = 0;
			if (PrviZnak != ' ') {
				for (int i = 0; i < redova; i++)
					if (PrviZnak == _niz[i][j])
						brojac++;
				if (brojac == 3) {
					(_igracNaPotezu % 2 == 0) ? O.dodajPobjedu() : X.dodajPobjedu();
					return true;
				}
			}
		}
		return false;
	}
	bool ProvjeriRedove() {
		char PrviZnak;
		int brojac;
		for (int i = 0; i < kolona; i++)
		{
			PrviZnak = _niz[i][0];
			brojac = 0;
			if (PrviZnak != ' ') {
				for (int j = 0; j < redova; j++)
					if (PrviZnak == _niz[i][j])
						brojac++;
				if (brojac == 3) {
					(_igracNaPotezu % 2 == 0) ? O.dodajPobjedu() : X.dodajPobjedu();
					return true;
				}
			}
		}
		return false;
	}
	bool ProvjeriDijagonalu1() {
		char PrviZnak = _niz[0][0];
		if (PrviZnak == ' ')
			return false;

		if (PrviZnak == _niz[1][1] && PrviZnak == _niz[2][2])
		{
			(_igracNaPotezu % 2 == 0) ? O.dodajPobjedu() : X.dodajPobjedu();
			return true;
		}
		else
			return false;
	}
	bool ProvjeriDijagonalu2() {
		char PrviZnak = _niz[0][2];
		if (PrviZnak == ' ')
			return false;
		if (PrviZnak == _niz[1][1] && PrviZnak == _niz[2][0]) {
			(_igracNaPotezu % 2 == 0) ? O.dodajPobjedu() : X.dodajPobjedu();
			return true;
		}
		else
			return false;

	}

};

void Ocisti() {
	system("cls");
}
void  main()
{
	xo igra;
	igra.DodajIgrace();
	int lokacija = 0;
	do {
		
		igra.Ispis();
		if (_brojacPoteza < 9) {
			cout << "Lokacija->";
			cin >> lokacija;

			Ocisti();
			_brojacPoteza++;
			igra.Igraj(lokacija);
		}
		else{
			igra.OcistiMatricu();
			igra.setKraj();
			system("cls");
		}
		

	} while (igra.getKrajIgre() == false);


}