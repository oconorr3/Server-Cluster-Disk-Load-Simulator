#ifndef DATABANK_H
#define DATABANK_H

//Header for the DataBank/ This class will be in charge of graphing and recieving data from the nodes.

#include <vector>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>

class DataBank {
	public: 
		/*Public Function Declarations*/
		DataBank(int numNodes, int interval);
		void reportLoad(int nodeNumber, int data);
		void printData();
		void graphDataDynamically();
		void graphData();
				
	private:
		int reportLoadInterval;	//used for graphing
		int timeStepCounter;
		int numberOfNodes;
		std::vector<int> *nodeLoadData;	//array of vectors, where each vector holds the data records for its respective node
		
		std::vector<double> calculateAverages(); 
};




#endif
