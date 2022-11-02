#pragma once

class Types
{
    public:

        struct GridBox
        {
            int xIndex;
            int yIndex;
            bool occupied;
            int Index;

            GridBox(int x, int y, bool occupied, int index)
            {
                xIndex = x;
                yIndex = y;
                occupied = occupied;
                Index = index;
            }
        };

        enum CharacterClass
        {
            Paladin = 1,
            Warrior = 2,
            Cleric = 3,
            Archer = 4
        };
};

