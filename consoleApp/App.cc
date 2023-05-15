#include <Character/Character.h>
#include <string>
#include <iostream>
using namespace character;
using namespace std;

void printMenu();
CharacterPtr createHero();


void printMenu()
{
	cout << "======================================" << endl;
	cout << "|| 1 - добавить героя в список      ||"<<endl;
	cout << "|| 2 - удалить героя из списка      ||" << endl;
	cout << "|| 3 - вывести список героев        ||" << endl;
	cout << "======================================" << endl;
}


int main()
{
	string answer = "";

	while (answer != "off")
	{
		printMenu();
		cin >> answer;

		if (answer == "1")
		{
			//CharacterPtr h = createHero();
		}
		else if (answer == "2")
		{

		}
	}
	return 0;
}