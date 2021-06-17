#include <iostream>
#include "MainMenu.h"

int main()
{
    MainMenu* mMenu = new MainMenu();
    mMenu->InitSDL();
    mMenu->CrearPantalla();
    return 0;
}