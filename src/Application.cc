#include <Application/Application.h>
#include <iostream>
#include<Character/Character.h>
#include <windows.h>
using namespace application;
using namespace std;
using namespace character;
#pragma comment(lib, "characters-v1.lib")
Item::Item() : menuItem("menuItem"), level(-1), key(-1) { };

Item::Item(string _menuItem, int _level, int _code) : menuItem(_menuItem), level(_level), key(_code)
{

};

ItemPtr Item::createItem(string _menuItem, int _level, int _code)
{
	return new Item(_menuItem, _level, _code);
};
ItemPtr Item::clone() const
{
	return new Item(menuItem, level, key);
}
int Item::get_level() const
{
	return level;
}
void Item::set_menuItem(string text)
{
	menuItem = text;
}
Application::Application() : _size(0), menuItems(nullptr), select(0),level(0), hconsole(GetStdHandle(STD_OUTPUT_HANDLE)),list(CharacterList()), _switch(false)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);	
}
Application:: Application(const Application& _menuItem) : menuItems(new ItemPtr[_menuItem._size]), _size(_menuItem._size),list(CharacterList()),_switch(false)
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251);
	hconsole = GetStdHandle(STD_OUTPUT_HANDLE);
	select = 0;
	for (int i = 0; i < _size; ++i)
	{
		menuItems[i] = _menuItem[i]->clone();
	}
	list = CharacterList();
};
ItemPtr Application :: operator[](const int index) const
{
	if (index >= _size || index < 0) {
		throw runtime_error("[Application::operator[] ] invalid index");
	}
	return menuItems[index];
};
int Application::getSizeLevel(int _level) const
{
	int count = 0;
	for (int i = 0; i < _size; ++i)
	{
		if (menuItems[i]->level == _level)
		{
			count++;
		}
	}
	return count;
};
void Application::printMenu(int shiftX, int shiftY, int borderColor)
{
	SetConsoleTextAttribute(hconsole, borderColor);
	setcur(shiftX, shiftY);
	int count = 0;
	cout << "======================================" << endl;	
	for (int i = 0; i < _size; ++i)
	{		
		if (menuItems[i]->get_level() == level)
		{
			count++;
			setcur(shiftX, shiftY+count);
			cout << "||";
			if ((menuItems[i]->key == select && (menuItems[i]->menuItem == "Выход" || menuItems[i]->menuItem == "Назад"))&&!_switch)
			{
				SetConsoleTextAttribute(hconsole, 4);
			}
			else if ((menuItems[i]->key == select) && !_switch)
			{
				SetConsoleTextAttribute(hconsole, 10);
			}
			else
			{
				SetConsoleTextAttribute(hconsole, 7);
			}
			cout << setiosflags(ios::left) << setw(34) << menuItems[i]->menuItem;
			SetConsoleTextAttribute(hconsole, borderColor);
			cout << "||" << endl;
		}
	};
	count++;
	setcur(shiftX, shiftY + count);
	cout << "======================================" << endl;

}
	void Application :: insert(ItemPtr _item)
	{
		auto new_items = new ItemPtr[_size + 1];

		for (int i = 0; i < _size; ++i)
		{
			new_items[i] = menuItems[i];
		}
		new_items[_size] = _item;

		delete[] menuItems;
		menuItems = new_items;

		++_size;
	};
	void Application::setcur(int x,int y)
	{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	};
	int Application::get_level()const
	{
		return level;
	}
	void Application::input()
	{
		int code = getch();
		if (code == 72)
		{

			if (select != 0)
			{
				select--;
			}
		}
		else if (code == 80)
		{
			if (select != (getSizeLevel(level) - 1) || (_switch))
			{
				select++;

			}
		}
		else if (code == 77)
		{
			_switch = 1;
			select = 0;
			menuItems[7]->set_menuItem("Удалить героя");
		}
		else if (code == 75)
		{
			_switch = 0;
			select = 0;
			menuItems[7]->set_menuItem("Создать героя");
		}
		else if (code == 13)
		{
			if (!_switch)
			{
				int exit_code = -1;
				for (int i = 0; i < _size; ++i)
				{
					if ((menuItems[i]->menuItem == "Выход" || menuItems[i]->menuItem == "Назад") && menuItems[i]->level == level && menuItems[i]->key == select)
					{
						exit_code = menuItems[i]->key;
					}
					else if ((menuItems[i]->menuItem == "Рыцарь") && menuItems[i]->level == level && menuItems[i]->key == select)
					{
						createKnight();
						break;


					}
					else if ((menuItems[i]->menuItem == "Ассасин") && menuItems[i]->level == level && menuItems[i]->key == select)
					{
						createAssasin();
						break;

					}
					else if ((menuItems[i]->menuItem == "Берсерк") && menuItems[i]->level == level && menuItems[i]->key == select)
					{
						createBerserk();
						break;

					}
					else if ((menuItems[i]->menuItem == "Симуляция боя") && menuItems[i]->level == level && menuItems[i]->key == select)
					{
						fight();
						break;
					}
				}
				if (select == exit_code)
				{
					level--;

				}
				else
				{
					level++;
				}
			}
			else
			{
				for (int i = 0; i < list.size(); ++i)
				{
					if (select == i)
					{
						system("cls");
						print_heroe(i,0,0,1);
							
					}
				}
			}
			//select = 0;
			system("cls");
			//key = 
		}
			setcur(0, 0);
	};

	void Application::createKnight()
	{
		system("cls");
		string hero_class;
		string description;
		string abylity;
		string abylityname;
		string passabylity;
		string passabylityname;
		int color = 0;
			hero_class = "Рыцарь";
			color = DarkGray;
			description = "	Благородный воитель в сверкающих доспехах, приверженный кодексу чести.Его способности ориентированы исключительно на бой. Имеет повышенную защиту.";
			passabylityname = "Прочные доспехи:";
			abylityname = "Защитная стойка:";
			passabylity = "	(Пассивная) Вероятность 15% снизить любой получаемый урон." ;
			abylity = "	Увеличивает собственную броню, но уменьшает наносимый урон.";
			auto hero = make_shared<character::Knight>(0, 0, 0, "");

		float health;
		float armor;
		float damage;
		string name;
		std::cout << "________________________________"<<endl;
		cout << "|                              |" << endl;
		cout << "|" << "          ";
		SetConsoleTextAttribute(hconsole,color);
		cout << setw(20) << hero_class;
		SetConsoleTextAttribute(hconsole, 9);
		cout<<	 "|"<<endl;
		cout << "|                              |" << endl;
		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout <<setiosflags(ios::left) << setw(30) << "  Здоровье:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;

		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << setiosflags(ios::left) << setw(30) << "  Броня:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;

		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << setiosflags(ios::left) << setw(30) << "  Урон:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		cout << "|                              |" << endl;
		cout << "--------------------------------" << endl;

		int count = 2;
		setcur(50, count);
		SetConsoleTextAttribute(hconsole, Yellow);
		cout << "Описание: ";
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(description); ++i)
		{
			if (i % 50 == 0)
			{
				count++;
				setcur(50, count);
			}
			cout << setiosflags(ios::left) << description[i];
			
		}
		count += 2;
		setcur(50, count);
		SetConsoleTextAttribute(hconsole, Yellow);
		cout << "Способности: "<<endl;
		count++;
		setcur(55, count);
		SetConsoleTextAttribute(hconsole, LightCyan);
		cout << passabylityname;
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(passabylity); ++i)
		{
			if (i % 40 == 0 && (i != 0))
			{
				count++;
				setcur(52, count);
			}
			cout << setiosflags(ios::left) << passabylity[i];

		}
		count++;
		setcur(55, count);
		SetConsoleTextAttribute(hconsole, LightCyan);
		cout << abylityname;
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(abylity); ++i)
		{
			if (i % 40 == 0 && (i != 0))
			{
				count++;
				setcur(52, count);
			}
			cout << setiosflags(ios::left) << abylity[i];

		}
		SetConsoleTextAttribute(hconsole, 9);
		//cout << setw(10)<< hero_class << setw(10);
		count += 3;
		setcur(13, 4);
		cin >> health;
		setcur(13, 5);
		cin >> armor;
		setcur(13, 6);
		cin >> damage;
		SetConsoleTextAttribute(hconsole, LightRed);
		setcur(0, 9);		
		cout << "--------------------------------" << endl;
		cout << "|                              |" << endl;
		cout << "|                              |" << endl;
		cout << "|                              |" << endl;
		cout << "--------------------------------" << endl;
		setcur(3, 11);
		SetConsoleTextAttribute(hconsole, White);
		cout << "Введите имя: ";
		cin >> name;
		level = 2;
		select = 0;
		while (level == 2)
		{
			printMenu(30,20,Red);
			input();
		}
		level = 0;
		if (select == 0)
		{
			hero->set_armor(armor);
			hero->set_health(health);
			hero->set_damage(damage);
			hero->set_name(name);
			list.insert(hero);
			//insert(Item::createItem(name,2,list.size()-1));
		}		
	}
	void Application::createAssasin()
	{
		system("cls");
		string hero_class;
		string description;
		string abylity;
		string abylityname;
		string passabylity;
		string passabylityname;
		int color = 0;
		hero_class = "Ассасин";
		color = LightRed;
		description = "	Профессиональный убийца, владеющий навыками отравления, маскировки, скрытного перемещения и внезапных смертельных ударов.";
		passabylityname = "Неистовство ветра:";
		abylityname = "Шаг в тень:";
		passabylity = " (Пассивная) Вероятность 25% повторной атаки в этот же ход.";
		abylity = " Любая следующая атака по персонажу будет обречена на 100% промах.";
		auto hero = make_shared<character::Assasin>(0, 0, 0, "");

		float health;
		float armor;
		float damage;
		string name;
		std::cout << "________________________________" << endl;
		cout << "|                              |" << endl;
		cout << "|" << "          ";
		SetConsoleTextAttribute(hconsole, color);
		cout << setw(20) << hero_class;
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		cout << "|                              |" << endl;
		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << setiosflags(ios::left) << setw(30) << "  Здоровье:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;

		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << setiosflags(ios::left) << setw(30) << "  Броня:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;

		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << setiosflags(ios::left) << setw(30) << "  Урон:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		cout << "|                              |" << endl;
		cout << "--------------------------------" << endl;

		int count = 2;
		setcur(50, count);
		SetConsoleTextAttribute(hconsole, Yellow);
		cout << "Описание: ";
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(description); ++i)
		{
			if (i % 50 == 0)
			{
				count++;
				setcur(50, count);
			}
			cout << setiosflags(ios::left) << description[i];

		}
		count += 2;
		setcur(50, count);
		SetConsoleTextAttribute(hconsole, Yellow);
		cout << "Способности: " << endl;
		count++;
		setcur(55, count);
		SetConsoleTextAttribute(hconsole, LightCyan);
		cout << passabylityname;
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(passabylity); ++i)
		{
			if (i % 40 == 0 && (i != 0))
			{
				count++;
				setcur(52, count);
			}
			cout << setiosflags(ios::left) << passabylity[i];

		}
		count++;
		setcur(55, count);
		SetConsoleTextAttribute(hconsole, LightCyan);
		cout << abylityname;
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(abylity); ++i)
		{
			if (i % 40 == 0 && (i != 0))
			{
				count++;
				setcur(52, count);
			}
			cout << setiosflags(ios::left) << abylity[i];

		}
		SetConsoleTextAttribute(hconsole, 9);
		//cout << setw(10)<< hero_class << setw(10);
		count += 3;
		setcur(13, 4);
		cin >> health;
		setcur(13, 5);
		cin >> armor;
		setcur(13, 6);
		cin >> damage;
		SetConsoleTextAttribute(hconsole, LightRed);
		setcur(0, 9);
		cout << "--------------------------------" << endl;
		cout << "|                              |" << endl;
		cout << "|                              |" << endl;
		cout << "|                              |" << endl;
		cout << "--------------------------------" << endl;
		setcur(3, 11);
		SetConsoleTextAttribute(hconsole, White);
		cout << "Введите имя: ";
		cin >> name;
		level = 2;
		select = 0;
		while (level == 2)
		{
			printMenu(30, 20, Red);
			input();
		}
		level = 0;
		if (select == 0)
		{
			hero->set_armor(armor);
			hero->set_health(health);
			hero->set_damage(damage);
			hero->set_name(name);
			list.insert(hero);
			//insert(Item::createItem(name,2,list.size()-1));
		}
	}
	void Application::createBerserk()
	{
		system("cls");
		string hero_class;
		string description;
		string abylity;
		string abylityname;
		string passabylity;
		string passabylityname;
		int color = 0;
		hero_class = "Берсерк";
		color = Brown;
		description = "	Главные достоинства - это сила и выносливость, намного превышающие аналогичные параметры у большинства других классов. Это достойный класс для ближних боёв, способный постоять за себя. ";
		passabylityname = "Тяжелая рука";
		abylityname = "Ярость безумца";
		passabylity = "";
		abylity = "";
		auto hero = make_shared<character::Berserk>(0, 0, 0, "");

		float health;
		float armor;
		float damage;
		string name;
		std::cout << "________________________________" << endl;
		cout << "|                              |" << endl;
		cout << "|" << "          ";
		SetConsoleTextAttribute(hconsole, color);
		cout << setw(20) << hero_class;
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		cout << "|                              |" << endl;
		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << setiosflags(ios::left) << setw(30) << "  Здоровье:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;

		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << setiosflags(ios::left) << setw(30) << "  Броня:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;

		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << setiosflags(ios::left) << setw(30) << "  Урон:";
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		cout << "|                              |" << endl;
		cout << "--------------------------------" << endl;

		int count = 2;
		setcur(50, count);
		SetConsoleTextAttribute(hconsole, Yellow);
		cout << "Описание: ";
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(description); ++i)
		{
			if (i % 50 == 0)
			{
				count++;
				setcur(50, count);
			}
			cout << setiosflags(ios::left) << description[i];

		}
		count += 2;
		setcur(50, count);
		SetConsoleTextAttribute(hconsole, Yellow);
		cout << "Способности: " << endl;
		count++;
		setcur(55, count);
		SetConsoleTextAttribute(hconsole, LightCyan);
		cout << passabylityname;
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(passabylity); ++i)
		{
			if (i % 40 == 0 && (i != 0))
			{
				count++;
				setcur(52, count);
			}
			cout << setiosflags(ios::left) << passabylity[i];

		}
		count++;
		setcur(55, count);
		SetConsoleTextAttribute(hconsole, LightCyan);
		cout << abylityname;
		SetConsoleTextAttribute(hconsole, White);
		for (int i = 0; i < size(abylity); ++i)
		{
			if (i % 40 == 0 && (i != 0))
			{
				count++;
				setcur(52, count);
			}
			cout << setiosflags(ios::left) << abylity[i];

		}
		SetConsoleTextAttribute(hconsole, 9);
		//cout << setw(10)<< hero_class << setw(10);
		count += 3;
		setcur(13, 4);
		cin >> health;
		setcur(13, 5);
		cin >> armor;
		setcur(13, 6);
		cin >> damage;
		SetConsoleTextAttribute(hconsole, LightRed);
		setcur(0, 9);
		cout << "--------------------------------" << endl;
		cout << "|                              |" << endl;
		cout << "|                              |" << endl;
		cout << "|                              |" << endl;
		cout << "--------------------------------" << endl;
		setcur(3, 11);
		SetConsoleTextAttribute(hconsole, White);
		cout << "Введите имя: ";
		cin >> name;
		level = 2;
		select = 0;
		while (level == 2)
		{
			printMenu(30, 20, Red);
			input();
		}
		level = 0;
		if (select == 0)
		{
			hero->set_armor(armor);
			hero->set_health(health);
			hero->set_damage(damage);
			hero->set_name(name);
			list.insert(hero);
			//insert(Item::createItem(name,2,list.size()-1));
		}
	}
	void Application :: print_heroes(int shiftX, int shiftY, int borderColor)
	{
		SetConsoleTextAttribute(hconsole, borderColor);
		setcur(shiftX, shiftY);
		int count = 1;
		string hero_class = "";
		int color;
		cout << "======================================" << endl;
		setcur(shiftX, shiftY+count);
		cout << "||          ";
		SetConsoleTextAttribute(hconsole, White);
		cout << "Список героев";
		SetConsoleTextAttribute(hconsole, borderColor);
		cout<<"           ||" << endl;
		for (int i = 0; i <list.size(); ++i)
		{
				count++;
				setcur(shiftX, shiftY + count);
				cout << "||   ";
				if (i == select)
				{
					SetConsoleTextAttribute(hconsole, 10);
				}
				else
				{
					SetConsoleTextAttribute(hconsole, 7);
				}
				if (list[i]->equals(make_shared<character::Knight>(0,0,0,"")))
				{
					hero_class = "Рыцарь: ";
					color = DarkGray;

				}
				else if (list[i]->equals(make_shared<character::Assasin>(0, 0, 0, "")))
				{
					hero_class = "Ассасин: ";
					color = LightRed;
				}
				else if (list[i]->equals(make_shared<character::Berserk>(0, 0, 0, "")))
				{
					hero_class = "Берсерк: ";
					color = Brown;

				}
				if (_switch && (i == select))
				{
					SetConsoleTextAttribute(hconsole, White);
				}
				else
				{
					SetConsoleTextAttribute(hconsole, color);
				}
				if (selected.size() != 0)
				{
					for (int index = 0; index < selected.size(); ++index)
					{
						if ((i == selected[index]))
						{
							SetConsoleTextAttribute(hconsole, LightGreen);
						}
					}
				}
				cout << setw(31) << hero_class + list[i]->get_name();
				 
				//cout << list[i]->get_name();
				SetConsoleTextAttribute(hconsole, borderColor);
				cout << "||" << endl;
		};
		count++;
		setcur(shiftX, shiftY + count);
		cout << "||                                  ||" << endl;
		setcur(shiftX, shiftY + count+1);
		cout << "======================================" << endl;
	}

	void Application::print_heroe(int index, int shiftX, int shiftY, bool full_description)
	{
		//system("cls");
		string hero_class;
		string description;
		string abylity;
		string abylityname;
		string passabylity;
		string passabylityname;
		int color = 0;
		if (list[index]->equals(make_shared<character::Knight>(0, 0, 0, "")))
		{
			hero_class = "Рыцарь";
			color = DarkGray;
			description = "	Благородный воитель в сверкающих доспехах, приверженный кодексу чести.Его способности ориентированы исключительно на бой. Имеет повышенную защиту.";
			passabylityname = "Прочные доспехи:";
			abylityname = "Защитная стойка:";
			passabylity = "	(Пассивная) Вероятность 15% снизить любой получаемый урон.";
			abylity = "	Увеличивает собственную броню, но уменьшает наносимый урон.";


		}
		else if (list[index]->equals(make_shared<character::Assasin>(0, 0, 0, "")))
		{
			hero_class = "Ассасин";
			color = LightRed;
			description = "	Профессиональный убийца, владеющий навыками отравления, маскировки, скрытного перемещения и внезапных смертельных ударов.";
			passabylityname = "Неистовство ветра:";
			abylityname = "Шаг в тень:";
			passabylity = " (Пассивная) Вероятность 25% повторной атаки в этот же ход.";
			abylity = " Любая следующая атака по персонажу будет обречена на 100% промах.";
		}
		else if (list[index]->equals(make_shared<character::Berserk>(0, 0, 0, "")))
		{
			hero_class = "Берсерк";
			color = Brown;
			description = "	Главные достоинства - это сила и выносливость, намного превышающие аналогичные параметры у большинства других классов. Это достойный класс для ближних боёв, способный постоять за себя. ";
			
			passabylityname = "Тяжелая рука";
			abylityname = "Ярость безумца";
			passabylity = "";
			abylity = "";			
		}
		int count = 0;
		SetConsoleTextAttribute(hconsole,9);
		setcur(shiftX, shiftY+count);
		
		cout << "________________________________" << endl;
		count++;
		setcur(shiftX, shiftY + count);
		cout << "|                              |" << endl;
		count++;
		setcur(shiftX, shiftY + count);
		cout << "|" << "          ";
		SetConsoleTextAttribute(hconsole, color);
		cout << setw(20) << hero_class;
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		count++;
		setcur(shiftX, shiftY + count);
		cout << "|                              |" << endl;
		count++;
		setcur(shiftX, shiftY + count);
		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << "  Здоровье:  ";
		cout << setiosflags(ios::left) << setw(17) << static_cast <int>(list[index]->get_health());
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		count++;
		setcur(shiftX, shiftY + count);

		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << "  Броня:     ";
		cout << setiosflags(ios::left) << setw(17) << static_cast <int>(list[index]->get_armor());
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		count++;
		setcur(shiftX, shiftY + count);

		cout << "|";
		SetConsoleTextAttribute(hconsole, White);
		cout << "  Урон:      ";
		cout << setiosflags(ios::left) << setw(17) << static_cast <int> (list[index]->get_damage());
		SetConsoleTextAttribute(hconsole, 9);
		cout << "|" << endl;
		count++;
		setcur(shiftX, shiftY + count);
		cout << "|                              |" << endl;
		count++;
		setcur(shiftX, shiftY + count);
		cout << "--------------------------------" << endl;
		count++;
		setcur(shiftX, shiftY + count);
		count = 2;
		int dop_damage = list[index]->get_damage() - list[index]->get_normal_damage();
		int dop_armor = list[index]->get_armor() - list[index]->get_normal_armor();
		if (!list[index]->equals(make_shared<character::Assasin>(0, 0, 0, "")))
		{
			
			setcur(50 * index + 19, 6);
			if (dop_damage > 0 )
			{
				SetConsoleTextAttribute(hconsole, Green);
				cout << '+' << dop_damage;
			}
			else if (dop_damage < 0)
			{
				SetConsoleTextAttribute(hconsole, Red);
				cout << dop_damage;
			}
			setcur(50 * index + 19, 5);
			if (dop_armor > 0)
			{
				SetConsoleTextAttribute(hconsole, Green);
				cout << '+' << dop_armor;
			}
			else if (dop_armor < 0)
			{
				SetConsoleTextAttribute(hconsole, Red);
				cout << dop_armor;
			}
		}
		if (full_description)
		{
			
			
			setcur(50, count);
			SetConsoleTextAttribute(hconsole, Yellow);
			cout << "Описание: ";
			SetConsoleTextAttribute(hconsole, White);
			for (int i = 0; i < size(description); ++i)
			{
				if (i % 50 == 0)
				{
					count++;
					setcur(50, count);
				}
				cout << setiosflags(ios::left) << description[i];

			}
			count += 2;
			setcur(50, count);
			SetConsoleTextAttribute(hconsole, Yellow);
			cout << "Способности: " << endl;
			count++;
			setcur(55, count);
			SetConsoleTextAttribute(hconsole, LightCyan);
			cout << passabylityname;
			SetConsoleTextAttribute(hconsole, White);
			for (int i = 0; i < size(passabylity); ++i)
			{
				if (i % 40 == 0 && (i != 0))
				{
					count++;
					setcur(52, count);
				}
				cout << setiosflags(ios::left) << passabylity[i];

			}
			count++;
			setcur(55, count);
			SetConsoleTextAttribute(hconsole, LightCyan);
			cout << abylityname;
			SetConsoleTextAttribute(hconsole, White);
			for (int i = 0; i < size(abylity); ++i)
			{
				if (i % 40 == 0 && (i != 0))
				{
					count++;
					setcur(52, count);
				}
				cout << setiosflags(ios::left) << abylity[i];

			}
		}
		SetConsoleTextAttribute(hconsole, 9);
		//cout << setw(10)<< hero_class << setw(10);
		count += 3;
		SetConsoleTextAttribute(hconsole, LightRed);
		setcur(shiftX+0, shiftY+9);
		cout << "--------------------------------" << endl;
		setcur(shiftX + 0, shiftY + 10);
		cout << "|                              |" << endl;
		setcur(shiftX + 0, shiftY + 11);
		cout << "|                              |" << endl;
		setcur(shiftX + 0, shiftY + 12);
		cout << "|                              |" << endl;
		setcur(shiftX + 0, shiftY + 13);
		cout << "--------------------------------" << endl;
		setcur(3+shiftX, 11+shiftY);
		SetConsoleTextAttribute(hconsole, White);
		cout << "Имя: "<<list[index]->get_name();
		level = 2;
		select = 0;
		_switch = 0;
		if (full_description)
		{
			while (level == 2)
			{
				printMenu(30, 20, Red);
				input();
			}
			level = 0;
			if (select == 0 && menuItems[7]->menuItem == "Выбрать")
			{
				selected.push_back(index);
			}
			else if (select == 0)
			{
				list.remove(index);
			}
			select = 0;
		}
	}

	void Application::fight()
	{
		srand(time(NULL));
		selected.clear();
		_switch = 1;
		system("cls");
		while (selected.size() != 2)
		{			
			if (list.size() < 2)
			{
				setcur(0, 7);
				cout << "Должно быть минимум два героя!" << endl;
				select = 0;
				getch();
				level--;
				break;
			}
			else
			{
				menuItems[7]->set_menuItem("Выбрать");
				print_heroes(0, 0, 9);
				_switch = 1;
				input();
			}
		}
		if (selected.size() == 2)
		{
			system("cls");
			CharacterList characters;
			CharacterPtr hero1 = list[selected[0]]->clone();
			CharacterPtr hero2 = list[selected[1]]->clone();
			characters.insert(hero1);
			characters.insert(hero2);
			list = characters;
			int count = 0;
			float old_health;
			int color;
			string abylityname;
			string passabylityname1;
			string passabylityname2;

			if (list[0]->equals(make_shared<character::Knight>(0, 0, 0, "")))
			{
				passabylityname1 = "Прочные доспехи";
			}
			else if (list[0]->equals(make_shared<character::Assasin>(0, 0, 0, "")))
			{
				passabylityname1 = "Неистовство ветра";
			}
			else if (list[0]->equals(make_shared<character::Berserk>(0, 0, 0, "")))
			{
				passabylityname1 = "Тяжелая рука";
			}

			if (list[1]->equals(make_shared<character::Knight>(0, 0, 0, "")))
			{
				passabylityname2 = "Прочные доспехи";
			}
			else if (list[1]->equals(make_shared<character::Assasin>(0, 0, 0, "")))
			{
				passabylityname2 = "Неистовство ветра";
			}
			else if (list[1]->equals(make_shared<character::Berserk>(0, 0, 0, "")))
			{
				passabylityname2 = "Тяжелая рука";
			}
			while(list[0]->get_health()>0 && list[1]->get_health() > 0)
			{
				int index1 = 0;
				int index2 = 1;
				print_heroe(0, 0, 0, 0);
				print_heroe(1, 50, 0, 0);
				
				if (count % 2 == 0)
				{
					index1 = 0;
					index2 = 1;
				}
				else
				{
					index1 = 1;
					index2 = 0;
				}
				if (list[index2]->equals(make_shared<character::Knight>(0, 0, 0, "")))
				{
					color = DarkGray;
					abylityname = "Защитная стойка";
					
				}
				else if (list[index2]->equals(make_shared<character::Assasin>(0, 0, 0, "")))
				{
					color = LightRed;
					abylityname = "Шаг в тень";
					
				}
				else if (list[index2]->equals(make_shared<character::Berserk>(0, 0, 0, "")))
				{
					color = Brown;
					abylityname = "Ярость безумца";
					
				}
				old_health = list[index1]->get_health();				
				//cout << endl << endl << endl;
				setcur(50 * index2, 15);
				Sleep(1000);
				cout << "Ход игрока ";
				SetConsoleTextAttribute(hconsole,color);
				cout << list[index2]->get_name();
				SetConsoleTextAttribute(hconsole,White);
				cout<<":";
				setcur(50*index2, 16);
				Sleep(1000);
				cout << list[index2]->get_name() << " совершает действие: ";
				int chance = 1 + rand() % 100;
				if (chance <= 50)
				{
					list[index2]->Attack(*list[index1]);
					SetConsoleTextAttribute(hconsole, Red);
					cout << "Атака";
					setcur(50 * index1 + 19, 4);
					SetConsoleTextAttribute(hconsole, Red);
					Sleep(1000);
					if ((old_health - list[index1]->get_health()) == 0)
					{
						SetConsoleTextAttribute(hconsole, DarkGray);
						cout << "промах";
					}
					else
					{
						cout << '-' << old_health - list[index1]->get_health();
					}
				}
				else
				{
					list[index2]->ability();
					SetConsoleTextAttribute(hconsole, LightCyan);
					cout << abylityname;
					if (list[index2]->equals(make_shared<character::Assasin>(0, 0, 0, "")))
					{
						int dop_damage = list[index2]->get_damage() - list[index2]->get_normal_damage();
						int dop_armor = list[index2]->get_armor()  - list[index2]->get_normal_armor();
						setcur(50 * index2 + 19, 6);
						if (dop_damage > 0)
						{
							SetConsoleTextAttribute(hconsole, Green);
							cout << '+' << dop_damage;
						}
						else
						{
							SetConsoleTextAttribute(hconsole, Red);
							cout  << dop_damage;
						}
						setcur(50 * index2 + 19, 5);
						if (dop_armor > 0)
						{
							SetConsoleTextAttribute(hconsole, Green);
							cout << '+' << dop_armor;
						}
						else
						{
							SetConsoleTextAttribute(hconsole, Red);
							cout << dop_armor;
						}
						Sleep(1000);
						
					}
				}
				
				if (list[0]->get_abylity_proc())
				{

					Sleep(1000);
					setcur(0, 18);
					SetConsoleTextAttribute(hconsole, White);
					cout << "Пассивная способность: ";
					SetConsoleTextAttribute(hconsole, LightCyan);

					cout << passabylityname1;
				}

				if (list[1]->get_abylity_proc())
				{
					Sleep(1000);
					setcur(50, 18);
					SetConsoleTextAttribute(hconsole, White);
					cout << "Пассивная способность: ";
					SetConsoleTextAttribute(hconsole, LightCyan);

					cout << passabylityname2;
				}
				SetConsoleTextAttribute(hconsole, White);
				if (list[index2]->equals(make_shared<character::Assasin>(0, 0, 0, "")) && list[index2]->get_abylity_proc())
				{
					Sleep(1000);
					old_health = list[index1]->get_health();
					setcur(50 * index2, 17);
					cout << list[index2]->get_name() << " совершает бонусное действие: ";
					list[index2]->Attack(*list[index1]);
					SetConsoleTextAttribute(hconsole, Red);
					cout << "Атака";
					setcur(50 * index1 + 19, 4);
					SetConsoleTextAttribute(hconsole, Red);
					Sleep(1);
					if ((old_health - list[index1]->get_health()) == 0)
					{
						SetConsoleTextAttribute(hconsole, DarkGray);
						cout << "промах";
					}
					else
					{
						cout << '-' << old_health - list[index1]->get_health();
					}
				}

				Sleep(1000);
				count++;
				system("cls");
			}
			list = characters;
		}
		_switch = 0;
		selected.clear();
		level = 0;
		
	}