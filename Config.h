/* -----------------------------------------------------------------------------
FILE NAME:         Config.h
DESCRIPTION:       Class file that holds the base class "Table"
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     04-07-2021         Initial Set up
----------------------------------------------------------------------------- */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <stdlib.h>
#include "string.h"

using namespace std;

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

//Struct declarations
struct AdjacentListNode {

	char nodeName;
	char neighbor;
	int distance;
	struct AdjacentListNode *next;

};

struct AdjacentList {

	struct AdjacentListNode *headPtr;

};

struct Graph {

	int numberOfVertices;
	int numberOfEdges;
	AdjacentList *array;

};

// Class Declaration 
class Config {
     
     private:
          char algorithmName;
          int Queue_delay;
          int Propagation_delay;
          int Processing_delay;
          int Transmission_delay;
     
     public:
          void setNodal(int);
          void setQueue(int);
          void setPropagation(int);
          void setTransmission(int);
          void readConfigSmall(Graph*&);
          void readConfigLarge(Graph*&);	
          void FindPath(Graph*, char, char, vector<char>&);
          void FindPath2(Graph*, char, char, vector<char>&);	

};




#endif