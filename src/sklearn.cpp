#include <boost/python.hpp>
#include <Python.h>
#include <boost/format.hpp>

#include <vector>
#include "sklearn.h"
#include "pickleloader.h"
#include "pyutils.h"

/**
 * Constructor for the Sklearn class.
 **/
Sklearn::Sklearn() {
    Py_Initialize();

    try {
        PyRun_SimpleString("import sys");
        PyRun_SimpleString("sys.path.append(\".\")");
        this->sklearn = py::import("pysim.simskl");
        this->load_networkfile = this->sklearn.attr("load_networkfile");
        this->get_prediction = this->sklearn.attr("get_prediction");
    } catch(boost::python::error_already_set const &) {
        std::string perror_str = parse_python_exception();
        std::cout << "Error in Python: " << perror_str << std::endl;
        exit(-1);
    }
}

/**
 * CALL THIS FIRST! Load the network by its file name.
 **/
void Sklearn::loadNetwork(std::string networkFile) {
    std::cout << "[C++] Loading sklearn network..." << std::endl;
    try {
        this->skl_network = this->load_networkfile(networkFile);
    } catch(boost::python::error_already_set const &) {
        std::string perror_str = parse_python_exception();
        std::cout << "Error in Python: " << perror_str << std::endl;
        exit(-1);
    }
}

/**
 * Get a prediction based on a list of (5) PickleData objects.
 **/
std::string Sklearn::getPrediction(std::vector<PickleData> dataList) {
    std::string result = "";

    try {
        py::list pyDataList;
        for (auto dElement: dataList) {
            PickleData element = (PickleData) dElement;
            pyDataList.append(0);
            pyDataList.append(0);
            pyDataList.append(element.isWrite);
            pyDataList.append(element.size);
        }
        py::list listOfList;
        listOfList.append(pyDataList);
        result = py::extract<std::string>(this->get_prediction(this->skl_network, listOfList));
    } catch(boost::python::error_already_set const &) {
        std::string perror_str = parse_python_exception();
        std::cout << "Error in Python: " << perror_str << std::endl;
        exit(-1);
    }
    return result;
}

/**
 *
 **/
std::string Sklearn::getPredictionByEventNumber(PickleLoader pLoader, std::string filename,
    int eventNumber) {
    // For each event number, we will be looking at that event and its preceeding four events.
    // Event at index 0 is the CURRENT event, index 1 is the previous event, and so on.

    std::vector<PickleData> events;
    const int minimum = 4;
    int index = 0;
    int backFillCount = minimum - eventNumber;
    if (eventNumber < minimum) {
        PickleData zeroPickle;
        zeroPickle.initialized = true;
        zeroPickle.timestamp = 0;
        zeroPickle.elapsedTime = 0;
        zeroPickle.isWrite = false;
        zeroPickle.fileName = "";
        zeroPickle.diskNum = 0;
        zeroPickle.size = 0;
        for (int i = 0; i < backFillCount; i++) {
            events.push_back(zeroPickle);
        }
        index = backFillCount;
    }
    for (; index < 5; index++) {
        events.push_back(pLoader.itemAtIndex(filename, eventNumber - index));
    }
    return this->getPrediction(events);
}
