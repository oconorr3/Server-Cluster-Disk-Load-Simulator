#include <boost/python.hpp>
#include <Python.h>
#include <boost/format.hpp>
#include <iostream>
#include <map>
#include <vector>
#include "pickleloader.h"
#include "pyutils.h"

PickleLoader::PickleLoader() {
    Py_Initialize();
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append(\".\")");
    this->pickleloader = py::import("pysim.pickleloader");
    this->load_pickle = pickleloader.attr("load_pickle");
}

PickleData PickleLoader::itemAtIndex(std::string pickleFile, int index) {
    PickleData pickleData;
    pickleData.initialized = false;

    try {
        // Extract the pickle data for the given file at the specified index
        py::list data = py::extract<py::list>(this->pickle_data[pickleFile]);
        py::dict dict = py::extract<py::dict>(data[index]);

        // Get all of the different elements of the row of data from the pickle
        int timestamp = py::extract<int>(dict["timestamp"]);
        int elapsedTime = py::extract<int>(dict["elapsedTime"]);
        bool isWrite = py::extract<bool>(dict["isWrite"]);
        std::string fileName = py::extract<std::string>(dict["fileName"]);
        int diskNum = py::extract<int>(dict["diskNum"]);
        int size = py::extract<int>(dict["size"]);

        // Set the structure members accordingly
        pickleData.initialized = true;
        pickleData.timestamp = timestamp;
        pickleData.elapsedTime = elapsedTime;
        pickleData.isWrite = isWrite;
        pickleData.fileName = fileName;
        pickleData.diskNum = diskNum;
        pickleData.size = size;


        // Return the result
        return pickleData;
    } catch(boost::python::error_already_set const &) {
        std::string perror_str = parse_python_exception();
        std::cout << "Error in Python: " << perror_str << std::endl;
        
        // Return entirely uninitialized structure in the event of failure
        return pickleData;
    }
}

int PickleLoader::loadPickle(std::string pickleFile) {
    std::cout << "[C++] Starting to load pickle: " << pickleFile << "..." << std::endl;

    try {
        py::list pickle_data = py::extract<py::list>(this->load_pickle(pickleFile));
        this->pickle_data.insert(std::pair<std::string, py::list>(pickleFile, pickle_data));
        this->pickle_list.push_back(pickleFile);

        // Return the length of the pickle data list
        return py::len(this->pickle_data[pickleFile]);
    } catch(boost::python::error_already_set const &){
        std::string perror_str = parse_python_exception();
        std::cout << "Error in Python: " << perror_str << std::endl;

        return -1;
    }
}
