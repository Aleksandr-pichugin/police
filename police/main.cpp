#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4326)
#include <Windows.h>
#include <iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<conio.h>
#include<map>
#include<list>
#include<ctime>

using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n---------------------------------------\n"

#define ENTER 13
#define ESCAPE 27
#define UP_ARROW 72
#define DOWN_ARROW 80

/*const char* MENU_ITEMS[] =
{
	"1. ��������� ���� �� �����;",
"2.��������� ���� � ����",
"3.������� ���� �� �����",
"4.������� ���������� �� ������",
"5. �������� ���������",
};*/

//const char* MENU_VIOATIONS[] =
const std::map<int, std::string>MENU_ITEMS =
{
{ 1, " ��������� ���� �� �����; " },
{ 2, " ��������� ���� � ����" },
{3, " ������� ���� �� �����"},
{4," ������� ���������� �� ������" },
{ 5," �������� ���������" },
};

//const int MENU_SIZE =  sizeof(MENU_VIOLATIONS) / sizeof(MENU_VIOLATIONS[0]);



const std::map<int, std::string> VIOLATIONS =
{
	{0, "N/A"},
	{1,"������ ������������"},
	{2,"�������� � ������������ �����"},
	{3,"����������� ��������"},
	{4,"���������� ��������"},
	{5,"���������� ������������� �������������"},
	{6,"���������� ����� ���������� �����������"},
	{7,"���������� ���������"},
	{8,"������ �� �������"},
	{9,"����� �� ��������� ������"},
	{10,"����� �� �����������"},
	{11,"���� � ��������� ���������"},
	{12,"����������� �������"},
	{13,"�������� ��������� ����������� ����������"},
	{14,"��������� �� ����������� �����"},
	{15,"���������� ������������ �������� ��  ���"},
	{16,"��������� ������� ��� ������"},
};

class Crime
{
	//std::string license_plate;
	int id;
	std::string place;
	tm time;
public:
	/*const std::string& get_license_plate()const
	{
		return license_plate;
	}*/
	int get_violation_id()const
	{
		return id;
	}
	const std::string& get_violation()const
	{
		return VIOLATIONS.at(id);
	}
	const std::string& get_place()const
	{
		return place;
	}
	const std::string get_time()const
	{
		/*std::string result = asctime(&time);
		result.pop_back();
		return asctime(&time);*/
		const int SIZE = 256;
		char formatted[SIZE]{};
		strftime(formatted, SIZE, "%R %e.%m.%Y", &time);
		return formatted;
	}
	const time_t get_timestamp()const
	{
		tm copy = time;
		return mktime(&copy);
	}

	/*void set_license_plate(const std::string& license_plate)
	{
		this->license_plate = license_plate;
	}*/
	void set_violation_id(int id)
	{
		this->id = id;
	}
	void set_place(const std::string& place)
	{
		this->place = place;
	}
	void set_time(const std::string& time)
	{
		//������� ��������� ������ ��� ���� ����� ���������� ���������� ������ :
		char* time_buffer = new char[time.size() + 1] {};

		//�������� ���������� ������ � �����
		strcpy(time_buffer, time.c_str());
		//������� ��������(dst,src) ���������� ������ ���������(srt-Sourse) � ������ ����������(dst)

		//������� ������ ��� �������� ��������� �������
		int time_elements[5]{};
		int i = 0;
		char delimiters[] = ":./ ";
		for (char* pch = strtok(time_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			time_elements[i++] = std::atoi(pch);
		//������� std::atoi() 'ASCII-string to int' ����������� ������ � ����� �����.
		delete[] time_buffer;
		//��������� �������� ������� � ��������� 'tm':
		this->time.tm_hour = time_elements[0];
		this->time.tm_min = time_elements[1];
		this->time.tm_mday = time_elements[2];
		this->time.tm_mon = time_elements[3];
		this->time.tm_year = time_elements[4] - 1900;
	}

	void set_timestamp(time_t timestamp)
	{
		time = *localtime(&timestamp);
	}

	explicit Crime
	(
		int violation_id = 0,
		const std::string& place = "Place",
		const std::string& time = "00:00 01.01.2000"
	)
	{
		this->time = {};
		this->set_violation_id(violation_id);
		this->set_place(place);
		this->set_time(time);


		cout << "Constructor:\t" << this << endl;

	}
	~Crime()
	{
		cout << "Destructor:\t" << this << endl;
	}
};
	// Constractors:
	/*Crime(int violation_id, const std::string& place, const std::string& time)
	{
		//set_license_plate(license_plate);
		this->time = {};
		this->set_violation_id(violation_id);
		this->set_place(place);
		this->set_time(time);
#ifdef DEBUG
		cout << "Construktor:\t" << this << endl;
#endif // DEBUG
	}
	void set_timestamp(time_t timestamp)
	{
		time = *localtime(&timestamp);
	}
	~Crime()
	{
#ifdef DEBUG
		cout << "Destruktor:\t" << this << endl;
#endif // DEBUG
	}
};*/
std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << ":\t" << obj.get_place() << " - " << obj.get_violation();
}
std::ofstream& operator<<(std::ofstream& os, const Crime& obj)
{
	os << obj.get_violation_id() << " " << obj.get_timestamp() << " " << obj.get_place();
	return os;
}
std::istream& operator>>(std::istream& is, Crime& obj)
{
	int id;
	time_t timestamp;
	std::string place;
	is >> id >> timestamp;
	std::getline(is, place, ',');
	is.ignore();
	obj.set_violation_id(id);
	obj.set_timestamp(timestamp);
	obj.set_place(place);
	return is;
}
int menu();
void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
std::map<std::string, std::list<Crime>> load(const std::string& filename);
//int menu();

//#define SAVE_CHECK
//#define LOAD_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef SAVE_CHECK
	/*Crime crime(1, "��. ������", "18:10 1.09.2024");
cout << crime << endl;*/

