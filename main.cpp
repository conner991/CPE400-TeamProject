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
void function2(vector<vector<pair<int, int> > > &linkDistances, int numOfRouters);
vector<int> function3(vector<vector<pair<int, int> > > &linkDistances, vector<int> &nodePath, int origin, int destination);
void function4(vector<int> &nodePath, int &numOfPackets, int &lostPackets, double &timeFinal, double &packetLoss, char verbose);
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
     
     int origin, numOfPackets = 1, lostPackets = 0, numOfRouters = 16, randMax = 100, destination;
     double packetLoss = 0.05, timeFinal = 0;
     char input, verbose;





     cout << "---------- Dynamic Routing Simulator -----------" << endl;
     cout << "The network will be generated with " << numOfRouters << " nodes." << endl;
     cout << "Change number of packets to send? Default 1. (y/n): ";
     cin >> input;

     if (input == 'y') {
          
          cout << "Packets to send: ";
          cin >> numOfPackets;
     }

     cout << "Origin ID: ";
     cin >> origin;
     
     cout << "Destination ID: ";
     cin >> destination;

     cout << "Verbose mode? (y/n): ";
     cin >> verbose;



     for (int i = 0; i < numOfPackets; i++) {
          
          if (verbose == 'y') {
               
               cout << endl;

          }

          

          // Here the createRouters function establishes the 
          // node connections
          createRouters(numOfRouters, packetLoss);

          
          function2(linkDistances, numOfRouters);


          nodePath = function3(linkDistances, nodePath, origin, destination);


          function4(nodePath, numOfPackets, lostPackets, timeFinal, packetLoss, verbose);
          


          packetInfo.push_back(make_pair(timeFinal, lostPackets));




          // Verbose mode shows the path the packets take and tells us if 
          // any packets are lost
          if (verbose == 'y') {
               
               printPath(verbose, i, nodePath);
               cout << "Travel time: " << timeFinal << " ms" << endl;
               cout << lostPackets << " lost packet(s)" << endl;
          }

          // Reset processing and Queue delay to 0 using the class destructor
          for (int k = 0; k < networkMesh.size(); k++) {

               networkMesh[k]->~Router();

          }
               

          networkMesh.clear();
          nodePath.clear();
     }


     if (verbose == 'n') {

          printPath(verbose, numOfPackets, emptyVector);
     
     }

     
     
     
     return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
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
     networkMesh[0]->newLink(networkMesh[4], 1);
     networkMesh[1]->newLink(networkMesh[0], 1);
     networkMesh[1]->newLink(networkMesh[2], 1);
     networkMesh[1]->newLink(networkMesh[5], 1);
     networkMesh[2]->newLink(networkMesh[1], 1);
     networkMesh[2]->newLink(networkMesh[3], 1);
     networkMesh[2]->newLink(networkMesh[6], 1);
     networkMesh[3]->newLink(networkMesh[2], 1);
     networkMesh[3]->newLink(networkMesh[7], 1);
     networkMesh[4]->newLink(networkMesh[0], 1);
     networkMesh[4]->newLink(networkMesh[5], 1);
     networkMesh[4]->newLink(networkMesh[8], 1);
     networkMesh[5]->newLink(networkMesh[1], 1);
     networkMesh[5]->newLink(networkMesh[4], 1);
     networkMesh[5]->newLink(networkMesh[6], 1);
     networkMesh[5]->newLink(networkMesh[9], 1);
     networkMesh[5]->newLink(networkMesh[10], 1);
     networkMesh[6]->newLink(networkMesh[2], 1);
     networkMesh[6]->newLink(networkMesh[5], 1);
     networkMesh[6]->newLink(networkMesh[7], 1);
     networkMesh[6]->newLink(networkMesh[10], 1);
     networkMesh[7]->newLink(networkMesh[3], 1);
     networkMesh[7]->newLink(networkMesh[6], 1);
     networkMesh[7]->newLink(networkMesh[11], 1);
     networkMesh[8]->newLink(networkMesh[4], 1);
     networkMesh[8]->newLink(networkMesh[9], 1);
     networkMesh[8]->newLink(networkMesh[12], 1);
     networkMesh[9]->newLink(networkMesh[5], 1);
     networkMesh[9]->newLink(networkMesh[8], 1);
     networkMesh[9]->newLink(networkMesh[10], 1);
     networkMesh[9]->newLink(networkMesh[13], 1);
     networkMesh[10]->newLink(networkMesh[5], 1);
     networkMesh[10]->newLink(networkMesh[6], 1);
     networkMesh[10]->newLink(networkMesh[9], 1);
     networkMesh[10]->newLink(networkMesh[11], 1);
     networkMesh[10]->newLink(networkMesh[14], 1);
     networkMesh[11]->newLink(networkMesh[7], 1);
     networkMesh[11]->newLink(networkMesh[10], 1);
     networkMesh[11]->newLink(networkMesh[15], 1);
     networkMesh[12]->newLink(networkMesh[8], 1);
     networkMesh[12]->newLink(networkMesh[13], 1);
     networkMesh[13]->newLink(networkMesh[9], 1);
     networkMesh[13]->newLink(networkMesh[12], 1);
     networkMesh[13]->newLink(networkMesh[14], 1);
     networkMesh[14]->newLink(networkMesh[10], 1);
     networkMesh[14]->newLink(networkMesh[13], 1);
     networkMesh[14]->newLink(networkMesh[15], 1);
     networkMesh[15]->newLink(networkMesh[11], 1);
     networkMesh[15]->newLink(networkMesh[14], 1);


}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void function2(vector<vector<pair<int, int> > > &linkDistances, int numOfRouters) 
{
     double dDist = 0;


     for (int x = 0; x < numOfRouters; x++) {

          int totalLinks = networkMesh[x]->routerLinks.size();
          linkDistances.push_back(vector<pair<int, int> >());
          
          for (int y = 0; y < totalLinks; y++) {

               dDist = networkMesh[x]->routerLinks[y].second;
               linkDistances[x].push_back(make_pair(networkMesh[x]->routerLinks[y].first->getID(), dDist));
          }
     }


}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           vector<int>
NOTES:             
------------------------------------------------------------------------------- */
vector<int> function3(vector<vector<pair<int, int> > > &linkDistances, vector<int> &nodePath, int origin, int destination) 
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
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void function4(vector<int> &nodePath, int &numOfPackets, int &lostPackets, double &timeFinal, double &packetLoss, char verbose) 
{
     Router * parent;
     Router * child;
     
     int randProb;
     int droppedRouter = 0;
     bool lost = 0;
     double timer;
     int packetSize = 256;
     
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

                    cout << "Lost packet! From " << nodePath[droppedRouter] << " to " << nodePath[droppedRouter-1] << "." << endl;
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

          else if (numOfPackets > 1) {
               
               numOfPackets--;
               x++;
          }

          timeFinal += timer;
     }

}

/* -----------------------------------------------------------------------------
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
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
FUNCTION:          main() 
DESCRIPTION:       Controls the flow of the program at the highest level
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