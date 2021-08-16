#ifdef _WIN32
#include <windows.h>

void sleep(unsigned milliseconds)
{
	Sleep(milliseconds);
}
#else
#include <unistd.h>

void sleep(unsigned milliseconds)
{
	usleep(milliseconds * 1000); // takes microseconds
}
#endif
#include <fstream>
#include <iostream>
using namespace std;

#define DEBUG false
#define eczn_file "eczane_liste.dat"
#define pass "merhaba123"

class ilac
{
	int ilac_id;
	int ilac_sayisi;
	double ilac_fiyati;
	string ilac_ismi;

 public:
	static int id_counter;
	ilac()
	{
		ilac_sayisi = 0;
		ilac_fiyati = 0;
		ilac_ismi = "";
	}

	ilac(int sayi, double fiyat, string ismi)
	{
		ilac_sayisi = sayi;
		ilac_fiyati = fiyat;
		ilac_ismi = ismi;
	}

	ilac(const ilac& other)
	{
		ilac_sayisi = other.ilac_sayisi;
		ilac_fiyati = other.ilac_fiyati;
		ilac_ismi = other.ilac_ismi;
	}

	ilac& operator=(const ilac other)
	{
		ilac_sayisi = other.ilac_sayisi;
		ilac_fiyati = other.ilac_fiyati;
		ilac_ismi = other.ilac_ismi;
		return *this;
	}
	void isim(string isim)
	{
		ilac_ismi = isim;
	}
	void fiyat(double fiyat)
	{
		ilac_fiyati = fiyat;
	}
	void sayi(int sayi)
	{
		ilac_sayisi = sayi;
	}
	void id(int id)
	{
		ilac_id = id;
	}
	int id()
	{
		return ilac_id;
	}
	string isim()
	{
		return ilac_ismi;
	}
	double fiyat()
	{
		return ilac_fiyati;
	}
	int sayi()
	{
		return ilac_sayisi;
	}
	ilac& ilac_olustur();
	void print_all()
	{
		cout << "\nID: " << ilac_id << "\nIsim: " << ilac_ismi << "\nFiyati: " << ilac_fiyati << "\nAdedi:"
			 << ilac_sayisi
			 << "\n";
	}
	friend ostream& operator<<(ostream& output, const ilac& object)
	{
		return output << object.ilac_id << "\t" << object.ilac_ismi << "\t" << object.ilac_fiyati << "\t"
					  << object.ilac_sayisi << "\n";
	}

	friend istream& operator>>(istream& input, ilac& object)
	{
		input >> object.ilac_id >> object.ilac_ismi >> object.ilac_fiyati >> object.ilac_sayisi;

		return input;
	}
};

int ilac::id_counter = 0;

class eczn
{
	int eczn_id;
	string eczn_isim;
	string eczn_adres;

 public:
	int static eczn_counter;
	void print_all()
	{
		cout << "id: " << eczn_id << "\nisim: " << eczn_isim << "\nadres: " << eczn_adres << "\n";
	}

	eczn()
	{
		eczn_isim = "";
		eczn_adres = "";
	}
	eczn(string isim, string adres)
	{
		eczn_isim = isim;
		eczn_adres = adres;
	}

	eczn(const eczn& other)
	{
		eczn_isim = other.eczn_isim;
		eczn_adres = other.eczn_adres;
	}
	eczn& operator=(const eczn& other)
	{
		eczn_id = other.eczn_id;
		eczn_isim = other.eczn_isim;
		eczn_adres = other.eczn_adres;
		return *this;
	}

	/*  void eczn_olustur()
	void eczn_goster()
	void eczn_ilac_sayfasi()

	getve setfonksiyonları */
	int id()
	{
		return eczn_id;
	}
	string isim()
	{
		return eczn_isim;
	}
	string adres()
	{
		return eczn_adres;
	}
	void id(int id)
	{
		eczn_id = id;
	}
	void isim(string isim)
	{
		eczn_isim = isim;
	}
	void adres(string adres)
	{
		eczn_adres = adres;
	}

	friend ostream& operator<<(ostream& output, const eczn& object)
	{
		return output << object.eczn_id << "\t" << object.eczn_isim << "\t" << object.eczn_adres << "\n";
	}

	friend istream& operator>>(istream& input, eczn& object)
	{
		input >> object.eczn_id >> object.eczn_isim;
		getline(input, object.eczn_adres);
		// object.print_all();

		return input;
	}
};

