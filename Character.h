#pragma once
#include <memory>
#include <list>
#include "Grid.h"
#include "Types.h"

using namespace std;

class Character
{
    public:

        Character(Types::CharacterClass characterClass);
        ~Character();
  
        float Health;
        float BaseDamage;
        float DamageMultiplier;
        int PlayerIndex;
        
        shared_ptr<Character> target;

        bool IsDead;
        char Icon;

        Types::GridBox* currentBox;

        bool TakeDamage(float amount);

        int getIndex(vector<Types::GridBox*> v, int index);

        void Die();

        void WalkTo(Grid* battlefield, int Index);

        void StartTurn(Grid* battlefield, list<shared_ptr<Character>> AllPlayers);

        bool CheckCloseTargets(Grid* battlefield, list<shared_ptr<Character>> AllPlayers);

        void Attack();
};

