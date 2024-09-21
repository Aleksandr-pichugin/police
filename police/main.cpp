#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable: 4326)
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

const std::map<int, std::string> VIOLATIONS =
{
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

	// Constractors:
	Crime(int violation_id, const std::string& place, const std::string& time)
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
};
std::ostream& operator<<(std::ostream& os, const Crime& obj)
{
	return os << obj.get_time() << "\t" << obj.get_place() << " - " << obj.get_violation();
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

void print(const std::map<std::string, std::list<Crime>>& base);
void save(const std::map<std::string, std::list<Crime>>& base, const std::string& filename);
std::map<std::string, std::list<Crime>> load(const std::string& filename);

//#define SAVE_CHECK
#define LOAD_CHECK

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

	std::map<std::string, std::list<Crime>> base = load("base.txt");
	print(base);

}
void print(const std::map<std::string, std::list<Crime>>& base)
{
	cout << delimiter << endl;
	for (std::map<std::string, std::list<Crime>>::const_iterator map_it = base.begin();
		map_it != base.end();
		++map_it)
	{
		cout << map_it->first << ":\n";
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
		{
			cout << *it << endl;
		}
		cout << delimiter << endl;
	}
	cout<<"���������� ������� � ����"<<base.size()<<endl; 
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
		for (std::list<Crime>::const_iterator it = map_it->second.begin(); it != map_it->second.end(); ++it)
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
			for (char* pch = strtok(sz_buffer, delimiters); pch; pch = strtok(NULL, delimiter))
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