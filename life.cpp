/****************************************************
Name: Matt Learned
Date: 2/27/2014
Problem Number: 3
Hours spent solving the problem: 4~ Hours
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This file provides the implementation of the life.h header file.


#include <iostream>
#include <fstream>

#include "life.h"

using namespace std;

//GLOBAL VARIABLES

struct cell ** world;
struct cell ** tempWorld; //2d array of structures to hold cell data
int ROWS;         //stores the number of rows in the grid
int COLUMNS;      //stores the number of rows in the grid


struct cell
{
	int neighbors; //cell neighbor count
	char status; //DEAD OR ALIVE

};

//This function reads input file for subsequent processing
//determines the number of rows and columns in the grid
//then records every character from the input into a matrix
void populateWorld (const char * file)
{
	    int flag = 1;//flag
		int count = 0; //counter used to determine array dimensions

		fstream fin(file, ios::in); //fstream object

		char input; //variable used for input

		while(!fin.eof()) //reads every character and counts the number of newline characters
		{
			input = fin.get();
			if(input == '\n')
			count++;
		}

		count++; //increments counter to record the last row

		ROWS = count;

		count = 0; //resets counter

		fin.clear(); //clears flags
		fin.seekg(0, ios::beg); //sets file index to the beginning

		//loop that counts the number of characters in the first row
		while(flag)
		{
			input = fin.get();

			if(input == '\n')
				flag = 0;
			else
				count++;
		}
		
		COLUMNS = count;
      

		fin.seekg(0, ios::beg); //sets file index to beginning


		createWorld();

		//reads every character into an array cell
		for(int i = 0; i < ROWS; ++i)
		{
			for(int j = 0; j < COLUMNS; ++j)
			{
				fin >> world[i][j].status;
			}
		}


}

//This function outputs the grid for current generation
//simple loop that loops through the matrix and displays
//different characters based on cellular status
void showWorld()
{

  //	for(int i = 0; i < 50; ++i)
	  //	{
	  //	cout << "\n";
		//	}

	for(int i = 0; i < ROWS; ++i)
	{
		for(int j = 0; j < COLUMNS; ++j)
		{
			if(world[i][j].status == '1') //if it's alive it'll display an 'o'
			{
				cout << 'o';
			}
			else
				cout << '.'; //else it's dead and displays a '.'
		}
		cout << endl;
	}

	return;
}

//This function creates new generation grid from the old generation grid
//it loops through every matrix cell, recording each one's neighbors
//then stores the information in a struct. How fun.
//then updates the cell status
void iterateGeneration ()
{
	//loop
	//checks every cell in the matrix and records the number of neighbors they have

	  if(cellOnBoundary())
	  {
	      expandWorld();
	  }
	  else  if(canShrink())
          {
  	      shrinkWorld();
  	  }


	for(int i = 0; i < ROWS; ++i)
	{
		for(int j = 0; j < COLUMNS; ++j)
		{
			world[i][j].neighbors = countNeighbors(i,j);
		}
	}
		//loop that updates cell status based on the set rules
		//3 neighbors create a cell
		//4 or more kill a cell
		//0 or 1 kill a cell
		//if it's living and has 2 or 3 neighbors it stays alive
		for(int i = 0; i < ROWS; ++i)
		{
			for(int j = 0; j < COLUMNS; ++j)
			{
				if(world[i][j].neighbors == 3)
					world[i][j].status = '1';
				else if(world[i][j].neighbors >= 4)
					world[i][j].status = '0';
				else if(world[i][j].neighbors <= 1)
					world[i][j].status = '0';
				else if(world[i][j].neighbors == 2 && world[i][j].status == '1')
					world[i][j].status = '1';
			}
		}



	return;
}

//This function takes a given cell
//And then calculates the correct number of neighbors
//Now featuring bound checking
int countNeighbors(int i, int j)
{


			int	neighborCount = 0;

				if(i == 0 && j == 0) //FIRST CHARACTER IN ARRAY
				{
					if(world[i][j+1].status == '1')
						neighborCount++;
					if(world[i+1][j].status == '1')
						neighborCount++;
					if(world[i+1][j+1].status == '1')
						neighborCount++;
				}
				else if(j == 0 && i == (ROWS - 1)) //1st ELEMENT
				{
					if(world[i][j+1].status == '1')
						neighborCount++;
					if(world[i-1][j].status == '1')
						neighborCount++;
					if(world[i-1][j+1].status == '1')
						neighborCount++;
				}
				else if(i == 0 && j == (COLUMNS -1)) //LAST ELEMENT FIRST ROW
				{
					if(world[i][j-1].status == '1')
						neighborCount++;
					if(world[i+1][j-1].status == '1')
						neighborCount++;
					if(world[i+1][j].status == '1')
						neighborCount++;
				}
				else if(i == (ROWS -1) && j == (COLUMNS - 1)) //LAST ELEMENT IN MATRIX
				{
					if(world[i-1][j-1].status == '1')
						neighborCount++;
					if(world[i-1][j].status == '1')
						neighborCount++;
					if(world[i][j-1].status == '1')
						neighborCount++;
				}
				else if(j == 0) //FIRST CHARACTER IN EACH ROW
				{
					if(world[i-1][j].status == '1')
						neighborCount++;
					if(world[i-1][j+1].status == '1')
						neighborCount++;
					if(world[i][j+1].status == '1')
						neighborCount++;
					if(world[i+1][j].status == '1')
						neighborCount++;
					if(world[i+1][j+1].status == '1')
						neighborCount++;
				}
				else if(i == (ROWS - 1)) //LAST ROW
				{
					if(world[i-1][j].status == '1')
						neighborCount++;
					if(world[i-1][j-1].status == '1')
						neighborCount++;
					if(world[i-1][j+1].status == '1')
						neighborCount++;
					if(world[i][j-1].status == '1')
						neighborCount++;
					if(world[i][j+1].status == '1')
						neighborCount++;
				}

				else if(j == (COLUMNS -1)) //LAST COLUMN IN EACH ROW
				{
					if(world[i-1][j].status == '1')
						neighborCount++;
					if(world[i-1][j-1].status == '1')
						neighborCount++;
					if(world[i][j-1].status == '1')
						neighborCount++;
					if(world[i+1][j-1].status == '1')
						neighborCount++;
					if(world[i+1][j].status == '1')
						neighborCount++;
				}
				else if(i == 0) //FIRST ROW
				{
					if(world[i][j-1].status == '1')
						neighborCount++;
					if(world[i][j+1].status == '1')
						neighborCount++;
					if(world[i+1][j-1].status == '1')
						neighborCount++;
					if(world[i+1][j].status == '1')
						neighborCount++;
					if(world[i+1][j+1].status == '1')
						neighborCount++;
				}
				else //EVERYTHING ELSE
				{
					if(world[i-1][j-1].status == '1')
						neighborCount++;
					if(world[i-1][j].status == '1')
						neighborCount++;
					if(world[i-1][j+1].status == '1')
						neighborCount++;
					if(world[i][j-1].status == '1')
						neighborCount++;
					if(world[i][j+1].status == '1')
						neighborCount++;
					if(world[i+1][j-1].status == '1')
						neighborCount++;
					if(world[i+1][j].status == '1')
						neighborCount++;
					if(world[i+1][j+1].status == '1')
						neighborCount++;
				}
				return neighborCount;
}

//This function checks the outer boundaries of the grid
bool cellOnBoundary()
{
	for(int i = 0; i < ROWS; ++i)
		{
			if(world[i][0].status == '1') //every row 1st column
			{
				return true;
			}
			else if(world[i][COLUMNS-1].status == '1') //every row last column
			{
				return true;
			}
		}


		for(int i = 0; i < COLUMNS; ++i)
		{
			if(world[0][i].status == '1')  //every column 1st row
			{
				return true;
			}
			else if(world[ROWS-1][i].status == '1')  //every column last row
			{
				return true;
			}
		}

		return false;
}


//This function takes the current cellular grid and resizes it
//Then moves each cell in the original grid up 1 and to the left 1
//Essentially adding a layer of padding around the cell
void expandWorld()
{

	//resizes the temporary world grid
	//adds dead cell padding to grid
	tempWorld = new cell * [ROWS + 2];

	for(int i = 0; i < ROWS+2; ++i)
	{
		tempWorld[i] = new cell[COLUMNS+2];
	}

	//shifts everything in the grid up 1 and to the left 1
	for(int i = 0; i < ROWS; ++i)
	{
		for(int j = 0; j < COLUMNS;++j)
		{
			tempWorld[i+1][j+1].status = world[i][j].status;
		}
	}

	//something about rapid cell death
	apoptosis();

	//change actual grid size
	ROWS +=2;
	COLUMNS+=2;

	//resyncs worlds
	alignWorlds();
}

//This function determines if the grid can safely shrink in size or not
bool canShrink()
{

	for(int i = 1; i < ROWS; ++i)
		{
			//checks 2nd column of each row
			if(world[i][1].status == '1')
			{
			return false;
			}
			//checks 2nd to last column of each row
			if(world[i][COLUMNS-2].status == '1')
			{
			return false;
			}
		}


		for(int i = 1; i < COLUMNS; ++i)
		{
			//checks 2nd row, each column
			if(world[1][i].status == '1')
			{
			return false;
			}
			//checks 2nd to last row, each column
			if(world[ROWS-2][i].status == '1')
			{
			return false;
			}
		}

	return true;

}

//this function attempts (and fails) to correctly shrink the grid
//it doesn't work right
//cool.
void shrinkWorld()
{
		//resizes the world
		tempWorld = new cell * [ROWS-2];

		for(int i = 0; i < ROWS-2; ++i)
		{
			tempWorld[i] = new cell[COLUMNS-2];
		}

		//shifts everything up 1 and to the left one
		for(int i = 0; i < ROWS - 2; ++i)
		{
			for(int j = 0; j < COLUMNS - 2; ++j)
			{
			tempWorld[i][j].status = world[i+1][j+1].status;
			}
		}
		//murder kill
		apoptosis();

		//changes grid size
		ROWS -=2;
		COLUMNS -= 2;

		//resyncs worlds
		alignWorlds();
}


void alignWorlds()
{
	//reconstructs world
	createWorld();

	//sets grids equal to each other
	for(int i = 0; i < ROWS; ++i)
	{
		for(int j = 0; j < COLUMNS; ++j)
		{
			world[i][j].status = tempWorld[i][j].status;
		}
	}
	//deletes the temporary grid
	for(int i = 0; i < ROWS; ++i)
	{
		delete [] tempWorld[i];
	}

	delete [] tempWorld;


}
//deletes the cell world grid
void apoptosis()
{
	for(int i = 0; i < ROWS; ++i)
		{
			delete [] world[i];
		}

		delete [] world;
}

//constructs cell world grid
void createWorld()
{
	world = new cell * [ROWS];

	for(int i = 0; i < ROWS; ++i)
	{
		world[i] = new cell[COLUMNS];
	}
}
