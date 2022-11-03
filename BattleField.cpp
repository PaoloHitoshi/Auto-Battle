#include <iostream>
#include <list>
#include <string>
#include <algorithm>
#include "Grid.h"
#include "BattleField.h"
#include "Types.h"
#include "Character.h"
#include "BattleField.h"

using namespace std;

BattleField::BattleField() 
{
    grid = new Grid(5, 5);
    currentTurn = 0;
    numberOfPossibleTiles = grid->grids.size();
    numberOfCharacters = 2;
    numberOfPlayersAlive = numberOfCharacters;
    numberOfEnemiesAlive = numberOfCharacters;
}

void BattleField::Setup()
{
    for(int i = 0; i < numberOfCharacters; i++)
    {
        GetPlayerChoice();
    }
    StartGame();
}

void BattleField::GetPlayerChoice()
{
    //asks for the player to choose between for possible classes via console.
    printf("Choose Between One of this Classes:\n");

    printf("[1] Paladin, [2] Warrior, [3] Cleric, [4] Archer\n");
    //store the player choice in a variable
    int choice;
    
    cin >> choice;
    
    if(choice >= 1 && choice <= 4)
    {
        CreatePlayerCharacter(choice);
    }
    else
    {
        GetPlayerChoice();
    }
}

void BattleField::CreatePlayerCharacter(int classIndex)
{
    Types::CharacterClass characterClass = (Types::CharacterClass)classIndex;
    printf("Player Class Choice: {characterClass}\n");
    
    PlayerCharacter = std::make_shared<Character>(characterClass);
    
    PlayerCharacter->Health = 100;
    PlayerCharacter->BaseDamage = 20;
    PlayerCharacter->PlayerIndex = 0;

    AllPlayers.push_back(PlayerCharacter);

    CreateEnemyCharacter();
}

void BattleField::CreateEnemyCharacter()
{
    //randomly choose the enemy class and set up vital variables
    int randomInteger = GetRandomInt(1, 4);
    Types::CharacterClass enemyClass = (Types::CharacterClass)randomInteger;

    printf("Enemy Class Choice: {enemyClass}\n");

    EnemyCharacter = std::make_shared<Character>(enemyClass);
    EnemyCharacter->Health = 100;
    EnemyCharacter->BaseDamage = 20;
    EnemyCharacter->PlayerIndex = 1;

    AllPlayers.push_back(EnemyCharacter);
}

void BattleField::StartGame()
{
    AlocatePlayers();
    grid->drawBattlefield(grid->xLenght, grid->yLength);
    getchar();
    StartTurn();
}

void BattleField::StartTurn() 
{
    if (currentTurn == 0)
    {
        AllPlayers.sort();  
    }
    
    std::list<shared_ptr<Character>>::iterator it;

    for (it = AllPlayers.begin(); it != AllPlayers.end(); ++it) 
    {
        if((*it)->Health > 0)
        {
            (*it)->StartTurn(grid, AllPlayers);

            if((*it)->target->Health == 0)
            {
                if((*it)->PlayerIndex == 0)
                {
                    numberOfEnemiesAlive -= 1;
                }
                else
                {
                    numberOfPlayersAlive -= 1;
                }
            }
        }
    }

    currentTurn++;
    
    HandleTurn();
}

void BattleField::HandleTurn()
{
    if (numberOfPlayersAlive == 0)
    {
        printf("\n");
        printf("You lost!");
        printf("\n");
        return;
    }
    else if (numberOfEnemiesAlive == 0)
    {
        printf("\n");
        printf("You won!");
        printf("\n");

        return;
    }
    else
    {
        printf("\n");
        printf("Click on any key to start the next turn...\n");
        printf("\n");

        cin.get();

        StartTurn();
    }
}

int BattleField::GetRandomInt(int min, int max)
{
    int index = rand()%(max-min+1)+min;

    return index;
}

void BattleField::AlocatePlayers()
{
    for(int i = 0; i < numberOfCharacters; i++)
    {
        AlocatePlayerCharacter(2*i);
    }
}

void BattleField::AlocatePlayerCharacter(int characterIndex)
{
    int random = GetRandomInt(0, numberOfPossibleTiles);
    auto l_front = grid->grids.begin();

    advance(l_front, random);
    Types::GridBox* RandomLocation = *l_front;

    if (!RandomLocation->occupied)
    {
        PlayerCurrentLocation.push_back(*l_front);
        (*l_front)->occupied = true;

        auto l_front_player = AllPlayers.begin();
        advance(l_front_player, characterIndex);
        (**l_front_player).currentBox = *l_front;

        AlocateEnemyCharacter(characterIndex+1);
    }
    else
    {
        AlocatePlayerCharacter(characterIndex);
    }
}

void BattleField::AlocateEnemyCharacter(int characterIndex)
{
    int random = GetRandomInt(0, numberOfPossibleTiles);
    auto l_front = grid->grids.begin();

    advance(l_front, random);
    Types::GridBox* RandomLocation = *l_front;
    
    if (!RandomLocation->occupied)
    {
        EnemyCurrentLocation.push_back(*l_front);
        (*l_front)->occupied = true;

        auto l_front_player = AllPlayers.begin();
        advance(l_front_player, characterIndex);
        (**l_front_player).currentBox = *l_front;
    }
    else
    {
        AlocateEnemyCharacter(characterIndex);
    }
}