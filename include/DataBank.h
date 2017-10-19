#ifndef DATABANK_H
#define DATABANK_H

//Header for the DataBank/ This class will be in charge of graphing and recieving data from the nodes.

#include <vector>

class DataBank {
	public: 
		/*Public Function Declarations*/
		DataBank(int numberOfNodes);
		reportLoad(int nodeNumber, int data);

	private:
		int timeStepCounter;
		std:vector<std:list<int>> nodeLoadData;
};

#endif
