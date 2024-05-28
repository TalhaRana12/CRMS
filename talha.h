#ifndef TALHA_H
#define TALHA_H
#include <iostream>
#include <windows.h>
#include <conio.h>
#include<iomanip>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);




void arrow_control(int up, int low, char key, int& selected)
{

    /**
     * @brief Handles arrow key controls for navigating menus.
     *
     * @param up The upper bound of the menu options.
     * @param low The lower bound of the menu options.
     * @param key The pressed arrow key.
     * @param selected The currently selected menu option (updated by reference).
     * @return The updated selected menu option.
     */
    switch (key)
    {
    case 72:
        if (selected != low)
            selected--;
        else if (selected == low)
            selected = up;
        break;
    case 80:
        if (selected != up)
            selected++;
        else if (selected == up)
            selected = low;
    }
    return;
}
void printmenu(string line, int selected, int x, int colour_selected, int colour_unselected)
{

    /**
     * @brief Prints a menu option with appropriate coloring.
     *
     * @param line The menu option text.
     * @param selected The currently selected menu option.
     * @param x The position of the menu option.
     * @param colour_selected The color for the selected menu option.
     * @param colour_unselected The color for unselected menu options.
     */
    if (selected == x)
    {
        SetConsoleTextAttribute(h, colour_selected);
        cout << line << endl;
    }
    else
    {
        SetConsoleTextAttribute(h, colour_unselected);
        cout << line << endl;
    }
}

int complete_menu(string arr[], int size, int colour = 13, int colour2 = 15)
{ /**
   * @brief Displays an interactive menu and handles user input.
   *
   * @param arr An array of menu options.
   * @param size The size of the menu options array.
   * @param colour The default color for menu options.
   * @param colour2 The color for the selected menu option.
   * @return The selected menu option.
   */
    char key;
    int selected = 1;
    do
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n";
        cout <<setw(100)<< "***********************************************************\n";
        cout<<setw(100) << "************** TR Car Rental Management System ************\n";
        cout <<setw(100)<< "***********************************************************\n";
        cout << "\n";
        for (int i = 0; i < size; i++)
            printmenu(arr[i], selected, i + 1, colour, colour2);
        key = _getch();
        if (key == 13)
        {
            SetConsoleTextAttribute(h, 15);
            return selected;
        }
        if (key != 13)
            arrow_control(size, 1, key, selected);
    } while (key != 27);
    SetConsoleTextAttribute(h, 15);
    return -1;
}
#endif

