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


     //Program header, gives instruction to user about packets and node number
     cout << "---------- Routing Simulator -----------" << endl;
     cout << "The network has " << numOfRouters << " nodes (routers)." << endl;
     cout << "Specify number of packets to send: ";

     // Error handling for user input on number of packets
     try {
          cin >> packetNum;
          if (packetNum > 0) {
          }
          else {
               throw "Invalid number of packets.  Defaulting to 1";
          }
     }
     catch(const char* msg) {
          cerr << msg << endl;
          packetNum = 1;
     }

     // Here the createRouters function establishes the 
     // node connections
     // numOfRouters is the amount of routers in the network
     // packetLoss is the const variable determining the chance of a packet being lost
     createRouters(numOfRouters, packetLoss);
     
     // routerDistances function applies distance values to each of the router links
     // linkDistances is a vector of vector pairs that specifies the link distances between each router ID
     routerDistances(linkDistances, numOfRouters);

     // receive Source router and destination router from user
     cout << "Origin ID (starts at 0): ";
     // Error handling for user inputs of router ID's
     try {
          cin >> origin;
          if (origin >= 0 && origin < numOfRouters) {
          }
          else {
               throw "Invalid Router ID.  Defaulting to Router 0";
          }
     }
     catch(const char* msg) {
          cerr << msg << endl;
          origin = 0;
     }
     
     cout << "Destination ID (ends at " << numOfRouters-1 << "): ";
     // Error handling for user inputs of router ID's
     try {
          cin >> destination;
          if (origin == destination) {
               throw (true);
          }
          else if (destination >= 0 && destination < numOfRouters) {
          }
          else {
               throw "Invalid Router ID.  Defaulting to Router 14";
          }
     }
     catch(const char* msg) {
          cerr << msg << endl;
          destination = 14;
     }
     catch(bool value){
          cerr << "Same Router given as Source and Destination" << endl;
          cerr << "Source set to 0, Destination set to 14" << endl;
          origin = 0;
          destination = 14;
     }

     // findPath is the function that determines the shortest viable path from source to destination
     // algorithm utilizes Djikstra for node comparisons
     // nodePath variable is a vector containing nodes used in path solution
     // origin is origin node
     // destination is destination node
     nodePath = findPath(linkDistances, nodePath, origin, destination);

     // Determine from user if program should show additional info
     cout << "Show path information and packet loss locations? (y/n): ";
     // Error handling
     try {
          cin >> verbose;
          if (verbose == 'y' || verbose == 'n') {
          }
          else {
               throw "Invalid input. Defaulting to 'n'";
          }
     }
     catch(const char* msg) {
          cerr << msg << endl;
          verbose = 'n';
     }

     // variable to be manipulated later without modifying max packet amount
     int numOfPackets = packetNum;

     // The main for loop
     // iterates an amount equivalent to the user provided packet amount to be sent
     // at each iteration determines if a packet is lost, where it's lost, and time to travel
     for (int i = 0; i < packetNum; i++) {
          
          // function to randomize the queue delay and processing delay at each router
          randomizeDelay(numOfRouters);

          if (verbose == 'y') {
               
               cout << endl;

          }

          // function to calculate the packet loss at each loop iteration
          // lostPackets is a variable that returns the amount of packets lost through full path traversal
          // timeFinal returns the total amount of time a packet took from src to dest
          // packetLoss is the base probability for a packet to be lost
          // verbose is whether the user requested more info
          calcPacketLoss(nodePath, packetNum, lostPackets, timeFinal, packetLoss, verbose);

          packetInfo.push_back(make_pair(timeFinal, lostPackets));

          // Outputs more information to the user
          if (verbose == 'y') {
               
               printPath(verbose, i, nodePath);
               cout << "Travel time: " << timeFinal << " ms" << endl;
               cout << lostPackets << " lost packet(s)" << endl;
          }    
     }

     // Print statement to let user know some information about packets
     if (verbose == 'n') {
          printPath(verbose, packetNum, emptyVector);
     }

     return 0;
}

