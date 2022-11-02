#pragma once
#include <memory>
#include "Grid.h"
#include "Character.h"
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
        //public GridBox currentBox;
        int PlayerIndex;
        //public Character Target{ get; set; }

        shared_ptr<Character> target;

        bool IsDead;
        char Icon;

        Types::GridBox* currentBox;

        bool TakeDamage(float amount);

        int getIndex(vector<Types::GridBox*> v, int index);

        void Die();

        void WalkTo(Grid* battlefield, int Index);

        void StartTurn(Grid* battlefield);

        bool CheckCloseTargets(Grid* battlefield);

        void Attack();
};

