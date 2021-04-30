/* -----------------------------------------------------------------------------
FILE NAME:         Table.h
DESCRIPTION:       Class file that holds the base class "Table"
USAGE:             
COMPILER:          GNU g++ compiler on Linux
NOTES:             

MODIFICATION HISTORY:
Author             Date               Version
---------------    ----------         --------------
Conner Fissell     04-07-2021         Initial Set up
----------------------------------------------------------------------------- */
#include "Config.h"




//Function declarations
AdjacentListNode* nameAdjacentListNode(char);
AdjacentListNode* newAdjacentListNode(char, int);
Graph* createGraph(int);
void wait(int msec);
float diffclock(clock_t, clock_t);
void addEdge(struct Graph*&, char, char, int);
void printGraph(struct Graph*);
void bellmanFord(Graph*, char);
void printBellmanFord(int[], char[], int);
void slowDijkstra(Graph*, char, char, vector<char>&);
void fastDijkstra(Graph*, char, char, vector<char>&);


/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
int main(){

	Config Save;
	Graph* smallGraph;
	Graph* largeGraph;
	Save.readConfigSmall(smallGraph);
     Save.readConfigLarge(largeGraph);

     printGraph(smallGraph);

     float total = 0;
     int size = smallGraph->numberOfVertices;
     vector<char> order;
     






     cout << endl << endl;
     cout << "--------------------------------------------------------------" << endl;
     cout << "Comparing original Dijkstra with Bellman-Ford (small network):" << endl;

     for (int i = 0; i < 100; ++i) {
	    
         clock_t start1=clock();
	    slowDijkstra(smallGraph, 'u', 'z', order);
	    clock_t end1=clock();
	    float time = diffclock(end1, start1);
	    total += time;
     }

     float average = total/100;
     cout << "Average Dijkstra runtime: " << average << endl;
     total = 0;
     
     for (int i = 0; i < 100; ++i)
     {
          clock_t start2=clock();
          bellmanFord(smallGraph, smallGraph->array[0].headPtr->nodeName);
          clock_t end2=clock();
          float time = diffclock(end2, start2);
          total += time;
     }

     average = total/100;
     cout << "Average Bellman-Ford runtime: " << average << endl;  
     cout << "--------------------------------------------------------------" << endl;  
     
     // Reset Total
     total = 0;

     // Reset order vector
     order.clear();   




     cout << "--------------------------------------------------------------" << endl;
     cout << "Comparing original Dijkstra with Bellman-Ford (large network):" << endl;

     for (int i = 0; i < 100; ++i)
     {
          clock_t start1=clock();
          slowDijkstra(largeGraph, 'a', 'z', order);
          clock_t end1=clock();
          float time = diffclock(end1, start1);
          total += time;
     }

          average = total/100;
     cout << "Average Dijkstra runtime: " << average << endl;
     total = 0;
     
     for (int i = 0; i < 100; ++i)
     {
          clock_t start2=clock();
          bellmanFord(largeGraph, largeGraph->array[0].headPtr->nodeName);
          clock_t end2=clock();
          float time = diffclock(end2, start2);
          total += time;
     }

     average = total/100;
     cout << "Average Bellman-Ford runtime: " << average << endl;    
     cout << "--------------------------------------------------------------" << endl;
     
     // Reset Total
     total = 0;

     // Reset order vector
     order.clear();    

    

     cout << "-------------------------------------------------------------------" << endl;
     cout << "Comparing original Dijkstra with improved Dijkstra (small network):" << endl;

     for (int i = 0; i < 100; ++i)
     {
          clock_t start1=clock();
          slowDijkstra(smallGraph, 'u', 'z', order);
          clock_t end1=clock();
          float time = diffclock(end1, start1);
          total += time;
     }

     average = total/100;
     cout << "Average original Dijkstra runtime: " << average << endl;
     total = 0;

     order.clear();    

     for (int i = 0; i < 100; ++i)
     {
          clock_t start1=clock();
          fastDijkstra(smallGraph, 'u', 'z', order);
          clock_t end1=clock();
          float time = diffclock(end1, start1);
          total += time;
     }        

     average = total/100;
     cout << "Average improved Dijkstra runtime: " << average << endl;
     cout << "----------------------------------------------------------------" << endl;

     // Reset Total
     total = 0;

     // Reset order vector
     order.clear();  




     
     

     cout << "-------------------------------------------------------------------" << endl;
     cout << "Comparing original Dijkstra with improved Dijkstra (large network):" << endl;

     for (int i = 0; i < 100; ++i)
     {
          clock_t start1=clock();
          slowDijkstra(largeGraph, 'a', 'z', order);
          clock_t end1=clock();
          float time = diffclock(end1, start1);
          total += time;
     }

     average = total/100;
     cout << "Average original Dijkstra runtime: " << average << endl;
     total = 0;

     order.clear();    

     for (int i = 0; i < 100; ++i)
     {
          clock_t start1=clock();
          fastDijkstra(largeGraph, 'a', 'z', order);
          clock_t end1=clock();
          float time = diffclock(end1, start1);
          total += time;
     }        

     average = total/100;
     cout << "Average improved Dijkstra runtime: " << average << endl;
     cout << "----------------------------------------------------------------" << endl;
     
     // Reset Total
     total = 0;

     // Reset order vector
     order.clear();    





     //change second and third parameter, respecively, to change 
     //the source and goal node
     //Packets
     cout << "\n\n";
     cout << "-----------------------------------------" << endl;    
     cout << "-----------------------------------------" << endl;
     cout << "Original Dijkstra algorithm (equal delays on small graph):" << endl;
     Save.FindPath(largeGraph, 'u', 'z', order);
     cout << "-----------------------------------------" << endl;

     order.clear();
     Save.setNodal(50);
     cout << "Improved Dijkstra algorithm (Nodal-Processing delay on small graph):";    
     Save.FindPath2(smallGraph, 'u', 'z', order);
     cout << "-----------------------------------------" << endl;

     order.clear();
     Save.setQueue(3);    
     Save.setNodal(25);    
     cout << "Improved Dijkstra algorithm (Queue delay on small graph):";    
     Save.FindPath2(smallGraph, 'u', 'z', order);
     cout << "-----------------------------------------" << endl;

     order.clear();    
     Save.setTransmission(33);
     Save.setQueue(25);      
     cout << "Improved Dijkstra algorithm (Transmission delay on small graph):";    
     Save.FindPath2(smallGraph, 'u', 'z', order);
     cout << "-----------------------------------------" << endl;

     order.clear();
     Save.setPropagation(38);
     Save.setTransmission(25);    
     cout << "Improved Dijkstra algorithm (Propagation delay on small graph):";  
     Save.FindPath2(smallGraph, 'u', 'z', order);
     cout << "-----------------------------------------" << endl;



     //change second and third parameter, respecively, to change 
     //the source and goal node
     //Packets
     cout << "\n\n";
     cout << "-----------------------------------------" << endl;    
     cout << "-----------------------------------------" << endl;
     Save.setNodal(25);
     Save.setQueue(25); 
     Save.setPropagation(25);
     Save.setTransmission(25);       
     cout << "Original Dijkstra algorithm (equal delays on large graph):" << endl;
     Save.FindPath(largeGraph, 'a', 'z', order);
     cout << "-----------------------------------------" << endl;

     order.clear();
     Save.setNodal(50);
     cout << "Improved Dijkstra algorithm (Nodal-Processing delay on large graph):";    
     Save.FindPath2(largeGraph, 'a', 'z', order);
     cout << "-----------------------------------------" << endl;

     order.clear();
     Save.setQueue(3);    
     Save.setNodal(25);    
     cout << "Improved Dijkstra algorithm (Queue delay on large graph):";    
     Save.FindPath2(largeGraph, 'a', 'z', order);
     cout << "-----------------------------------------" << endl;

     order.clear();    
     Save.setTransmission(33);
     Save.setQueue(25);      
     cout << "Improved Dijkstra algorithm (Transmission delay on large graph):";    
     Save.FindPath2(largeGraph, 'a', 'z', order);
     cout << "-----------------------------------------" << endl;

     order.clear();
     Save.setPropagation(38);
     Save.setTransmission(25);    
     cout << "Improved Dijkstra algorithm (Propagation delay on large graph):";    
     Save.FindPath2(largeGraph, 'a', 'z', order);
     cout << "-----------------------------------------" << endl;                   

}