int eczn::eczn_counter = 0;

void init_value();
int menu(int menu_loc);
int main_menu();
void eczn_ekle();
bool liste_kontrol(string isim);
void eczn_liste_olustur();
void ilac_ekle(string isim = "");
int id_bul(string obj);
void ilac_duzenle();
void edit_line(string file_name, int line);
void ilac_ara();
void eczn_listele();
void eczn_ara();
void eczn_liste_ara();

int main()
{
	init_value();

	string ext = ".txt";
	int menu_loc = 0;
	int menu_choice;

	bool loop = true;
	while (loop)
	{

		if (menu_loc == 3)
		{
			loop = false;
			break;
		}
		else if (menu_loc == 0)
		{
			menu_loc = main_menu();
		}
		else if (menu_loc == 1)
		{
			menu_choice = menu(menu_loc);
			//Eczane Menusu
			switch (menu_choice)
			{
			case 1:
				eczn_liste_olustur();
				break;
			case 2:
				eczn_ekle();
				break;
			case 3:
				ilac_ekle();
				break;
			case 4:
				ilac_duzenle();
				break;
			case 5:
				menu_loc = 0;
				break;
			}

		}
		else if (menu_loc == 2)
		{
			menu_choice = menu(menu_loc);
			//Musteri Menusu
			switch (menu_choice)
			{
			case 1:
				ilac_ara();
				break;
			case 2:
				eczn_listele();
				break;
			case 3:
				eczn_ara();
				break;
			case 4:
				eczn_liste_ara();
				break;
			case 5:
				menu_loc = 0;
				break;
			}
		}
	}

	return 0;
}

int main_menu()
{
	int choice;
	cout << "\n1. Eczane Girisi\n";
	cout << "2. Musteri Girisi\n";
	cout << "3. Cikis\n";
	cin >> choice;

	if (choice == 1)
	{
		cout << "Parolayi giriniz: ";
		string parola;
		cin >> parola;
		if (parola == pass)
		{
			cout << "Parola kabul edildi.\n\n";
			return choice;
		}
		else
		{
			cout << "\nYanlis Parola!\n";
			return 0;
		}
	}
	return choice;
}

int menu(int menu_loc)
{
	int choice;

	if (menu_loc == 1)
	{
		cout << "Eczane Girisi:\n\n";
		cout << "\t1. Eczane listesi olustur\n";
		cout << "\t2. Eczane ekle\n";
		cout << "\t3. Ilac ekle\n";
		cout << "\t4. Ilac duzenle\n";
		cout << "\t5. Ana Menu\n";
		cin >> choice;
		return choice;
	}
	else if (menu_loc == 2)
	{
		cout << "Musteri Girisi:\n\n";
		cout << "\t1. Ilac ara\n";
		cout << "\t2. Eczane listele\n";
		cout << "\t3. Herhangi bir Eczaneyi Goster\n";
		cout << "\t4. Herhangi bir Eczaneye ait Ilac Listesi\n";
		cout << "\t5. Ana Menu\n";
		cin >> choice;
		return choice;
	}
	else
		return 0;
}

void init_value()
{
	string prefix = "_ilac.dat";
	string check;
	int max = 0, max2 = 0, curr, curr2;;
	ifstream input;
	input.open(eczn_file, ios::in);
	{
		eczn buff;
		ilac buff2;

		while (input >> buff)
		{
			curr = buff.id();
			// buff.print_all();

			if (curr > max)
			{
				if (DEBUG)
					cout << "new max: " << curr << "\nold max: " << max << "\n";
				max = curr;
			}
			check = buff.isim();

			if (liste_kontrol(check))
			{
				check += prefix;
				//cout << "\nchecking: " << check;
				ifstream input2(check);
				while (input2 >> buff2)
				{
					curr2 = buff2.id();
					//buff2.print_all();
					if (curr2 > max2)
					{
						//cout << "new max2: " << curr2 << "\nold max2: " << max2 << "\n";
						max2 = curr2;
					}
				}
			}
		}
	}
	cout << "Eczane ID sayaci: " << max << "\nIlac ID sayaci: " << max2 << "\n///////////////////////////////\n\n";
	ilac::id_counter = max2;
	eczn::eczn_counter = max;
	return;
}

