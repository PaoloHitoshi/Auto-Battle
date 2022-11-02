#include <vector>
#include <algorithm>
#include "Grid.h"
#include "Character.h"
#include "Types.h"
#include "Character.h"

using namespace std;

Character::Character(Types::CharacterClass characterClass)
{

}

Character::~Character() 
{

}

bool Character::TakeDamage(float amount) 
{
    Health -= amount;
	if (Health <= 0) 
	{
        Health = 0;
		return true;
	}
	return false;
}

void Character::WalkTo(Grid* battlefield, int Index) 
{
    currentBox->occupied = false;

    currentBox = (battlefield->grids[Index]);
    currentBox->occupied = true;

    battlefield->drawBattlefield(5, 5);

    return;
}

void Character::StartTurn(Grid* battlefield) 
{
    {
        if (CheckCloseTargets(battlefield))
        {
            Attack();

            return;
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
            if (currentBox->xIndex > target->currentBox->xIndex)
            {                
                WalkTo(battlefield, currentBox->Index - battlefield->yLength);
                return;
            }
            else if (currentBox->xIndex < target->currentBox->xIndex)
            {
                WalkTo(battlefield, currentBox->Index + battlefield->yLength);
                return;
            }
            if (currentBox->yIndex > target->currentBox->yIndex)
            {
                WalkTo(battlefield, currentBox->Index - 1);
                return;
            }
            else if (currentBox->yIndex < target->currentBox->yIndex)
            { 
                WalkTo(battlefield, currentBox->Index + 1);
                return;
            }
        }
    }
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
    if(currentBox->xIndex == target->currentBox->xIndex)
    {
        if(currentBox->yIndex == target->currentBox->yIndex - 1 || currentBox->yIndex == target->currentBox->yIndex + 1)
        {
            return true;
        }
    }

    if(currentBox->yIndex == target->currentBox->yIndex)
    {
        if(currentBox->xIndex == target->currentBox->xIndex - 1 || currentBox->xIndex == target->currentBox->xIndex + 1)
        {
            return true;
        }
    }

    return false;
}

void Character::Attack() 
{
    target->TakeDamage(BaseDamage);
}

