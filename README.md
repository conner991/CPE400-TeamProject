# CPE 400 Final Project

## Ashley Ponce, Christopher Collum, Conner Fissell, Luke Collier

### How To Run
make main
./main

### Project Idea
Two graphs that represent networks are created (a small a large one, 6 vertices and 10 vertices). They are created using the Queue, Propogation, Processing, and Transmission delay values established in the Config.conf file.

This program first uses two different versions of Dijkstras Algorithm (a slow and fast version, along with the Bellman-Ford algorithm) to compare the graph traversal processing times for each graph.
Then, comparisons are made amongst the different algorithms with each graph that factor in the network delay values. This is where the network packet information comes in. 