ilac& ilac::ilac_olustur()
{

	cout << "\nIlac ismi: ";
	cin >> ilac_ismi;

	cout << "\nIlac sayisi: ";
	cin >> ilac_sayisi;

	cout << "\nIlac fiyati: ";
	cin >> ilac_fiyati;

	return *this;
}

void eczn_ekle()
{
	string isim;
	string adres;

	cout << "\tEczane Ekle:\n";
	cout << "\n\t\tEczane ismi: ";
	cin >> isim;
	cout << "\n\t\tEczane adresi: ";
	cin.ignore();
	getline(cin, adres);
	{
		eczn ekle(isim, adres);
		ekle.id(++eczn::eczn_counter);
		ofstream output;
		output.open(eczn_file, ios::app);
		output << ekle;
		output.close();
	}
}

bool liste_kontrol(string isim)
{
	string prefix = "_ilac.dat";
	string check = isim + prefix;

	ifstream input(check);
	return input.good();
}

void eczn_liste_olustur()
{
	ifstream input(eczn_file);
	eczn buff;
	eczn array[eczn::eczn_counter];

	int counter = 0;

	while (input >> buff)
	{
		if (!liste_kontrol(buff.isim()))
		{
			array[counter] = buff;
			counter++;
		}
	}
	input.close();

	if (counter == 0)
	{
		cout << "\n\tSistemde her eczanenin listesi mevcuttur.\n\n";
		return;
	}

	cout << "\n\tListesi Olmayan Eczaneler:\n";
	for (int i = 0; i < counter; ++i)
	{
		cout << "\n\t" << i + 1 << ": " << array[i].isim();
	}
	cout << "\n\n\t Secim yapiniz: ";
	int choice;
	cin >> choice;
	choice--;
	string prefix = "_ilac.dat";
	string isim = array[choice].isim();
	string file = isim + prefix;
	ofstream output(file);
	output.close();
	cout << "\n\tListe basariyla olusturulmustur.\n\n";
}

void ilac_ekle(string isim)
{
	string prefix = "_ilac.dat";
	string file;
	if (isim == "")
	{
		//listesi olanları sıralayıp seçim yaptır
		ifstream input(eczn_file);
		eczn buff;
		eczn array[eczn::eczn_counter];
		int counter = 0;

		while (input >> buff)
		{
			if (liste_kontrol(buff.isim()))
			{
				array[counter] = buff;
				counter++;
			}
		}
		input.close();
		if (counter == 0)
		{
			cout << "\n\tKayitli eczane listesi yoktur.\nOnce liste olusturun.\n\n";
			return;
		}

		cout << "\n\tEkleme yapilabilen Eczaneler:\n";
		for (int i = 0; i < counter; ++i)
		{
			cout << "\n\t\t" << i + 1 << ": " << array[i].isim();
		}
		cout << "\n\n\t Secim yapiniz: ";
		int choice;
		cin >> choice;
		choice--;
		isim = array[choice].isim();
	}

	file = isim + prefix;
	cout << "\n\n\t" << file << " dosyasi secildi.\n";
	ilac buffer;
	buffer.ilac_olustur();
	buffer.id(id_bul(buffer.isim()));

	ofstream output(file, ios::app);
	output << buffer;

	output.close();
}

int id_bul(string obj)
{

	string prefix = "_ilac.dat";
	string check;
	string curr;
	ifstream input;
	input.open(eczn_file, ios::in);
	{
		eczn buff;
		ilac buff2;

		while (input >> buff)
		{
			check = buff.isim();
			if (liste_kontrol(check))
			{
				check += prefix;
				//cout << "\nchecking: " << check;
				ifstream input2(check);
				while (input2 >> buff2)
				{
					//buff2.print_all();
					curr = buff2.isim();
					if (obj == curr)
					{
						//cout << check << " dosyasında " << curr << "isimli ilac bulunmustur, id: " << buff2.id() << "\n";
						return buff2.id();
					}
				}
			}
		}
		int id = ++ilac::id_counter;
		//cout << "\nfounded id: " << id << "\n";
		return id;
	}
}

