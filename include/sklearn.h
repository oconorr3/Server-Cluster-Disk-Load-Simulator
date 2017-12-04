#ifndef SKLEARN_H
#define SKLEARN_H

#include <map>
#include <boost/python.hpp>
#include <Python.h>

#include "pickleloader.h"
#include "pyutils.h"

class Sklearn {
public:
    Sklearn();

    void loadNetwork(std::string networkFile);

    std::string getPrediction(std::vector<PickleData> dataList);

    std::string getPredictionByEventNumber(PickleLoader pLoader, std::string filename,
        int eventnumber);

private:
    // Python-callable attributes and functions:
    py::object sklearn;
    py::object load_networkfile;
    py::object get_prediction;
    py::object skl_network;
};


#endif
