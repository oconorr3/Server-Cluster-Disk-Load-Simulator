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
        int numberOfNodes;
        std::vector<double> *nodeLoadData;							//array of vectors, where each vector holds the data records for its respective node
    public:
        DataBank(int numNodes);					//constructor
        ~DataBank();                            //destructor
        int maxLoad;
        int getMaxLoad();
        int getNumNodes();
        void logData(int nodeNumber, double load);				//used by nodes to report data to the data bank
        void exportData();
        void printData();										//prints the data for every node to to std out

        std::vector<double> getNodeLoadsAtTime(int t);
        std::vector<double> getTimes();
        std::vector<double> * getNodeLoadData();
        std::vector<double> calcAveragesByTime();    //calculates the overall average across all nodes
};


#endif