void ilac_duzenle()
{
	string file;
	{
		ifstream input(eczn_file);
		eczn buff;
		string array[eczn::eczn_counter];

		int counter = 0;

		while (input >> buff)
		{
			if (liste_kontrol(buff.isim()))
			{
				array[counter] = buff.isim();
				counter++;
			}
		}
		input.close();

		if (counter == 0)
		{
			cout << "\n\tEczane listesi bulunamamistir.\n\n";
			return;
		}

		cout << "\n\tListesi Olan Eczaneler:\n";
		for (int i = 0; i < counter; ++i)
		{
			cout << "\n\t" << i + 1 << ": " << array[i];
		}
		cout << "\n\n\tDuzenlemek icin secim yapiniz: ";
		int choice;
		cin >> choice;
		choice--;
		string prefix = "_ilac.dat";
		string isim = array[choice];
		file = isim + prefix;
	}

	ifstream input(file);
	ilac buff;
	int line, counter = 0;
	while (input >> buff)
	{
		cout << "\n[" << ++counter << "]/////////////////////////";
		buff.print_all();
	}
	if (!counter)
	{
		cout << "\nListede Ilac Yok!\n\n";
		return;
	}
	cout << "\nSecim yapin: ";
	int choice;
	cin >> choice;
	edit_line(file, choice);
}

void edit_line(string file_name, int line)
{
	//ToDo belirlediğim satır haricindekileri başka bir dosyaya yazsın sonra ilk dosyayı sildin sonra yazdığını rename
	ifstream input(file_name);

	ilac array[ilac::id_counter];
	int counter = 0;

	while (input >> array[counter])
	{
		counter++;
	}

	cout << "\nEski fiyat: " << array[line - 1].fiyat() << " Yeni fiyati giriniz: ";
	double t;
	cin >> t;
	array[line - 1].fiyat(t);

	int t2;
	cout << "\nEski adet: " << array[line - 1].sayi() << " Yeni sayiyi giriniz: ";
	cin >> t2;
	array[line - 1].sayi(t2);

	input.close();
	ofstream output;
	output.open(file_name, ios::trunc);
	for (int i = 0; i < counter; i++)
	{
		output << array[i];
	}
}

void ilac_ara()
{
	cout << "\nIlac Arama:\n\n";
	cout << "\tIlac ismi giriniz: ";
	string isim;
	cin >> isim;

	string prefix = "_ilac.dat";

	{
		string file;
		{
			ifstream eczn_input(eczn_file);
			eczn eczn_buff;
			ilac ilac_buff;

			while (eczn_input >> eczn_buff)
			{
				file = eczn_buff.isim();
				if (liste_kontrol(file))
				{
					file += prefix;
					ifstream ilac_input(file);
					while (ilac_input >> ilac_buff)
					{
						if (ilac_buff.isim() == isim)
						{
							cout << "/////////////////////////////////////\n";
							cout << eczn_buff.isim() << " Eczanesinde:\n";
							ilac_buff.print_all();
							sleep(3000);
						}
					}
					ilac_input.close();
				}
			}
			eczn_input.close();
		}
	}
}

void eczn_listele()
{
	ifstream eczn_input(eczn_file);
	eczn eczn_buff;

	while (eczn_input >> eczn_buff)
	{
		eczn_buff.print_all();
		sleep(888);
		cout << "\n";
	}
}

void eczn_ara()
{
	ifstream eczn_input(eczn_file);
	eczn eczn_buff;

	string name;
	cout << "Eczane Arama:\n";
	cout << "\n\tEczane ismini girin: ";
	cin >> name;
	cout << "\n";

	while (eczn_input >> eczn_buff)
	{
		if (eczn_buff.isim() == name)
		{
			eczn_buff.print_all();
			sleep(777);
			cout << "\n";
			return;
		}
	}
	cout << "Aradiginiz Eczane bulunamadi, Menu 2.2'den eczane listesini inceleyebilirsiniz.\n\n";
	sleep(1111);
	return;
}

void eczn_liste_ara()
{

	eczn eczn_buff;
	ilac ilac_buff;
	string pretext = "_ilac.dat";
	string name;

	cout << "Eczane Liste Gosterici:\n";
	cout << "\n\tEczane ismini girin: ";
	cin >> name;
	cout << "\n";

	if (liste_kontrol(name))
	{
		name += pretext;
	}

	else
	{
		cout << "Aradiginiz liste bulunamamistir.\n\n";
		sleep(555);
		return;
	}

	ifstream ilac_input(name);

	while (ilac_input >> ilac_buff)
	{
		cout << "/////////////////////////////////////\n";
		ilac_buff.print_all();
		sleep(2222);
		cout << "\n";

	}
}