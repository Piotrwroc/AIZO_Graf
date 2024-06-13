#include "Menu.h"
#include "Menu_Settings.h"

#include <iostream>
#include <cstdlib>

using namespace std;

void Menu::f_menu()
{
    bool x = true;
    while (x)
    {
        //system("cls");
        int wybor_typu = 0;
        cout << "Autorem programu jest Piotr Jozefek 272311" << endl;
        cout << "Wybierz problem: " << endl;
        cout << "1. Wyznaczanie minimalnego drzewa rozpinajacego (MST) " << endl;
        cout << "2. Wyznaczanie najkrotszej sciezki w grafie" << endl;
        cout << "3. Wylaczenie programu" << endl;
        cout << endl;
        cin >> wybor_typu;


        switch (wybor_typu)
        {
        case 1:
        {   
            Menu_Settings menu_settings;
            menu_settings.f_menu_settings(1);
            break;
        }

        case 2:
        {
            Menu_Settings menu_settings;
            menu_settings.f_menu_settings(2);
            break;
        }

        case 3:
        {
            cout << "Zakonczono dzialanie programu" << endl;
            exit(0);
            break;
        }

        default:
        {
            cout << "Wybrano niepoprawna opcje" << endl;
            break;
        }
        }
    }
}