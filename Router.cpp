/* -----------------------------------------------------------------------------
FILE NAME:         Router.cpp
DESCRIPTION:       Implementation file for the Router class. 
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             
----------------------------------------------------------------------------- */
#ifndef __ROUTER_CPP__
#define __ROUTER_CPP__

#include "Router.h"


/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
//default constructor
Router::Router()
{
     //TODO: Change variables to better reflect timeOfTravel() variables
     ID = -1;
     delayProcessing = ((rand() % 1000) / 1000.0);
     delayTransmission = 0;
     delayQueueing = ((rand() % 1000) / 1000.0);
     delayPropagation = 0;
     speedPropagation = 200000000;
     lossProbability = 1;
     bandwidth = 1000000;
}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
//parameterized constructor
Router::Router(int id, double s_prop, double loss, double band)
{
     ID = id;
     delayProcessing = ((rand() % 1000) / 1000.0);
     delayTransmission = 0;
     delayQueueing = ((rand() % 1000) / 1000.0);
     delayPropagation = 0;
     speedPropagation = s_prop;
     lossProbability = loss;
     bandwidth = band;
}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
Router::~Router()
{
     //routerLinks.clear();
     delayProcessing = 0;
     delayQueueing = 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void Router::newLink(Router * newRouter, int length)
{
     routerLinks.push_back(make_pair(newRouter, length));
}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
double Router::internalDelay()
{
     return (delayQueueing + delayProcessing);
}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
double Router::timeOfTravel(Router * dest, int packetSize)
{    
     //Checks all links from child (passed) router
     for (int x = 0; x<routerLinks.size(); x++) {

          //Finds link chosen in nodePath
          if (routerLinks[x].first == dest) {
               //nodal + queue + trans + prop
               //Nodal: Arbitrary
               //Queueing: Congestion based
               //Transmission: packet size / bandwidth
               //Propagation: length / speed
               delayTransmission = packetSize/bandwidth;
               delayPropagation = routerLinks[x].second/speedPropagation;
               return (delayProcessing + delayQueueing + delayPropagation + delayTransmission); //Router found
          }
     }

     //Router not found
     cout << "The packet was not able to find a path to the specified router." << endl;


}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
int Router::getID()
{
     return ID;
}






#endif