/* -----------------------------------------------------------------------------
FILE NAME:         main.cpp
DESCRIPTION:       Driver file that contains main() and controls the whole program
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             
----------------------------------------------------------------------------- */
#include "Router.h"


//Globals
vector<Router*> networkMesh;
vector<pair<double, int> > packetInfo;

// Prototypes
vector<pair<int, int> > dijkstra(int startID, int dest, vector<vector<pair<int, int> > > routerLinks);
void printPath(char v, int i, vector<int> nodePath);
void createRouters(int numOfRouters, double packetLoss);
void routerDistances(vector<vector<pair<int, int> > > &linkDistances, int numOfRouters);
vector<int> findPath(vector<vector<pair<int, int> > > &linkDistances, vector<int> &nodePath, int origin, int destination);
void calcPacketLoss(vector<int> &nodePath, int numOfPackets, int &lostPackets, double &timeFinal, double &packetLoss, char verbose);
void randomizeDelay(int numOfRouters);

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
int main()
{
     //Variables
     srand(time(NULL));
     
     vector<vector<pair<int, int> > > linkDistances;
     vector<int> nodePath;
     vector<int> emptyVector;
     
     int origin, packetNum = 1, lostPackets = 0, numOfRouters = 15, randMax = 100, destination;
     double packetLoss = 0.1, timeFinal = 0;
     char input, verbose;





     cout << "---------- Dynamic Routing Simulator -----------" << endl;
     cout << "The network will be generated with " << numOfRouters << " nodes." << endl;
     cout << "Change number of packets to send? Default 1. (y/n): ";
     cin >> input;

     if (input == 'y') {
          
          cout << "Packets to send: ";
          cin >> packetNum;
     }

     // Here the createRouters function establishes the 
     // node connections
     //createRouters(numOfRouters, packetLoss);
     createRouters(numOfRouters, packetLoss);
     //for (int i = 0; i < networkMesh.size(); i++){
     //     cout << networkMesh[i]->getID() << endl;
     //}

     routerDistances(linkDistances, numOfRouters);
     /*for (int i = 0; i < linkDistances.size(); i++){
          cout << networkMesh[i]->getID() << endl;
          for (int j = 0; j < linkDistances[i].size(); j++){
               cout << linkDistances[i][j].first << ", " << linkDistances[i][j].second << endl;
          }
     }*/

     cout << "Origin ID: ";
     cin >> origin;
     
     cout << "Destination ID: ";
     cin >> destination;

     nodePath = findPath(linkDistances, nodePath, origin, destination);
     //for (int i = 0; i < nodePath.size(); i++){
     //    cout << nodePath[i] << endl;
     //}
     //cout << nodePath.size() << endl;


     cout << "Verbose mode? (y/n): ";
     cin >> verbose;

     int numOfPackets = packetNum;

     for (int i = 0; i < packetNum; i++) {
          
          randomizeDelay(numOfRouters);

          if (verbose == 'y') {
               
               cout << endl;

          }

          calcPacketLoss(nodePath, packetNum, lostPackets, timeFinal, packetLoss, verbose);

          packetInfo.push_back(make_pair(timeFinal, lostPackets));

          // Verbose mode shows the path the packets take and tells us if 
          // any packets are lost
          if (verbose == 'y') {
               
               printPath(verbose, i, nodePath);
               cout << "Travel time: " << timeFinal << " ms" << endl;
               cout << lostPackets << " lost packet(s)" << endl;
          }    
     }

     if (verbose == 'n') {
          printPath(verbose, packetNum, emptyVector);
     }

     return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          createRouters() 
DESCRIPTION:       
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void createRouters(int numOfRouters, double packetLoss) 
{
     double bandwidth = 1500;
     double dProp = 1;


     // Here all the router nodes are created and will have the 
     // same speed propogation, loss probability, and bandwidth.
     // Unique IDs are assigned for each node
     for (int x = 0; x < numOfRouters; x++) {
          
          Router *temp = new Router(x, dProp, packetLoss, bandwidth);
          networkMesh.push_back(temp);
     }

     networkMesh[0]->newLink(networkMesh[1], 1);
     networkMesh[0]->newLink(networkMesh[2], 1);
     networkMesh[0]->newLink(networkMesh[3], 1);
     networkMesh[0]->newLink(networkMesh[4], 1);
     networkMesh[0]->newLink(networkMesh[9], 4);
     networkMesh[0]->newLink(networkMesh[5], 2);
     networkMesh[1]->newLink(networkMesh[0], 1);
     networkMesh[1]->newLink(networkMesh[2], 1);
     networkMesh[1]->newLink(networkMesh[5], 2);
     networkMesh[1]->newLink(networkMesh[6], 2);
     networkMesh[2]->newLink(networkMesh[0], 1);
     networkMesh[2]->newLink(networkMesh[1], 1);
     networkMesh[2]->newLink(networkMesh[3], 1);
     networkMesh[2]->newLink(networkMesh[7], 2);
     networkMesh[3]->newLink(networkMesh[0], 1);
     networkMesh[3]->newLink(networkMesh[2], 1);
     networkMesh[3]->newLink(networkMesh[4], 2);
     networkMesh[3]->newLink(networkMesh[8], 2);
     networkMesh[4]->newLink(networkMesh[0], 1);
     networkMesh[4]->newLink(networkMesh[3], 2);
     networkMesh[4]->newLink(networkMesh[8], 3);
     networkMesh[4]->newLink(networkMesh[9], 2);
     networkMesh[5]->newLink(networkMesh[0], 2);
     networkMesh[5]->newLink(networkMesh[1], 2);
     networkMesh[5]->newLink(networkMesh[6], 3);
     networkMesh[6]->newLink(networkMesh[1], 2);
     networkMesh[6]->newLink(networkMesh[5], 3);
     networkMesh[6]->newLink(networkMesh[7], 4);
     networkMesh[6]->newLink(networkMesh[11], 1);
     networkMesh[7]->newLink(networkMesh[2], 2);
     networkMesh[7]->newLink(networkMesh[6], 4);
     networkMesh[7]->newLink(networkMesh[8], 4);
     networkMesh[7]->newLink(networkMesh[12], 1);
     networkMesh[8]->newLink(networkMesh[3], 2);
     networkMesh[8]->newLink(networkMesh[4], 3);
     networkMesh[8]->newLink(networkMesh[7], 4);
     networkMesh[8]->newLink(networkMesh[13], 1);
     networkMesh[9]->newLink(networkMesh[0], 4);
     networkMesh[9]->newLink(networkMesh[4], 2);
     networkMesh[9]->newLink(networkMesh[14], 2);
     networkMesh[10]->newLink(networkMesh[5], 2);
     networkMesh[10]->newLink(networkMesh[14], 6);
     networkMesh[11]->newLink(networkMesh[6], 1);
     networkMesh[12]->newLink(networkMesh[7], 1);
     networkMesh[13]->newLink(networkMesh[8], 1);
     networkMesh[14]->newLink(networkMesh[9], 2);
     networkMesh[14]->newLink(networkMesh[10], 6);

}

/* -----------------------------------------------------------------------------
FUNCTION:          routerDistances() 
DESCRIPTION:       
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void routerDistances(vector<vector<pair<int, int> > > &linkDistances, int numOfRouters) 
{
     double dDist = 0;


     for (int x = 0; x < numOfRouters; x++) {

          int totalLinks = networkMesh[x]->routerLinks.size();
          //cout << totalLinks << endl;
          linkDistances.push_back(vector<pair<int, int> >());

          for (int y = 0; y < totalLinks; y++) {

               dDist = networkMesh[x]->routerLinks[y].second;
               linkDistances[x].push_back(make_pair(networkMesh[x]->routerLinks[y].first->getID(), dDist));
          }
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          findPath() 
DESCRIPTION:       
RETURNS:           vector<int>
NOTES:             
------------------------------------------------------------------------------- */
vector<int> findPath(vector<vector<pair<int, int> > > &linkDistances, vector<int> &nodePath, int origin, int destination) 
{
     
     vector<pair<int, int> > pathInfo = dijkstra(origin, destination, linkDistances);
     
     int prevRouter = pathInfo[destination].second;
     
     nodePath.push_back(destination);
     nodePath.push_back(prevRouter);

     while (prevRouter != -1) {

          prevRouter = pathInfo[prevRouter].second;
          nodePath.push_back(prevRouter);
     }
     return nodePath;
}

/* -----------------------------------------------------------------------------
FUNCTION:          calcPacketLoss() 
DESCRIPTION:       
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void calcPacketLoss(vector<int> &nodePath, int numOfPackets, int &lostPackets, double &timeFinal, double &packetLoss, char verbose) 
{
     Router * parent;
     Router * child;
          
     int randProb;
     int droppedRouter = 0;
     int droppedRouterRollover = 0;
     bool lost = 0;
     double timer = 0;
     int packetSize = 256;
     lostPackets = 0;
     timeFinal = 0.0;
          
     for (int x = nodePath.size() - 2; x > 0; x--) {
          randProb = (rand() % 101);
          
          if (randProb < packetLoss * 100) {
               
               if (numOfPackets == 1) {

                    droppedRouter = x;
               }

               else {

                    droppedRouter = rand() % (nodePath.size() - 2);
               }
          
               if (verbose == 'y') {
                    if (0 > droppedRouter-1) {
                         cout << "Lost packet! From " << nodePath[droppedRouter+1] << " to " << nodePath[droppedRouter] << "." << endl;
                    }
                    else {
                         cout << "Lost packet! From " << nodePath[droppedRouter] << " to " << nodePath[droppedRouter-1] << "." << endl;
                    }
               }
               
               lost = 1;
          }

          parent = networkMesh[nodePath[x]];
          child = networkMesh[nodePath[x-1]];
          timer = parent->timeOfTravel(child, packetSize);
          
          if (lost) {
               x++;
               lostPackets++;
               lost = 0;
          }

          timeFinal += timer;
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          randomizeDelay() 
DESCRIPTION:       
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void randomizeDelay(int numOfRouters) 
{
     for (int i = 0; i < numOfRouters; i++) {
          networkMesh[i]->randomizeVariables();
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          dijkstra() 
DESCRIPTION:       
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
vector<pair<int, int> > dijkstra(int startID, int destination, vector<vector<pair<int, int> > > routerLinks)
{
     set<pair<int, int> > finalRoute;
     vector<pair<int, int> > minDistance;
     vector<pair<int, int> > delays;



     for (int x = 0; x < routerLinks.size(); x++) {

          minDistance.push_back(make_pair(INT_MAX, -1));
          delays.push_back(make_pair(INT_MAX, -1));
     }

     minDistance[startID].first = 0;
     delays[startID].first = networkMesh[startID]->internalDelay();
     finalRoute.insert(make_pair(0, startID));

     //Evaluating travel times
     while (!finalRoute.empty()) {

          int location = finalRoute.begin()->second;

          if (location == destination) {

               return minDistance;
          }
          
          finalRoute.erase(finalRoute.begin());

          for (auto z : routerLinks[location]) {

               //Better path found
               if ((minDistance[z.first].first > minDistance[location].first + z.second) || (delays[z.first].first > delays[location].first + networkMesh[z.first]->internalDelay()))  {

                    finalRoute.erase(make_pair(minDistance[z.first].first, z.first));
                    minDistance[z.first].first = minDistance[location].first + z.second;
                    minDistance[z.first].second = location;
                    delays[z.first].first = delays[location].first + networkMesh[z.first]->internalDelay();
                    delays[z.first].second = location;
                    finalRoute.insert(make_pair(minDistance[z.first].first, z.first));
               }
          }
     }


     return minDistance;
}

/* -----------------------------------------------------------------------------
FUNCTION:          printPath() 
DESCRIPTION:       
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void printPath(char verbose, int numOfPackets, vector<int> nodePath)
{
     if (verbose == 'y') {

          cout << nodePath[nodePath.size() - 2];

          for (int x = nodePath.size() - 3; x >= 0; x--) {

               cout << " -> " << nodePath[x];
          }

          cout << endl;
     }

     else {
          
          cout.precision(5);
          cout << "#\tTime\t\tLost  " << endl << "----------------------------" << endl;
                    
          
          for (int x = 0; x < numOfPackets; x++) {
               cout << x + 1 << "\t" << packetInfo[x].first << "\t\t" << packetInfo[x].second << endl;
          }
     }
}