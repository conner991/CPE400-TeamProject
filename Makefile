# ---------------------------------------------------------------------------------------
# FILE NAME:	Makefile
# 
# DESCRIPTION: 	Makefile for a C++ Program
#
# PURPOSE:		Build a program executable on Linux
# 
# MODIFICATION HISTORY: 
#
# Author		 		   Date				Modifications(s)
# ---------		 		----------			------------------
# Conner Fissell		09-18-2019			Version 1
# 
# ________________________________________________________________________________________

#	This is our original generic makefile command that will build
#	any stand alone ".cpp" source file
#	Usage: e.g. make hello
# .cpp:
# 	g++ -o $* $*.cpp -std=c++11


clean:
	rm -f main


Routing:	main.o Router.o
	g++ main.o Router.o -o Routing

main.o:	main.cpp Router.h Router.cpp
	g++ -c main.cpp

Router.o:	Router.h Router.cpp
	g++ -c Router.cpp