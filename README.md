# CPE 400 Final Project

## Ashley Ponce, Christopher Collum, Conner Fissell, Luke Collier

### How To Run
make main
./main

### Project Idea
Two graphs that represent networks are created (a small a large one, 6 vertices and 10 vertices). The readConfigSmall() and readConfigLarge() functions set the Queue, Propogation, Processing, and Transmission delay values (these are established in the Config.conf file.) of the Config class object and also define the vertices and distances for each graph. The graph info is read in from the smallGraph.txt and largeGraph.txt files. The Config class object is used to manipulate both graphs.  

This program first uses two different versions of Dijkstras Algorithm (a slow and fast version, along with the Bellman-Ford algorithm) to compare the graph traversal processing times for each graph.
Then, comparisons are made amongst the different algorithms with each graph that factor in the network delay values. This is where the network packet information comes in. 