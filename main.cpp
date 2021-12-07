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
#define pharmacy_file "pharmacy_list.dat"
#define pass "merhaba123"

class medicine
{
	int medicine_id;
	int medicine_count;
	double medicine_price;
	string medicine_name;

 public:
	static int id_counter;
	medicine()
	{
		medicine_count = 0;
		medicine_price = 0;
		medicine_name = "";
	}

	medicine(int number, double price, string name)
	{
		medicine_count = number;
		medicine_price = price;
		medicine_name = name;
	}

	medicine(const medicine& other)
	{
		medicine_count = other.medicine_count;
		medicine_price = other.medicine_price;
		medicine_name = other.medicine_name;
	}

	medicine& operator=(const medicine other)
	{
		medicine_count = other.medicine_count;
		medicine_price = other.medicine_price;
		medicine_name = other.medicine_name;
		return *this;
	}
	void name(string name)
	{
		medicine_name = name;
	}
	void price(double price)
	{
		medicine_price = price;
	}
	void number(int number)
	{
		medicine_count = number;
	}
	void id(int id)
	{
		medicine_id = id;
	}
	int id()
	{
		return medicine_id;
	}
	string name()
	{
		return medicine_name;
	}
	double price()
	{
		return medicine_price;
	}
	int count()
	{
		return medicine_count;
	}
	medicine& create_medicine();
	void print_all()
	{
		cout << "\nID: " << medicine_id << "\nName: " << medicine_name << "\nPrice: " << medicine_price << "\nCount:"
			 << medicine_count
			 << "\n";
	}
	friend ostream& operator<<(ostream& output, const medicine& object)
	{
		return output << object.medicine_id << "\t" << object.medicine_name << "\t" << object.medicine_price << "\t"
					  << object.medicine_count << "\n";
	}

	friend istream& operator>>(istream& input, medicine& object)
	{
		input >> object.medicine_id >> object.medicine_name >> object.medicine_price >> object.medicine_count;

		return input;
	}
};

int medicine::id_counter = 0;

class pharmacy
{
	int pharmacy_id;
	string pharmacy_name;
	string pharmacy_address;

 public:
	int static pharmacy_counter;
	void print_all()
	{
		cout << "id: " << pharmacy_id << "\nisim: " << pharmacy_name << "\nadres: " << pharmacy_address << "\n";
	}

	pharmacy()
	{
		pharmacy_name = "";
		pharmacy_address = "";
	}
	pharmacy(string name, string address)
	{
		pharmacy_name = name;
		pharmacy_address = address;
	}

	pharmacy(const pharmacy& other)
	{
		pharmacy_name = other.pharmacy_name;
		pharmacy_address = other.pharmacy_address;
	}
	pharmacy& operator=(const pharmacy& other)
	{
		pharmacy_id = other.pharmacy_id;
		pharmacy_name = other.pharmacy_name;
		pharmacy_address = other.pharmacy_address;
		return *this;
	}

	int id()
	{
		return pharmacy_id;
	}
	string name()
	{
		return pharmacy_name;
	}
	string address()
	{
		return pharmacy_address;
	}
	void id(int id)
	{
		pharmacy_id = id;
	}
	void name(string name)
	{
		pharmacy_name = name;
	}
	void address(string address)
	{
		pharmacy_address = address;
	}

	friend ostream& operator<<(ostream& output, const pharmacy& object)
	{
		return output << object.pharmacy_id << "\t" << object.pharmacy_name << "\t" << object.pharmacy_address << "\n";
	}

	friend istream& operator>>(istream& input, pharmacy& object)
	{
		input >> object.pharmacy_id >> object.pharmacy_name;
		getline(input, object.pharmacy_address);
		// object.print_all();

		return input;
	}
};

int pharmacy::pharmacy_counter = 0;

