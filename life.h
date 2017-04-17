/****************************************************
Name: Matt Learned
Date: 2/27/14
Problem Number: 3
CS2308
Instructor: Komogortsev, TSU
*****************************************************/

//This header file provides the prototypes of the function definitions
//for the project.

#ifndef life_h
#define life_h

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void populateWorld(const char * file);
void showWorld();
void iterateGeneration();
int countNeighbors(int, int);
bool cellOnBoundary();
void shrinkWorld();
bool canShrink();
void createWorld();
void apoptosis();
void alignWorlds();
void expandWorld();

#endif
