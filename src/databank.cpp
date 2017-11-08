#include "../include/databank.h"

DataBank::DataBank(int numNodes, int interval)  {
	
	numberOfNodes = numNodes;
	nodeLoadData = new std::vector<int>[numberOfNodes];
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
	if (!(nodeNumber < 0 || nodeNumber >= numberOfNodes))
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


void DataBank::graphAvg(std::string directory) {
	std::string commandFileName;
    std::ofstream commandUnit;
	std::string dataFileName;
	std::ofstream dataUnit;
	std::string plotFileName;	//in case we want to save it
	
	
	//write the avg load data to a file
	std::vector<double> averages = calculateAverages();
	dataFileName = "averageLoadDataValues..dat";
	dataUnit.open(dataFileName.c_str());
	
	int numberOfDataPoints = averages.size();
	for (int i = 0; i < numberOfDataPoints; i++) {
		
		dataUnit << reportLoadInterval * i << " "	//x value
			<< averages[i] << "\n";					//y value
	}
	dataUnit.close();
	
	
	//write command file
	commandFileName = directory +  "gnuplot_commands.txt";
	plotFileName = directory + "average_load.png";
	
	commandUnit.open(commandFileName.c_str());
	commandUnit << "reset\n";
    commandUnit << "set term png size 2000, 1000\n";
    commandUnit << "set output \"" << plotFileName << "\"\n";
    commandUnit << "set grid\n";
    commandUnit << "set style data lines\n";
    commandUnit << "unset key\n";
    commandUnit << "set xlabel 'Time'\n";
    commandUnit << "set ylabel 'Avg Load'\n";
	commandUnit << "set title 'Average Loads'\n";
	commandUnit << "set yrange[0:*]\n";
    commandUnit << "set timestamp\n";
    commandUnit << "plot \"" << dataFileName << "\" using 1:2 with lines lw 3\n";
    commandUnit << "quit\n";
    commandUnit.close();
	
	
	//graph the data & remove command and data files
	system(("gnuplot " + commandFileName).c_str());
	system(("rm " + commandFileName).c_str());	
	//system(("rm " + dataFileName).c_str());	
}

void DataBank::graphSnapshot(int t, std::string directory) {
	std::string commandFileName;
    std::ofstream commandUnit;
	std::string dataFileName;
	std::ofstream dataUnit;
	std::string plotFileName;	//in case we want to save it
	
	int time = t * reportLoadInterval;
	
	dataFileName = directory + std::string("loads_at_time_") + std::to_string(time) + std::string(".dat");
	dataUnit.open(dataFileName.c_str());
	
	std::vector<int> loads;
	//go through each list and get the data point at node t in the list
	for (int i = 0; i < numberOfNodes; i++) {
		std::vector<int> iNodeDataList = nodeLoadData[i];
		
		dataUnit << i << " Node" + std::to_string(i) + " "								//x value-> node i
			<< iNodeDataList[t] << "\n";					//y value-> load on that node at time = t
	}
	dataUnit.close();
	
	//write command file
	commandFileName = directory + "gnuplot_commands.txt";
	plotFileName = directory + std::string("loads_at_time_") + std::to_string(time) + ".png";
	
	commandUnit.open(commandFileName.c_str());
	commandUnit << "reset\n";
	commandUnit << "set term png size 2000, 1000\n";
    commandUnit << "set output \"" << plotFileName << "\"\n";
    commandUnit << "set boxwidth 0.5\n";
	commandUnit << "set style fill solid 1.00 border 0\n";
	commandUnit << "set style histogram\n";
	commandUnit << "set style data histogram\n";
    commandUnit << "unset key\n";
    commandUnit << "set xlabel 'Nodes'\n";
    commandUnit << "set ylabel 'Load'\n";
	commandUnit << "set grid ytics linestyle 1\n";
	commandUnit << "set xtics rotate by -45\n";
    commandUnit << "set timestamp\n";
	commandUnit << "set yrange[0:*]\n";
	commandUnit << "set title 'Loads At Time t = " + std::to_string(time) + "\n";
    commandUnit << "plot \"" << dataFileName << "\" using 1:3:xtic(2) ti 'Load' with boxes linecolor rgb '#0000FF'\n";
    commandUnit << "quit\n";
    commandUnit.close();
	
	
	//graph the data & remove command and data files
	system(("gnuplot " + commandFileName).c_str());
	system(("rm " + commandFileName).c_str());	
	//system(("rm " + dataFileName).c_str());	
	
}

void DataBank::graphAllSnapshots(std::string directoryName) {
	static int count = 0;
	count++;
	
	//make a directory for the graphs/data files
	std::string path = std::string("./") + directoryName + std::string("/");
	
	if(mkdir((path).c_str(),  S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) == -1) //creating a directory
	{
		std::cout << "Error :  Making Directory\n";
		return;
	} 
	
	int numberOfDataPoints = nodeLoadData[0].size();
	//go through each x value
	for (int t = 0; t < numberOfDataPoints; t++) {
		graphSnapshot(t, path);
	}
}



 /*int main() {
 	DataBank dataBank(200, 5);	//100 nodes report int of 5 
	
	//add 1000 events to every node
	for (int node = 0; node < 200; node++) {
		for (int i = 0; i < 1000; i++) {
			dataBank.reportLoad(node, rand() % 1024);
		}
	}
	
	

	dataBank.graphAllSnapshots("yolo");

 	return 0;
 }*/
