#include "DataBank.h"

DataBank::DataBank(int numberOfNodes) {
	
	timeStepCounter = 0;
	//create a list for every node to report to
	for (int i = 0; i < numberOfNodes; i++) {
		std:list<int> nodeDataList;
		nodeLoadData.push_back(nodeDataList);
	}	
}


DataBank::reportLoad(int nodeNumber, int data) {
	//go to the list in nodeLoadData that corresponds to the node number
	//and add the data
		
}


int main() {
	return 0;
}
