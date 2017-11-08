#ifndef DATABANK_H
#define DATABANK_H

//Header for the DataBank/ This class will be in charge of graphing and recieving data from the nodes.

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>


class DataBank {
	public: 
		/*Public Function Declarations*/
		DataBank(int numNodes, int interval);
		void reportLoad(int nodeNumber, int data);
		void printData();	//prints the data for every node to to std out
		void graphAvg(std::string directory);	//x axis-> time, y-axis -> avg load at that time from all nodes
		void graphSnapshot(int t, std::string directory); //produces a grpah for each reportLoadInterval, x-axis -> node n, y-axis-> load on that node at time t * reportLoadInterval
		void graphAllSnapshots(std::string directoryName);
	private:
		int reportLoadInterval;	//used for graphing
		int timeStepCounter;
		int numberOfNodes;
		std::vector<int> *nodeLoadData;	//array of vectors, where each vector holds the data records for its respective node
		
		std::vector<double> calculateAverages(); 
};




#endif
