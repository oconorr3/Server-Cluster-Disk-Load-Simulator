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
	private:
		int reportLoadInterval;	
		int numberOfNodes;
		
		int *nodeLoadSums;
		double *nodeLoadAverages;
		std::vector<int> *nodeLoadData;							//array of vectors, where each vector holds the data records for its respective node
	
	public: 
		DataBank(int numNodes, int interval);					//constructor
		~DataBank();											//destructor
		void reportLoad(int nodeNumber, int load);				//used by nodes to report data to the data bank
		void printData();										//prints the data for every node to to std out
		void graphAvg(std::string directory);					//graphs the average load across all nodes
		void graphSnapshot(int t, std::string directory); 		//produces a grpah for each reportLoadInterval, x-axis -> node n, y-axis-> load on that node at time t * reportLoadInterval
		void graphAllSnapshots(std::string directoryName);
		
		std::vector<int> * getNodeLoadData();
		double *getAverages();
};




#endif
