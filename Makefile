dijkstra: Ilano_TestGraph.o MatrixGraph_Ilano.o
	g++ -g -Wall Ilano_TestGraph.o MatrixGraph_Ilano.o -o dijkstra

Ilano_TestGraph.o: Ilano_TestGraph.cpp
	g++ -g -Wall -c Ilano_TestGraph.cpp

MatrixGraph_Ilano.o: MatrixGraph_Ilano.cpp MatrixGraph_Ilano.h
	g++ -g -Wall -c MatrixGraph_Ilano.cpp

clean:
	rm *.o dijkstra