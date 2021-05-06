/* -----------------------------------------------------------------------------
FILE NAME:         Router.cpp
DESCRIPTION:       Implementation file for the Router class. 
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             
----------------------------------------------------------------------------- */
#ifndef __ROUTER_H__
#define __ROUTER_H__

#include <time.h>
#include <vector>
#include <iostream>
#include <climits>
#include <set>

using namespace std;

// Router class that contains basic information on delays
class Router
{
     private:
          // Private class variables
          int ID;
          double delayProcessing;
          double delayTransmission;
          double delayQueueing;
          double delayPropagation;
          double speedPropagation;
          double lossProbability;
          double bandwidth;
          
     public:
          // Public class variables
          vector<pair<Router*, int> > routerLinks;

          // Public class functions
          Router();
          Router(int id, double s_prop, double loss, double band);
          ~Router();
          void newLink(Router * newRouter, int length);
          double internalDelay();
          double timeOfTravel(Router * dest, int packetSize);
          int getID();
          void randomizeVariables();

          
};


#include "Router.cpp"

#endif