#include "../include/DataBank.h"

DataBank::DataBank(int numNodes, int interval)  {
	
	nodeLoadData = new std::vector<int>[numberOfNodes];
	numberOfNodes = numNodes;
	reportLoadInterval = interval;
	timeStepCounter = 0;
	
	
	//create a list for every node to report to
	for (int i = 0; i < numberOfNodes; i++) {
		std::vector<int> nodeDataList;
		nodeLoadData[i] = nodeDataList;
	}	
}


void DataBank::reportLoad(int nodeNumber, int data) {
	//go to the list in nodeLoadData that corresponds to the node number
	//and add the data
	if (!(nodeNumber < 0 || nodeNumber > numberOfNodes))
		nodeLoadData[nodeNumber].push_back(data);
}

void DataBank::printData() {
	for (int i = 0; i < numberOfNodes; i++) {
		std::vector<int> iNode = nodeLoadData[i];
		
		std::cout << "Node " << i << " data: ";
		for (int j = 0; j < (int)iNode.size(); j++) {
			std::cout << iNode[j] << "\t";
		}
		std::cout << "\n";

	}
}

std::vector<double> DataBank::calculateAverages() {
	std::vector<double> averages;
	
	int numberOfDataPoints = nodeLoadData[0].size();
	//go through each x value
	for (int i = 0; i < numberOfDataPoints; i++) {
		//compute sum of y values
		int sum = 0;
		for (int j = 0; j < numberOfNodes; j++) {
			std::vector<int> jNodeDataList = nodeLoadData[j];
			//std::cout << "adding data point " << jNodeDataList[i] << " to sum for point 1\n";
			sum += jNodeDataList[i];
		}
		
		//calculate avg of y values
		
		double avg = (double)sum / numberOfNodes;
		averages.push_back(avg);
		
	}
	
	return averages;
}


void DataBank::graphData() {
	std::string dataFileName;
	std::ofstream dataUnit;
	std::string plotFileName;	//in case we want to save it
	
	
	//write the avg load data to a file
	std::vector<double> averages = calculateAverages();
	dataFileName = "averageLoadDataValues.txt";
	dataUnit.open(dataFileName.c_str());
	
	int numberOfDataPoints = averages.size();
	for (int i = 0; i < numberOfDataPoints; i++) {
		
		dataUnit << reportLoadInterval * i << " "	//x value
			<< averages[i] << "\n";					//y value
	}
	dataUnit.close();
	
	
	//write command file
	std::string commandFileName = "gnuPlotCommands.txt";		
	system(("gnuplot " + commandFileName).c_str());
	system(("rm " + dataFileName).c_str());	//remove the data file
}


// int main() {
// 	DataBank dataBank(2, 5);
	
// 	//add some stuff to node0 list
// 	for (int i = 0; i < 10; i++) {
// 		dataBank.reportLoad(0, i * 1);
// 	}
	
// 	//add some stuff to node1 list
// 	for (int i = 0; i < 10; i++) {
// 		dataBank.reportLoad(1, i * 2);
// 	}
	
	
	
// 	dataBank.printData();
	
// 	dataBank.graphData();
// 	return 0;
// }
