#include "Owner.h"

HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

Owner::Owner(string fullname, string INN)
{
	this->fullname = fullname;
	this->INN = INN;
}

Owner::Owner()
{
	this->fullname = "";
	this->INN = "";
}

void Owner::getOwnerData()
{
	cout << this->fullname << endl 
		<< "��� - " << this->INN << endl;

	for (int i = 0; i < this->properties.size(); i++)
	{
		this->properties[i]->printProp();
	}

	cout << endl;
}

int Owner::getCntProp()
{
	return this->properties.size();
}

vector<Property*> Owner::getProp()
{
	return this->properties;
}

void Owner::addProperty(Property* prop)
{
	this->properties.push_back(prop);
}

void Owner::delProperty(int id)
{
	this->properties.erase(this->properties.begin() + id - 1);
}

unsigned int Owner::sumWorth()
{
	unsigned int sum = 0;

	for (int i = 0; i < this->properties.size(); i++)
	{
		sum += this->properties[i]->getWorth();
	}

	return sum;
}

void Owner::fromJson(json json)
{
	this->fullname = json.at("fullname");
	this->INN = json.at("inn");
	auto props = json.at("properties").get<vector<Property>>();

	for (auto& prop : props)
	{
		string key = prop.items().begin().key();
		Property* prop = PropertyFactoryMethod::getProperty(key);
		prop->fromJson(json.at("key"));
		this->addProperty(prop);
	}
}

json Owner::toJson()
{
	return json();
}

Owner::~Owner()
{
	for (int i = 0; i < this->properties.size(); i++)
	{
		delete this->properties[i];
	}
}

void GoToXY(short x, short y)
{
	SetConsoleCursorPosition(hStdOut, { x, y });
}

void ConsoleCursorVisible(bool show, short size)
{
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(hStdOut, &structCursorInfo);
	structCursorInfo.bVisible = show;
	structCursorInfo.dwSize = size;
	SetConsoleCursorInfo(hStdOut, &structCursorInfo);
}

int PrintMenu(vector<string> &vecMenu, int &active_menu_point, int &key, bool &exitVar)
{
	while (!exitVar)
	{
		int x = 50, y = 12;
		GoToXY(x, y);

		for (int i = 0; i < vecMenu.size(); i++)
		{
			if (i == active_menu_point)
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
			}
			else
			{
				SetConsoleTextAttribute(hStdOut, FOREGROUND_GREEN);
			}
			GoToXY(x, y++);
			cout << vecMenu[i] << endl;
		}

		key = _getch();
		switch (key)
		{
		case KEY_ESC:
		{
			exit(0);
		}
		case KEY_UP:
		{
			if (active_menu_point > 0)
			{
				active_menu_point--;
			}
		}
		break;

		case KEY_DOWN:
		{
			if (active_menu_point < vecMenu.size() - 1)
			{
				active_menu_point++;
			}
		}
		break;

		case KEY_ENTER:
		{
			return active_menu_point;
			exitVar = true;
		}
		break;
		}
	}
}

bool PrintQuit()
{
	cout << endl << endl << "Backspace - ������� � ����";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			system("cls");
			press = true;
			return press;
		}
		else
		{
			answ = _getch();
		}
	}
}