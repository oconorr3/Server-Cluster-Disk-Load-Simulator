#include "../include/databank.h"



DataBank::DataBank(int numNodes)  {
    std::cout << "initialized databank" << std::endl;
    numberOfNodes       = numNodes;
    nodeLoadData        = new std::vector<double>[numberOfNodes];
    maxLoad = 0;
    //create a list for every node to report to
    for (int i = 0; i < numberOfNodes; i++) {
        std::vector<double> nodeDataList;
        nodeLoadData[i] = nodeDataList;
    }
}


DataBank::~DataBank() {
    std::cout << "databank destroyed" << std::endl;
    delete [] nodeLoadData;
}

int DataBank::getMaxLoad() {
    return maxLoad;
}

int DataBank::getNumNodes() {
    return numberOfNodes;
}


void DataBank::printData() {
        for (int i = 0; i < numberOfNodes; i++) {
        std::vector<double> iNode = nodeLoadData[i];

                std::cout << "DiskNode " << i << " data: ";
                for (int j = 0; j < (int)iNode.size(); j++) {
                        std::cout << iNode[j] << "\t";
                }
                std::cout << "\n";
        }
}

std::vector<double> * DataBank::getNodeLoadData() {
    return nodeLoadData;
}



void DataBank::logData(int nodeNumber, double load) {
    //std::cout << "Node " << nodeNumber << " logging data with load..." << load << std::endl;
    //if laod is negative make it zero
    if (load < 0) {
        load = 0;
    }
    if (load > maxLoad) {
        maxLoad = load;
    }
    //validate that the node is valid
    if (!(nodeNumber < 0 || nodeNumber >= numberOfNodes)) {
        nodeLoadData[nodeNumber].push_back(load);
    }
}
std::vector<double> DataBank::calcAveragesByTime() {
    int maxTime = nodeLoadData[0].size();
    std::vector<double> averages;
    double sum;
    for (int t = 0; t < maxTime; t++) {
        sum = 0;
        for (int n = 0; n < numberOfNodes; n++) {
            sum += nodeLoadData[n][t];
        }

        averages.push_back(sum / numberOfNodes);
    }

    return averages;
}

std::vector<double> DataBank::getNodeLoadsAtTime(int t) {
    std::vector<double> res;
    //push every node value at time t
    for (int i = 0; i < numberOfNodes; i++) {
        res.push_back(nodeLoadData[i][t]);
    }
    return res;
}

std::vector<double> DataBank::getTimes() {
    int maxTime = nodeLoadData[0].size();
    std::vector<double> times;
    for (int t = 0; t < maxTime; t++) {
        times.push_back(t);
    }
    return times;
}


void DataBank::exportData() {
    //calc the averages which will be its own seperate .csv
    std::ofstream averagesFile;
    averagesFile.open("averages.csv");
    std::vector<double> averages = calcAveragesByTime();

    for (int i = 0; i < averages.size(); i++) {
        averagesFile << averages[i] << "\n";
    }
    averagesFile.close();

    //write the data out to a .csv where each row is a node and each column is a time point
    std::ofstream dataFile;
    dataFile.open("data.csv");
    for (int i = 0; i < numberOfNodes; i++) {
        for (int j = 0; j < nodeLoadData[i].size(); j++) {
            dataFile << nodeLoadData[i][j] << " ";
        }
        dataFile << "\n";
    }
    dataFile.close();

}