/* -----------------------------------------------------------------------------
FUNCTION:          createRouters() 
DESCRIPTION:       creates the router networkMesh vector
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

     // Full networkLink graph generation
     // leftmost networkMesh determines origin node
     // newLink determines which node it goes to, and the second int is the distance between the two nodes
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
DESCRIPTION:       Applies the given distances to a linkDistance vector that maintains the information moving forward
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void routerDistances(vector<vector<pair<int, int> > > &linkDistances, int numOfRouters) 
{
     // initial distance variable
     double dDist = 0;

     // For loop to iterate through all networkMesh class objects and pull the distance values
     for (int x = 0; x < numOfRouters; x++) {

          // Provides total number of links between nodes
          int totalLinks = networkMesh[x]->routerLinks.size();
          linkDistances.push_back(vector<pair<int, int> >());

          // Second for loop that applies link distances
          for (int y = 0; y < totalLinks; y++) {

               dDist = networkMesh[x]->routerLinks[y].second;
               linkDistances[x].push_back(make_pair(networkMesh[x]->routerLinks[y].first->getID(), dDist));
          }
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          findPath() 
DESCRIPTION:       Uses Djikstra to find the shortest path between source and destination nodes
RETURNS:           vector<int>
NOTES:             
------------------------------------------------------------------------------- */
vector<int> findPath(vector<vector<pair<int, int> > > &linkDistances, vector<int> &nodePath, int origin, int destination) 
{
     // Maintains Djikstra path information
     vector<pair<int, int> > pathInfo = dijkstra(origin, destination, linkDistances);
     
     // Keeps previous router record to apply to path Info for source and destination management
     int prevRouter = pathInfo[destination].second;
     
     nodePath.push_back(destination);
     nodePath.push_back(prevRouter);

     // Iterate until no more nodes to move to
     while (prevRouter != -1) {

          prevRouter = pathInfo[prevRouter].second;
          nodePath.push_back(prevRouter);
     }

     // returns the updated nodePath vector
     return nodePath;
}

/* -----------------------------------------------------------------------------
FUNCTION:          calcPacketLoss() 
DESCRIPTION:       Function that takes a number of variables to calculate whether packets are lost, where they are lost, and the time it takes
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void calcPacketLoss(vector<int> &nodePath, int numOfPackets, int &lostPackets, double &timeFinal, double &packetLoss, char verbose) 
{
     Router * parent;
     Router * child;

     // variables that need to be reset on each new function call
     int randProb;
     int droppedRouter = 0;
     int droppedRouterRollover = 0;
     bool lost = 0;
     double timer = 0;
     int packetSize = 256;
     lostPackets = 0;
     timeFinal = 0.0;
          
     // for loop that iterates through nodePath
     for (int x = nodePath.size() - 2; x > 0; x--) {
          
          // initial random chance to determine if a packet will be lost
          randProb = (rand() % 101);
          
          // if checks for situations where packet is lost, and when a packet is not lost
          if (randProb < packetLoss * 100) {
               
               // Base case
               if (numOfPackets == 1) {

                    droppedRouter = x;
               }

               // If a packet is lost, randomly choose a router to have 'dropped' the packet
               else {

                    droppedRouter = rand() % (nodePath.size() - 2);
               }
          
               // If user requested more information
               if (verbose == 'y') {
                    // Covers an exception for when a src and dest node are right next to each other.  Prevents code from outputting a -1 indexed node
                    if (0 > droppedRouter-1) {
                         cout << "Lost packet! From " << nodePath[droppedRouter+1] << " to " << nodePath[droppedRouter] << "." << endl;
                    }
                    // All other situations
                    else {
                         cout << "Lost packet! From " << nodePath[droppedRouter] << " to " << nodePath[droppedRouter-1] << "." << endl;
                    }
               }
               
               lost = 1;
          }

          // Calculates the time it takes for a packet to go from one node to the next
          parent = networkMesh[nodePath[x]];
          child = networkMesh[nodePath[x-1]];
          timer = parent->timeOfTravel(child, packetSize);
          
          // if a packet is lost, try to resend and iterate through again
          if (lost) {
               x++;
               lostPackets++;
               lost = 0;
          }

          // return the final time it took for a node to traverse from src to dest
          timeFinal += timer;
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          randomizeDelay() 
DESCRIPTION:       Rerandomizes the queue and processing delays in each router
RETURNS:           Nothing
NOTES:             
------------------------------------------------------------------------------- */
void randomizeDelay(int numOfRouters) 
{
     // loop to iterate through networkMesh and randomize variables
     for (int i = 0; i < numOfRouters; i++) {
          networkMesh[i]->randomizeVariables();
     }
}

/* -----------------------------------------------------------------------------
FUNCTION:          dijkstra() 
DESCRIPTION:       standard dijkstra algorithm
RETURNS:           vector<pair<int, int>>
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
DESCRIPTION:       terminal print out statements to provide user with information
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