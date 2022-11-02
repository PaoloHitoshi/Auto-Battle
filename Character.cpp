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
	if ((Health -= BaseDamage) <= 0) 
	{
		Die();
		return true;
	}
	return false;
}

void Character::Die() 
{
	// TODO >> kill
	//TODO >> end the game?
}

void Character::WalkTo(bool CanWalk) 
{

}

void Character::StartTurn(Grid* battlefield) 
{
    {
        if (CheckCloseTargets(battlefield))
        {
            Attack(Character::target);

            return;
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
            
            if (currentBox->xIndex > target->currentBox->xIndex)
            {
                
                if(find(battlefield->grids.begin(), battlefield->grids.end(), currentBox) != battlefield->grids.end())
                {
                    currentBox->occupied = false;
                    battlefield->grids[currentBox->Index] = currentBox;

                    currentBox = (battlefield->grids[currentBox->Index - 1]);
                    currentBox->occupied = true;
                    battlefield->grids[currentBox->Index] = currentBox;
                    //Console.WriteLine($"Player {PlayerIndex} walked left\n");

                    battlefield->drawBattlefield(5, 5);

                    return;
                }
            }
            
            else if (currentBox->xIndex < target->currentBox->xIndex)
            {
                currentBox->occupied = false;
                battlefield->grids[currentBox->Index] = currentBox;
                currentBox = (battlefield->grids[currentBox->Index + 1]);
                return;

                battlefield->grids[currentBox->Index] = currentBox;
                //Console.WriteLine($"Player {PlayerIndex} walked right\n");
                battlefield->drawBattlefield(5, 5);
            }
            if (currentBox->yIndex > target->currentBox->yIndex)
            {
                battlefield->drawBattlefield(5, 5);
                currentBox->occupied = false;
                battlefield->grids[currentBox->Index] = currentBox;

                currentBox = battlefield->grids[(currentBox->Index - battlefield->xLenght)];
                currentBox->occupied = true;
                battlefield->grids[currentBox->Index] = currentBox;
                //Console.WriteLine($"PlayerB {PlayerIndex} walked up\n");

                return;
            }
            else if (currentBox->yIndex < target->currentBox->yIndex)
            { 
                currentBox->occupied = true;
                battlefield->grids[currentBox->Index] = currentBox;
                currentBox = battlefield->grids[currentBox->Index + battlefield->xLenght];

                currentBox->occupied = false;
                battlefield->grids[currentBox->Index] = currentBox;
                //Console.WriteLine($"Player {PlayerIndex} walked down\n");

                battlefield->drawBattlefield(5, 5);

                return;
            }
        }
    }
}

bool Character::CheckCloseTargets(Grid* battlefield)
{
    return false;
}

void Character::Attack(shared_ptr<Character> target) 
{

}

