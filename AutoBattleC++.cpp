// AutoBattleC++.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
#include <iostream>
#include "BattleField.h"

int main()
{
    BattleField* battleField = new(BattleField);
    battleField->Setup();
}


