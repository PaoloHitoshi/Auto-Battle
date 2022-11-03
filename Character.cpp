#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include "Grid.h"
#include "Character.h"
#include "Types.h"

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
    printf("%f\n", amount);
	if (Health <= 0) 
	{
        Die();
        return true;
	}
	return false;
}

void Character::Die()
{
    Health = 0;
    currentBox->occupied = false;
}

void Character::WalkTo(Grid* battlefield, int Index) 
{
    currentBox->occupied = false;

    currentBox = (battlefield->grids[Index]);
    currentBox->occupied = true;

    battlefield->drawBattlefield(battlefield->xLenght, battlefield->yLength);

    return;
}

void Character::StartTurn(Grid* battlefield, list<shared_ptr<Character>> AllPlayers) 
{
    {
        if (CheckCloseTargets(battlefield, AllPlayers))
        {
            Attack();

            return;
        }
        else
        {   // if there is no target close enough, calculates in wich direction this character should move to be closer to a possible target
            int index = -1;
            string direction = "";
            if (currentBox->xIndex > target->currentBox->xIndex)
            {                
                if(!battlefield->grids[currentBox->Index - battlefield->yLength]->occupied)
                {
                    index = currentBox->Index - battlefield->yLength;
                    direction = "up";
                }
            }
            else if (currentBox->xIndex < target->currentBox->xIndex)
            {
                if(!battlefield->grids[currentBox->Index + battlefield->yLength]->occupied)
                {
                    index = currentBox->Index + battlefield->yLength;
                    direction = "down";
                }
            }
            if (currentBox->yIndex > target->currentBox->yIndex)
            {
                if(!battlefield->grids[currentBox->Index - 1]->occupied)
                {
                    index = currentBox->Index - 1;
                    direction = "left";
                }
            }
            else if (currentBox->yIndex < target->currentBox->yIndex)
            { 
                if(!battlefield->grids[currentBox->Index + 1]->occupied)
                {
                    index = currentBox->Index + 1;
                    direction = "right";
                }
            }

            if(index != -1)
            {
                cout << "Character moved " + direction + ".\n";
                WalkTo(battlefield, index);
            }

            return;
        }
    }
}

bool Character::CheckCloseTargets(Grid* battlefield, list<shared_ptr<Character>> AllPlayers)
{
    std::list<shared_ptr<Character>>::iterator it;

    float minDistance = battlefield->xLenght * battlefield->yLength;

    for (it = AllPlayers.begin(); it != AllPlayers.end(); ++it) 
    {
        if((*it)->PlayerIndex != PlayerIndex && (*it)->Health != 0)
        {
            float distance = sqrt(pow((*it)->currentBox->xIndex - currentBox->xIndex, 2) + pow((*it)->currentBox->yIndex - currentBox->yIndex, 2));

            if(distance <= minDistance)
            {
                minDistance = distance;
                target = *it;
            }
        }
    }

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
    bool wasKilled = target->TakeDamage(BaseDamage);
    printf("Player %d attacks Player %d\n", PlayerIndex, target->PlayerIndex);
    printf("New Health = %f\n", target->Health);

    if(wasKilled)
    {
        printf("Character Died!\n");
    }
}