/*******************************************************************************

********************************** MAIN FUNCTIONS ***********************************

********************************************************************************/

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
AdjacentListNode* nameAdjacentListNode(char input){

	AdjacentListNode* newNode = (AdjacentListNode*) malloc(sizeof(AdjacentListNode));
	newNode->nodeName = input;

     return newNode;

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
AdjacentListNode* newAdjacentListNode(char neighbor, int distance){

	AdjacentListNode* newNode = (AdjacentListNode*) malloc(sizeof(AdjacentListNode));
	newNode->neighbor = neighbor;
	newNode->distance = distance;
	newNode->next = NULL;

     return newNode;

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
Graph* createGraph(int numberOfVertices){

	Graph* graph = (Graph*) malloc(sizeof(Graph));
	graph->numberOfVertices = numberOfVertices;

	graph->array = (struct AdjacentList*) malloc(numberOfVertices * sizeof(struct AdjacentList));

	int index;
	for (int index = 0 ; index < numberOfVertices ; index++) {
		graph->array[index].headPtr = NULL;
	}

	graph->numberOfEdges = 0;

	return graph;
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
float diffclock(clock_t clock1, clock_t clock2)
{
    float diffticks = clock1-clock2;
    float diffms = (diffticks)/(CLOCKS_PER_SEC/1000);
    diffms /= 1000;
    return diffms;
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void wait(int msec){
	
     clock_t start = clock();
	bool keepgoing = true;


	while(keepgoing) {
		
          clock_t end=clock();
		int save = diffclock(end, start) * 1000; 
		
          if (save >= msec) {
			
               keepgoing = false;
		}
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void addEdge(struct Graph*& graph, char source, char neighbor, int distance){

    AdjacentListNode* newNode = newAdjacentListNode(neighbor, distance);
    int saveLocation;
    bool done = 0;

    //Find starting node 
    for (int i = 0; i < graph->numberOfVertices; i++)
    {
    	if (graph->array[i].headPtr->nodeName == source)
    	{
    		saveLocation = i;
    		break;
    	}
    }

    AdjacentListNode* pointer = graph->array[saveLocation].headPtr;

    if (pointer == NULL)
    {
    	pointer = newNode;
    }

    else
    {
	    while (pointer->next != NULL)
	    {
	    	pointer = pointer->next;
	    }    	
	    pointer->next = newNode;
    }

    graph->numberOfEdges += 1;

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void printGraph(struct Graph* graph)
{
    int vertex;

    //print graph in it's entirety
    for (vertex = 0; vertex < graph->numberOfVertices; vertex++)
    {
        AdjacentListNode* graphOutput = graph->array[vertex].headPtr;
        
        cout << "Adjacency list of vertex " << graph->array[vertex].headPtr->nodeName << endl << "head";
        
        graphOutput = graphOutput->next;

        while (graphOutput != NULL)
        {
            cout << " -> " << graphOutput->neighbor << "-" << graphOutput->distance;
            graphOutput = graphOutput->next;
        }
        cout << endl;
    }
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
// Implementation of the Bellman Ford algorithm
void bellmanFord(Graph* graph, char source){

     char sourceNodeName, prevSourceNodeName;
	char neighborNodeName;
	int distanceBetweenNodes;
	int indexOfSource = 0;
	int indexOfNeighbor = 0;
	bool continueAlg = 1;
	int totalIterations = 0;



	int vertices = graph -> numberOfVertices;
	int edges = graph -> numberOfEdges;	
	int dist[vertices]; //integer array to hold values of distance from source
	char sourceNodes[vertices]; //character array to hold nodes' characters

	//Copy start of adjacency list into new array
	for (int i = 0 ; i < vertices ; i++)
	{
		sourceNodes[i] = graph -> array[i].headPtr->nodeName;
	}

	//Set values of each node to 1000 except the one passed by parameter
	//1000 is to help indicate that distance has not been evaluated yet
	for (int i = 0 ; i < vertices ; i++)
	{
		dist[i] = 1000;
		if (sourceNodes[i] == source)
		{
			dist[i] = 0;
		}
	}
	

	//Go through all the vertices
	for (int i = 0 ; i < vertices ; i++)
	{
		//Go through all the edges
		for (int j = 0 ; j < vertices ; j++)
		{
			//Create pointer to headPtr of array to prevent segmentation faults
			AdjacentListNode* bellmanPointer = graph -> array[j].headPtr;
			totalIterations++;

			//Store name of the node
	  		sourceNodeName = bellmanPointer->nodeName;
	  		
	  		if (sourceNodeName == prevSourceNodeName)
	  		{
	  			continueAlg = 0;
	  		}
	  		else
	  		{
	  			prevSourceNodeName = sourceNodeName;
	  		}

	  		if (continueAlg == 0)
	  		{
	  			cout << "here" << endl;
	  			bellmanPointer == NULL;
	  			i = vertices;
	  			j = vertices;
	  		}
			
	  		//Move to next item in the node's adjacency list
			bellmanPointer = bellmanPointer->next;

			//While adjacency list of that node does not hit NULL
			while (bellmanPointer != NULL)
			{
				//Set neighbor name
				neighborNodeName = bellmanPointer->neighbor;
				//Set distance between the nodes
				distanceBetweenNodes = bellmanPointer->distance;

				//Find index of the node 
				while (sourceNodes[indexOfSource] != sourceNodeName)
				{
					indexOfSource++;
				}

				//Find index of its neighbor
				while (sourceNodes[indexOfNeighbor] != neighborNodeName)
				{
					indexOfNeighbor++;
				}

				//If distance has been set and the value is less than the distance of the neighbor
				if ((dist[indexOfSource] != 1000) && (((dist[indexOfSource] + distanceBetweenNodes) < dist[indexOfNeighbor])))
				{
					//Set new value of distance (shortest path possible)
					dist[indexOfNeighbor] = dist[indexOfSource] + distanceBetweenNodes;
				}

				//Move onto next item in adjacency list
				bellmanPointer = bellmanPointer->next;

				//Reset index values to be used
				indexOfSource = 0;
				indexOfNeighbor = 0;				
			}

		}
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
//Function prints out the results of a Bellman-Ford algorithm
void printBellmanFord(int dist[], char sourceNodes[], int vertices){

	cout << endl << "Vertex    Distance from Source" << endl;
	for (int i = 0 ; i < vertices ; i++)
	{
		cout << sourceNodes[i] << "         " << dist[i] << endl;
	}

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void fastDijkstra(Graph* graph, char start, char finish, vector<char> &order)
{
	/* -------------------------- OVERHEAD ---------------------------*/
	//needs forwarding table, saving smallest path cost to get to node
	char point;
	AdjacentListNode* pointer;
	
	int distanceTraveled = 0;
	int size = graph->numberOfVertices;


	char heads[size];
	int dist[size];
	bool sptSet[size];
	int min = 1000, min_index;
	char minNode;

	//initialize arrays
	for (int i = 0; i < size; ++i)
	{
		dist[i] = 1000;
		sptSet[i] = 0;
	}

	for (int i = 0; i < size; ++i)
	{
		//set each value to "infinity" until set
		//cout << graph->array[i].headPtr->nodeName;
		point = graph->array[i].headPtr->nodeName;
		heads[i] = point;
		if (point == start)
		{
			pointer = graph->array[i].headPtr;
			dist[i] = 0;
			sptSet[i] = 1;
		}
	}
	AdjacentListNode* move;

	//searches until entire graph is known
	bool continueAlg = 1;
	char prevSourceNodeName;

	//loop for entirity of graph
	for (int j = 0; j < size; ++j)
	{
		//set move to head's next
		move = pointer;
		//cout << "Evaluating at node: " << move->nodeName << endl;

	/*---------------------------------UPDATE-------------------------------------*/
		//Added cases where Dijkstra finishes exploring nodes early
		//and breaks out of the loop, saving large amounts of algorithm time
		if (move->nodeName == prevSourceNodeName || move->nodeName == finish)
  		{
  			continueAlg = 0;
  		}
  		else
  		{
  			order.push_back(move->nodeName);
  			prevSourceNodeName = move->nodeName;
  		}

  		if (continueAlg == 0)
  		{
  			order.push_back(move->nodeName);
  			break;
  		}

		//Run search for distances outward
		min = 1000;
		while(move != NULL)
		{
			if (min > move->distance)
			{	
				min = move->distance;
				minNode = move->neighbor;
				for (int i = 0; i < size; ++i)
				{
					if (minNode == heads[i] && min < dist[i] && sptSet[i] == 0)
					{
						dist[i] = min + distanceTraveled;
					}
					else if (minNode == heads[i] && min < dist[i])
					{
						dist[i] = min + distanceTraveled;
					}
				}
			}
			move = move->next;
			min = 1000;
		}

		//Done finding distances, now determine shortest path from dist
		for (int i = 0; i < size; ++i)
		{
			if (min > dist[i] && dist[i] != 0 && sptSet[i] != 1)
			{
				min = dist[i];
				min_index = i;
				sptSet[i] = 1;
				distanceTraveled = min;
			}
		}
		//use shortest path outward to update which node pointer is located
		pointer = graph->array[min_index].headPtr;
		distanceTraveled = dist[min_index];
			
		//print current iteration's forwarding table
		/*
		cout << "---Printing updated forwarding table---" << endl;
		for (int i = 0; i < size; ++i)
		{
			cout << heads[i] << " " << dist[i] << endl;
		}
		*/
	}
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void slowDijkstra(Graph* graph, char start, char finish, vector<char> &order)
{
	/* -------------------------- OVERHEAD ---------------------------*/
	//needs forwarding table, saving smallest path cost to get to node
	char point;
	AdjacentListNode* pointer;
	
	int distanceTraveled = 0;
	int size = graph->numberOfVertices;


	char heads[size];
	int dist[size];
	bool sptSet[size];
	int min = 1000, min_index;
	char minNode;

	//initialize arrays
	for (int i = 0; i < size; ++i)
	{
		dist[i] = 1000;
		sptSet[i] = 0;
	}

	for (int i = 0; i < size; ++i)
	{
		//set each value to "infinity" until set
		//cout << graph->array[i].headPtr->nodeName;
		point = graph->array[i].headPtr->nodeName;
		heads[i] = point;
		if (point == start)
		{
			pointer = graph->array[i].headPtr;
			dist[i] = 0;
			sptSet[i] = 1;
		}
	}
	AdjacentListNode* move;

	//searches until entire graph is known
	bool continueAlg = 1;
	char prevSourceNodeName;

	//loop for entirity of graph
	for (int j = 0; j < size; ++j)
	{
		//set move to head's next
		move = pointer;
		//cout << "Evaluating at node: " << move->nodeName << endl;
		order.push_back(move->nodeName);

		//Run search for distances outward
		min = 1000;
		while(move != NULL)
		{
			if (min > move->distance)
			{	
				min = move->distance;
				minNode = move->neighbor;
				for (int i = 0; i < size; ++i)
				{
					if (minNode == heads[i] && min < dist[i] && sptSet[i] == 0)
					{
						dist[i] = min + distanceTraveled;
					}
					else if (minNode == heads[i] && min < dist[i])
					{
						dist[i] = min + distanceTraveled;
					}
				}
			}
			move = move->next;
			min = 1000;
		}

		//Done finding distances, now determine shortest path from dist
		for (int i = 0; i < size; ++i)
		{
			if (min > dist[i] && dist[i] != 0 && sptSet[i] != 1)
			{
				min = dist[i];
				min_index = i;
				sptSet[i] = 1;
				distanceTraveled = min;
			}
		}
		//use shortest path outward to update which node pointer is located
		pointer = graph->array[min_index].headPtr;
		distanceTraveled = dist[min_index];
			
		//print current iteration's forwarding table
		/*
		cout << "---Printing updated forwarding table---" << endl;
		for (int i = 0; i < size; ++i)
		{
			cout << heads[i] << " " << dist[i] << endl;
		}
		*/
	}
}


/*******************************************************************************

***************************** CONFIG CLASS FUNCTIONS ***************************

********************************************************************************/

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void Config::setNodal(int nodal){

	Processing_delay = nodal;

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void Config::setQueue(int queue){

	Queue_delay = queue;

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void Config::setPropagation(int propagation){

	Propagation_delay = propagation;

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void Config::setTransmission(int transmission){

	Transmission_delay = transmission;

}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void Config::readConfigSmall(Graph*& graph)
{

	ifstream fileIn;
	fileIn.open("Config.conf"); 			

	string input;
	char algorithm;
	int delayTime;


	//read in from file
	while (!fileIn.eof())
	{
		fileIn >> input;

		if (input == "Algorithm:")
		{
			fileIn >> algorithm;
			algorithmName = algorithm;
		}

		if (input == "Queue:")
		{
			fileIn >> delayTime;
			Queue_delay = delayTime;
		}

		if (input == "Propagation:")
		{
			fileIn >> delayTime;
			Propagation_delay = delayTime;
		}

		if (input == "Processing:")
		{
			fileIn >> delayTime;
			Processing_delay = delayTime;
		}

		if (input == "Transmission:")
		{
			fileIn >> delayTime;
			Transmission_delay = delayTime;
		}						

	}

	fileIn.close();

	fileIn.open("smallGraph.txt");

	int numberOfNodes;
	char nodeNames;
	char nodeStart;
	char nodeEnd;
	int nodeDistance;

	fileIn >> numberOfNodes;

	//create graph
	graph = createGraph(numberOfNodes);

	//initialize headPtr for each spot in array
	for (int i = 0 ; i < numberOfNodes ; i++)
	{
		fileIn >> nodeNames;
    	     AdjacentListNode* newNode = nameAdjacentListNode(nodeNames);		
		graph->array[i].headPtr = newNode;
	}

	//set nodeStart, nodeEnd, and nodeDistance for each edge
	while (!fileIn.eof())
	{
		fileIn >> nodeStart;
		fileIn >> nodeEnd;
		fileIn >> nodeDistance;
		addEdge(graph, nodeStart, nodeEnd, nodeDistance);
	}

	fileIn.close();
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
void Config::readConfigLarge(Graph*& graph)
{

	ifstream fileIn;
	fileIn.open("Config.conf"); 
	string input;
	char algorithm;
	int delayTime;

	//read in from file
	while (!fileIn.eof())
	{
		fileIn >> input;

		if (input == "Algorithm:")
		{
			fileIn >> algorithm;
			algorithmName = algorithm;
		}

		if (input == "Queue:")
		{
			fileIn >> delayTime;
			Queue_delay = delayTime;
		}

		if (input == "Propagation:")
		{
			fileIn >> delayTime;
			Propagation_delay = delayTime;
		}

		if (input == "Processing:")
		{
			fileIn >> delayTime;
			Processing_delay = delayTime;
		}

		if (input == "Transmission:")
		{
			fileIn >> delayTime;
			Transmission_delay = delayTime;
		}						

	}

	fileIn.close();

	fileIn.open("largeGraph.txt");

	int numberOfNodes;
	char nodeNames;
	char nodeStart;
	char nodeEnd;
	int nodeDistance;

	fileIn >> numberOfNodes;

	//create graph
	graph = createGraph(numberOfNodes);

	//initialize headPtr for each spot in array with the 10 vertex names 
	for (int i = 0 ; i < numberOfNodes ; i++)
	{
		fileIn >> nodeNames;
    	     AdjacentListNode* newNode = nameAdjacentListNode(nodeNames);		
		graph->array[i].headPtr = newNode;
	}

	//set nodeStart, nodeEnd, and nodeDistance for each edge
	while (!fileIn.eof())
	{
		fileIn >> nodeStart;
		fileIn >> nodeEnd;
		fileIn >> nodeDistance;
		addEdge(graph, nodeStart, nodeEnd, nodeDistance);
	}

	fileIn.close();
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
//This function runs the desired algorithm and proceeds to simulate packets
//being sent within specified amount of time, keepalive
void Config::FindPath(Graph* graph, char start, char goal, vector<char> &order){

	//relevant data
	int packet = 576; //bytes
	bool keepgoing = true, algorithmRan = false;
	
	//Specific run time in msec, change to simulate longer packet transfer 
	int keepalive = 3000;
	
	float increment = 0;
	vector<char> copy;
	int lul = 0;
	//Start time, run algorithm once, then spend packets with simulated Nodal
	//Processing, Queue, Transmission, and Propagation delay
	clock_t begin = clock();

	while (keepgoing) {

		if (algorithmRan == 0)
		{
			slowDijkstra(graph, start, goal, order);
			copy = order;
			algorithmRan = true;
		}

		order = copy;
		clock_t check = clock();
		float timecheck = diffclock(check, begin)*1000;

		//checks if time is over specified time limit
		if (timecheck >= keepalive){
			break;
		}
		else{

			//simulate Nodal Processing delay
			wait(Processing_delay);
			
			//Travel over Hops until at goal node
			while(order.size() != 0){

				//simulate Queue delay
				wait(Queue_delay);
				
				//simulate Transmission delay
				wait(Transmission_delay);
				
				//simulate Propogation delay
				wait(Propagation_delay);

				order.erase(order.begin());
			}
			increment++;
		}
	}

	cout << "Total packets sent: " << increment << endl;
	cout << "Total bytes sent: " << increment * packet << endl;
}

/* -----------------------------------------------------------------------------
FUNCTION:          
DESCRIPTION:       
RETURNS:           None
NOTES:             
------------------------------------------------------------------------------- */
//This function runs the desired algorithm and proceeds to simulate packets
//being sent within specified amount of time, keepalive
void Config::FindPath2(Graph* graph, char start, char goal, vector<char> &order){

	//relevant data
	int packet = 576; //bytes
	bool keepgoing = true, algorithmRan = false;
	
	//Specific run time in msec, change to simulate packet transfer for longer
	int keepalive = 3000;
	
	float increment = 0;
	vector<char> copy;
	int lul = 0;
	//Start time, run algorithm once, then spend packets with simulated Nodal
	//Processing, Queue, Transmission, and Propagation delay
	clock_t begin = clock();

	for (int i = 0 ; i < order.size() ; i++)
	{
		cout << order[i] << " ";
	}

	cout << endl;

	while(keepgoing){

		if (algorithmRan == false)
		{
			fastDijkstra(graph, start, goal, order);
			copy = order;
			algorithmRan = true;
		}

		order = copy;
		clock_t check = clock();
		float timecheck = diffclock(check, begin)*1000;

		//checks if time is over specified time limit
		if (timecheck >= keepalive) {
			break;
		}

		else {

			//simulate Nodal Processing delay
			wait(Processing_delay);
			
			//Travel over Hops until at goal node
			while(order.size() != 0){

				//simulate Queue delay
				wait(Queue_delay);
				
				//simulate Transmission delay
				wait(Transmission_delay);
				
				//simulate Propogation delay
				wait(Propagation_delay);

				order.erase(order.begin());
			}
			increment++;
		}
	}

	/*
	cout << "Processing: " << Processing_delay << endl;
	cout << "Queue: " << Queue_delay << endl;
	cout << "Transmission: " << Transmission_delay << endl;
	cout << "Propagation: " << Propagation_delay << endl;
	*/
	cout << "Total packets sent: " << increment << endl;
	cout << "Total bytes sent: " << increment * packet << endl;
}

