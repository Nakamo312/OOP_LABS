#pragma once
#include<string>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
#include <vector>
#include <Character/Character.h>
namespace application
{
	enum ConsoleColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};
	class Item;
	using ItemPtr = Item*;
	std::string Heroes[] = {"Рыцарь","Ассасин","Берсерк","Назад"};
	std :: string menuItems[] = { "Добавить героя в список","Симуляция боя","Выход" };
	class Item
	{
	public:
		std::string menuItem;
		int level;
		int key;
	public:
		Item();
		Item(std::string _menuItem, int _level, int _code);
		static ItemPtr createItem(std::string _menuItem, int _level, int _code);
		ItemPtr clone() const;
		int get_level() const;
		void set_menuItem(std :: string text);
	};

	class Application
	{
		ItemPtr* menuItems;
		character ::CharacterList list;
		int select;
		int level;
		int _size;
		bool _switch;
		std::vector<int> selected;
		ConsoleColor textColor;
		HANDLE hconsole;
	public:
		Application();
		Application(const Application& _menuItem);
		void insert(ItemPtr _item);
		int getSizeLevel(int level) const;
		void printMenu(int shiftX,int shiftY, int borderColor);
		ItemPtr operator[](const int index) const; 
		void input();
		int get_level()const;
		void createHero(character::Type type);
		void setcur(int x, int y);//установка курсора на позицию  x y 
		void print_heroes(int shiftX, int shiftY, int borderColor);
		void print_heroe(int shiftX, int shiftY,int index, bool full_description);
		void fight();
	};
}


