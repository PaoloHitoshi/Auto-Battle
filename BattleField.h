#pragma once
#include <list>
#include <iostream>
#include <memory>
#include "Character.h"
#include "Types.h"
#include "Grid.h"

using namespace std;

class BattleField
{
	public:

		BattleField();

		Grid* grid;
		list<Types::GridBox*> PlayerCurrentLocation;
		list<Types::GridBox*> EnemyCurrentLocation;
		list<shared_ptr<Character>> AllPlayers;
		shared_ptr<Character> PlayerCharacter;
		shared_ptr<Character> EnemyCharacter;

		int currentTurn;
		int numberOfPossibleTiles;
		int numberOfCharacters;
		int numberOfPlayersAlive;
		int numberOfEnemiesAlive;
		
		void Setup();

		void GetPlayerChoice();

		void CreatePlayerCharacter(int classIndex);

		void CreateEnemyCharacter();

		void StartGame();

		void StartTurn();

		void HandleTurn();

		int GetRandomInt(int min, int max);

		void AlocatePlayers();

		void AlocatePlayerCharacter(int characterIndex);

		void AlocateEnemyCharacter(int characterIndex);
};


