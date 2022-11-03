#include <stdio.h>
#include "Grid.h"
#include "Types.h"

Grid::Grid(int Lines, int Columns)
{
    xLenght = Lines;
    yLength = Columns;

    for (int i = 0; i < Lines; i++)
    {

        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* newBox = new Types::GridBox(i, j, false, (Columns * i + j));
            grids.insert(grids.end(), newBox);
        }
    }
}

Grid::~Grid() 
{

}

void Grid::drawBattlefield(int Lines, int Columns)
{
    for (int i = 0; i < Lines; i++)
    {
        for (int j = 0; j < Columns; j++)
        {
            Types::GridBox* currentgrid = grids[Columns * i + j]; 
            if (currentgrid->occupied)
            {
                printf("[X]\t");
            }
            else
            {
                printf("[ ]\t");
            }
        }
        printf("\n");
    }
    printf("\n");
}