void init_value();
int menu(int menu_loc);
int main_menu();
void add_pharmacy();
bool list_check(string isim);
void create_pharmacy_list();
void add_list(string isim = "");
int find_id(string obj);
void edit_medicine();
void edit_line(string file_name, int line);
void search_medicine();
void list_pharmacies();
void search_pharmacy();
void search_pharmacy_list();

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
			//Pharmacy Menu
			switch (menu_choice)
			{
			case 1:
				create_pharmacy_list();
				break;
			case 2:
				add_pharmacy();
				break;
			case 3:
				add_list();
				break;
			case 4:
				edit_medicine();
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
				search_medicine();
				break;
			case 2:
				list_pharmacies();
				break;
			case 3:
				search_pharmacy();
				break;
			case 4:
				search_pharmacy_list();
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
	cout << "\n1. Pharmacy Interface\n";
	cout << "2. Customer Interface\n";
	cout << "3. Exit\n";
	cin >> choice;

	if (choice == 1)
	{
		cout << "Password: ";
		string passw;
		cin >> passw;
		if (passw == pass)
		{
			cout << "Correct Password.\n\n";
			return choice;
		}
		else
		{
			cout << "\nIncorrect Password!\n";
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
		cout << "\nPharmacy Interface:\n\n";
		cout << "\t1. Create Pharmacy List\n";
		cout << "\t2. Add Pharmacy\n";
		cout << "\t3. Add Medicine\n";
		cout << "\t4. Update Medicine\n";
		cout << "\t5. Back to Main Menu\n";
		cin >> choice;
		return choice;
	}
	else if (menu_loc == 2)
	{
		cout << "Customer Interface:\n\n";
		cout << "\t1. Search Medicine";
		cout << "\t2. List Pharmacies\n";
		cout << "\t3. Show information of the Pharmacy\n";
		cout << "\t4. Show the medicine list of the Pharmacy\n";
		cout << "\t5. Back to Main Menu\n";
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
	input.open(pharmacy_file, ios::in);
	{
		pharmacy buff;
		medicine buff2;

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
			check = buff.name();

			if (list_check(check))
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
	medicine::id_counter = max2;
	pharmacy::pharmacy_counter = max;
	return;
}

medicine& medicine::create_medicine()
{

	cout << "\nMedicine's Name: ";
	cin >> medicine_name;

	cout << "\nMedicine'stock: ";
	cin >> medicine_count;

	cout << "\nMedicine's Price: ";
	cin >> medicine_price;

	return *this;
}

void add_pharmacy()
{
	string isim;
	string adres;

	cout << "\tAdd Pharmacy:\n";
	cout << "\n\t\tPharmacy Name: ";
	cin >> isim;
	cout << "\n\t\tPharmacy Address: ";
	cin.ignore();
	getline(cin, adres);
	{
		pharmacy ekle(isim, adres);
		ekle.id(++pharmacy::pharmacy_counter);
		ofstream output;
		output.open(pharmacy_file, ios::app);
		output << ekle;
		output.close();
	}
}

bool list_check(string isim)
{
	string prefix = "_ilac.dat";
	string check = isim + prefix;

	ifstream input(check);
	return input.good();
}

void create_pharmacy_list()
{
	ifstream input(pharmacy_file);
	pharmacy buff;
	pharmacy array[pharmacy::pharmacy_counter];

	int counter = 0;

	while (input >> buff)
	{
		if (!list_check(buff.name()))
		{
			array[counter] = buff;
			counter++;
		}
	}
	input.close();

	if (counter == 0)
	{
		cout << "\n\tEvery Pharmacy has their Medicine List on the Database.\n\n";
		return;
	}

	cout << "\n\tPharmacies that doesnt have their Medicine List:\n";
	for (int i = 0; i < counter; ++i)
	{
		cout << "\n\t" << i + 1 << ": " << array[i].name();
	}
	cout << "\n\n\t Make a Choice: ";
	int choice;
	cin >> choice;
	choice--;
	string prefix = "_ilac.dat";
	string isim = array[choice].name();
	string file = isim + prefix;
	ofstream output(file);
	output.close();
	cout << "\n\tThe List created successfully.\n\n";
}

void add_list(string isim)
{
	string prefix = "_ilac.dat";
	string file;
	if (isim == "")
	{
		//listesi olanları sıralayıp seçim yaptır
		ifstream input(pharmacy_file);
		pharmacy buff;
		pharmacy array[pharmacy::pharmacy_counter];
		int counter = 0;

		while (input >> buff)
		{
			if (list_check(buff.name()))
			{
				array[counter] = buff;
				counter++;
			}
		}
		input.close();
		if (counter == 0)
		{
			cout << "\n\tThere isnt a registered Pharmacy List.\nCreate one first.\n\n";
			return;
		}

		cout << "\n\tPharmacies that can be add on:\n";
		for (int i = 0; i < counter; ++i)
		{
			cout << "\n\t\t" << i + 1 << ": " << array[i].name();
		}
		cout << "\n\n\t Make a Choice: ";
		int choice;
		cin >> choice;
		choice--;
		isim = array[choice].name();
	}

	file = isim + prefix;
	cout << "\n\n\t" << file << " is selected.\n";
	medicine buffer;
	buffer.create_medicine();
	buffer.id(find_id(buffer.name()));

	ofstream output(file, ios::app);
	output << buffer;

	output.close();
}

int find_id(string obj)
{

	string prefix = "_ilac.dat";
	string check;
	string curr;
	ifstream input;
	input.open(pharmacy_file, ios::in);
	{
		pharmacy buff;
		medicine buff2;

		while (input >> buff)
		{
			check = buff.name();
			if (list_check(check))
			{
				check += prefix;
				//cout << "\nchecking: " << check;
				ifstream input2(check);
				while (input2 >> buff2)
				{
					//buff2.print_all();
					curr = buff2.name();
					if (obj == curr)
					{
						//cout << check << " dosyasında " << curr << "isimli ilac bulunmustur, id: " << buff2.id() << "\n";
						return buff2.id();
					}
				}
			}
		}
		int id = ++medicine::id_counter;
		//cout << "\nfounded id: " << id << "\n";
		return id;
	}
}

void edit_medicine()
{
	string file;
	{
		ifstream input(pharmacy_file);
		pharmacy buff;
		string array[pharmacy::pharmacy_counter];

		int counter = 0;

		while (input >> buff)
		{
			if (list_check(buff.name()))
			{
				array[counter] = buff.name();
				counter++;
			}
		}
		input.close();

		if (counter == 0)
		{
			cout << "\n\tCouldnt find the pharmacy list.\n\n";
			return;
		}

		cout << "\n\tPharmacies that has their list:\n";
		for (int i = 0; i < counter; ++i)
		{
			cout << "\n\t" << i + 1 << ": " << array[i];
		}
		cout << "\n\n\tSelect one to edit: ";
		int choice;
		cin >> choice;
		choice--;
		string prefix = "_ilac.dat";
		string isim = array[choice];
		file = isim + prefix;
	}

	ifstream input(file);
	medicine buff;
	int line, counter = 0;
	while (input >> buff)
	{
		cout << "\n[" << ++counter << "]/////////////////////////";
		buff.print_all();
	}
	if (!counter)
	{
		cout << "\nThere isnt a medicine in the list!\n\n";
		return;
	}
	cout << "\nMake a choice: ";
	int choice;
	cin >> choice;
	edit_line(file, choice);
}

void edit_line(string file_name, int line)
{
	//ToDo belirlediğim satır haricindekileri başka bir dosyaya yazsın sonra ilk dosyayı sildin sonra yazdığını rename
	ifstream input(file_name);

	medicine array[medicine::id_counter];
	int counter = 0;

	while (input >> array[counter])
	{
		counter++;
	}

	cout << "\nOld price: " << array[line - 1].price() << " Enter the new price: ";
	double t;
	cin >> t;
	array[line - 1].price(t);

	int t2;
	cout << "\nOld stock: " << array[line - 1].count() << " Enter the new stock: ";
	cin >> t2;
	array[line - 1].number(t2);

	input.close();
	ofstream output;
	output.open(file_name, ios::trunc);
	for (int i = 0; i < counter; i++)
	{
		output << array[i];
	}
}

void search_medicine()
{
	cout << "\nSearch Medicine:\n\n";
	cout << "\tEnter Medicine Name: ";
	string isim;
	cin >> isim;

	string prefix = "_ilac.dat";

	{
		string file;
		{
			ifstream eczn_input(pharmacy_file);
			pharmacy eczn_buff;
			medicine ilac_buff;

			while (eczn_input >> eczn_buff)
			{
				file = eczn_buff.name();
				if (list_check(file))
				{
					file += prefix;
					ifstream ilac_input(file);
					while (ilac_input >> ilac_buff)
					{
						if (ilac_buff.name() == isim)
						{
							cout << "/////////////////////////////////////\n";
							cout << eczn_buff.name() << " Pharmacy:\n";
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

void list_pharmacies()
{
	ifstream eczn_input(pharmacy_file);
	pharmacy eczn_buff;

	while (eczn_input >> eczn_buff)
	{
		eczn_buff.print_all();
		sleep(888);
		cout << "\n";
	}
}

void search_pharmacy()
{
	ifstream eczn_input(pharmacy_file);
	pharmacy eczn_buff;

	string name;
	cout << "Search Pharmacy:\n";
	cout << "\n\tEnter Pharmacy Name: ";
	cin >> name;
	cout << "\n";

	while (eczn_input >> eczn_buff)
	{
		if (eczn_buff.name() == name)
		{
			eczn_buff.print_all();
			sleep(777);
			cout << "\n";
			return;
		}
	}
	cout << "Couldnt find the searched Pharmacy,you can list Pharmacies through Menu 2.2.\n\n";
	sleep(1111);
	return;
}

void search_pharmacy_list()
{

	pharmacy eczn_buff;
	medicine ilac_buff;
	string pretext = "_ilac.dat";
	string name;

	cout << "Search Pharmacy List:\n";
	cout << "\n\tEnter Pharmacy Name: ";
	cin >> name;
	cout << "\n";

	if (list_check(name))
	{
		name += pretext;
	}

	else
	{
		cout << "Couldnt find the searched list.\n\n";
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