	std::map<std::string, std::list<Crime>> base =
	{
		{"a777bb",{Crime(1,"�� ������","18:10 1.09.2024"), Crime(2,"��.�������","12:25 10.08.2024")}},
		{"a000bb",{Crime(6,"�� �����������", "17:50 1.08.2024"), Crime(8,"�� �����������" ,"17:45 01.08.2024")}},
		{"a001aa",{Crime(10,"�� ������������", "21:50 1.08.2024"), Crime(9,"�� ������������" ,"21:50 01.08.2024"), Crime(12,"�� ������������", "22:05 1.08.2024")}},
	};
	//cout << delimiter << endl;
	print(base);
	save(base, "base.txt");
#endif // SAVE_CHECK

#ifdef LOAD_CHECK
	std::map<std::string, std::list<Crime>> base = load("base.txt");
	print(base);
#endif // LOAD_CHECK
	std::map<std::string, std::list<Crime>> base = load("base.txt");
	do
	{
		switch (menu()) 
		{
		case 0: return;
		case 1: base = load("base.txt"); break;
		case 2: save(base, "base.txt"); break;
		case 3: print(base); break;
		case 4: cout << "����� ����� " << endl; break;
		case 5: cout << "����� ����� " << endl; break;
		}
	} while (true);
}
int menu()
{
	int selected_item = 1;
	char key;
	do
	{
		//key = _getch();
		system("CLS");
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		for (int i = 1; i <= MENU_ITEMS.size(); i++)
		{
			cout << (i == selected_item ? "[" : " ");
			cout << i << ". ";
			cout.width(32);
			cout << std::left;
			if (i == selected_item)SetConsoleTextAttribute(hConsole, 0x70);
			//SetConsoleTextAttribute(hConsole, 0x70);
			cout << MENU_ITEMS.at(i);
			SetConsoleTextAttribute(hConsole, 0x07);
			cout << (i == selected_item ? "  ]" : " "); 
			cout << endl;
		}
		key = _getch();
		switch (key)
		{
		case UP_ARROW: /*if (selected_item > 1)*/selected_item--; break;
		case DOWN_ARROW: /*if (selected_item < MENU_ITEMS.size())*/ selected_item++; break;
		case ENTER: return selected_item ;
		case ESCAPE: return 0;
		}
		if (selected_item == MENU_ITEMS.size() + 1)selected_item = 1;
		if (selected_item == 0)selected_item = MENU_ITEMS.size();
	} while (key != ESCAPE);
	return 0;
}

void print(const std::map<std::string, std::list<Crime>>& base)
{
	cout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end();
			++it)
		{
			cout<<"\t" << *it << endl;
		}
		cout << delimiter << endl;
	}
	cout<<"���������� ������� � ����"<<base.size()<<endl; 
	system("PAUSE");
}
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename)
{
	std::ofstream fout(filename);
	//fout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		fout << map_it->first << ":\t";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end();
			++it)
		{
			fout << *it<<",";
		}
		//fout.seekp(-1, std::ios::cur);
		// //����� seekp(offset,direction)������ ������� ������� ������ 
		//fout << ";\n";
		fout << endl;
	}
	fout.close();
	std::string command = "notepad " + filename;
	system(command.c_str());
}
std::map<std::string, std::list<Crime>> load(const std::string& filename)
{
	std::map<std::string, std::list<Crime>> base;
	std::ifstream fin(filename);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			std::string licence_plate;
			std::getline(fin, licence_plate,':'); 
			//if (licence_plate.empty())continue;
			licence_plate.erase(0, licence_plate.find_first_not_of('\n'));
			fin.ignore();

			std::string crimes;
			std::getline(fin, crimes);
			char* sz_buffer = new char[crimes.size() + 1] {};
			strcpy(sz_buffer, crimes.c_str());
			char delimiters[] = ",";
		    Crime crime(0, "place", "00:00 01.01.2000");
			for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiters))
			{
				//std::string s_crime(pch);
				std::stringstream ss_crime(pch, std::ios_base::in | std::ios_base::out);
				ss_crime >> crime;
				base[licence_plate].push_back(crime);
			}
			delete[] sz_buffer;
		}
		fin.close();
	}
	else
	{
		std::cerr << "error: file not found" << endl;
	}
	return base;
}