#include <iostream>
#include <Application/Application.h>
#include<string>
#include <windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>
using namespace application;

using namespace std;

int main()
{
	Application app = Application();
	app.insert(Item::createItem(menuItems[0], 0, 0));
	app.insert(Item::createItem(menuItems[1], 0, 1));
	app.insert(Item::createItem(menuItems[2], 0, 2));
	app.insert(Item::createItem(Heroes[0], 1, 0));
	app.insert(Item::createItem(Heroes[1], 1, 1));
	app.insert(Item::createItem(Heroes[2], 1, 2));
	app.insert(Item::createItem(Heroes[3], 1, 3));
	app.insert(Item::createItem("Создать героя", 2, 0));
	app.insert(Item::createItem("Назад", 2, 1));
	while(app.get_level()!=-1)
	{
		app.printMenu(0,0,9);
		if (app.get_level() == 0)
		{
			app.print_heroes(50, 0, Red);
		}
		app.input();
	}
	
	return 0;
}